#include "gradient.hpp"
#include "../image/image.hpp"
#include "../image/ppm-export.hpp"
#include "../image/pgm-export.hpp"
#include "../filters/gaussian.hpp"
#include "../filters/sharpen.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

double Gradient::angle_from_two(double x, double y){
	if(iszero(x) && iszero(y)) return 0;
	return atan2(y,x);
}

bool inline Gradient::clos(double a, double b, double ep){
	if(abs(a-b) < ep || abs(a-b-2*PI) < ep || abs(a-b+2*PI) < ep) return true;
	return false;
}

bool inline Gradient::corners_on_different_sides(int &Sx, int &Sy, double Gx, double Gy){
	//czy rogi kwadraciku o srodku w S sa po dwoch stronach wektora do G?
	return (((Sx+0.5)*Gy - (Sy+0.5)*Gx) * ((Sx-0.5)*Gy - (Sy-0.5)*Gx) < 0 ||
	   	    ((Sx+0.5)*Gy - (Sy-0.5)*Gx) * ((Sx-0.5)*Gy - (Sy+0.5)*Gx) < 0 );
}

int Gradient::Find(int x){
	if(p[x] == x) return x;
	p[x] = Find(p[x]);
	return p[x];
}

void Gradient::Union(int x, int y){
	if(Find(x) == Find(y)) return;
	p[p[x]] = p[y];
	detector.G[x].push_back(y);
	detector.G[y].push_back(x);
}

inline int min(int a, int b){
	if(a < b) return a; return b;
}

inline int max(int a, int b){
	if(a > b) return a; return b;
}

void Gradient::join(int x1,int y1,int x2,int y2,image& im, int color){
	if(x1 > x2){ std::swap(x1,x2); std::swap(y1,y2);}
	if(x1 != x2){
		for(int x = 1; x < x2-x1; x++){
			int y = (int)(y1 + x*(double)(y2-y1)/(double)(x2-x1));
			if(im.pixel(x1+x,y)==0) im.pixel(x1+x,y) = color;
		}
	}
	else for(int y = min(y1,y2)+1; y < max(y1,y2); y++)
			if(im.pixel(x1,y)==0) im.pixel(x1,y) = color;	
}

void Gradient::compute_gradients(){
	LX = new double*[n];
	LY = new double*[n];
	mag = new double*[n];
	ang = new double*[n];
	supressed = new int*[n];
	
	for(int i = 0; i < n; i++){
		LX[i] = new double[m];
		LY[i] = new double[m];
		mag[i] = new double[m];
		ang[i] = new double[m];
		supressed[i] = new int[m];
	}
	
	for(int i = 1; i < n-1; i++){
		for(int j = 1; j < m-1; j++){
		
			LX[i][j] = LY[i][j] = 0;
			
			if(i>1 && i<n-1)
				LX[i][j] = -2 * img.pixel(i-1,j) - img.pixel(i-1,j-1) - img.pixel(i-1,j+1)
						   +2 * img.pixel(i+1,j) + img.pixel(i+1,j-1) + img.pixel(i+1,j+1);
					
			else if(i == 0)
				LX[i][j] = img.pixel(i+1,j) - img.pixel(i,j);
			else if(i == n-1)
				LX[i][j] = img.pixel(i,j) - img.pixel(i-1,j);
				
			if(j>1 && j<m-1)
				LY[i][j] = -2 * img.pixel(i,j-1) - img.pixel(i-1,j-1) - img.pixel(i+1,j-1)
						   +2 * img.pixel(i,j+1) + img.pixel(i-1,j+1) + img.pixel(i+1,j+1);
			else if(j == 0)
				LX[i][j] = img.pixel(i,j+1) - img.pixel(i,j);
			else if(j == m-1)
				LX[i][j] = img.pixel(i,j) - img.pixel(i,j-1);	
				
			mag[i][j] = sqrt(LX[i][j]*LX[i][j] + LY[i][j]*LY[i][j]);
			ang[i][j] = angle_from_two(LY[i][j], LX[i][j]);
			
			//czy spelnione non-maximum suppression?
		}
	}
}

void Gradient::suppress(){
	std::stack<std::pair<int,int> >edges;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			supressed[i][j] = 0;
			int I,J;
			for(int x = -R; x <= R; x++){
				for(int y = -R; y <= R; y++){
					I = i+x; J = j+y;
					if((x==0 && y==0) || I < 0 || I >= n || J < 0 || J>=m) continue;
					
					if(corners_on_different_sides(x,y,LX[i][j],LY[i][j]) ||
					   corners_on_different_sides(x,y,-LX[i][j],-LY[i][j])){
						if(mag[I][J] > mag[i][j] && clos(ang[i][j],ang[I][J],ep1)){
							supressed[i][j] = 1;
							break;
						}
					} 
				}
			}
			if(supressed[i][j]!=1 && mag[i][j] < high_threshold){
				supressed[i][j] = 2;
				out.pixel(i,j) = 0;
				continue;
			}
			if(!supressed[i][j]){
				out.pixel(i,j) = 100;
				edges.push(std::make_pair(i,j));
			} else out.pixel(i,j) = 0;
			
	 	}
	}
	int I,J;
	int i,j;
	
	while(!edges.empty()){
		i = edges.top().first;
		j = edges.top().second;
		edges.pop();
		
		for(int x = -thresh_ray; x <= thresh_ray; x++){
			for(int y = -thresh_ray; y <= thresh_ray; y++){
				I = i+x; J = j+y;
				if((x==0 && y==0) || I < 0 || I >= n || J < 0 || J>=m) continue;
				if(supressed[I][J]!=2) continue;
				
				if(corners_on_different_sides(x,y,LY[i][j],-LX[i][j]) ||
				   corners_on_different_sides(x,y,-LY[i][j],LX[i][j])){
					if(mag[I][J] > low_threshold && abs(ang[i][j]-ang[I][J]) < ep2){
						supressed[I][J] = 0;
						out.pixel(I,J) = 140;
						edges.push(std::make_pair(I,J));
					}
				} 
			}
		}	
	}
}

void Gradient::union_find_join(){
	p = new int[n*m];
	for(int i = 0; i < n*m; i++) p[i] = i;
	//laczymy prostopadle
	
	detector.G.resize(n*m);
	
	int clx, cly; int dist, I,J;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(supressed[i][j]) continue;
			dist = 10000000.;
			for(int x = -union_ray; x <= union_ray; x++){
			for(int y = -union_ray; y <= union_ray; y++){
				I = i+x; J = j+y;
				if((x==0 && y==0) || I < 0 || I >= n || J < 0 || J>=m) continue;
				if(supressed[I][J]) continue;
				//prostopadle
				if(corners_on_different_sides(x,y,-LY[i][j],LX[i][j]) ||
				   corners_on_different_sides(x,y,LY[i][j],-LX[i][j])){
				   
				   if(x*x+y*y < dist){
				   	   dist = x*x+y*y; clx=I;cly=J;
				   }
				   if(clos(ang[i][j],ang[I][J],ep3)){
					   Union(i*m+j, I*m+J);
				   }
				} 
			}
		}	
		}
	}
}

void Gradient::assign_colors(){
	if(print_color){
		r = image(img);
		g = image(img);
		b = image(img);
		col = new int[n*m];
	}
	
	for(int i = 0; i < n*m; i++){
		ile[i] = 0;
		fx = i/m;
		fy = i%m;
		if(!supressed[fx][fy] && p[i] == i) {
			if(print_color){
				col[i] = cc+40; cc = (cc+20)%200;
				r.pixel(fx,fy) = rand()%256;
				g.pixel(fx,fy) = rand()%256;
				b.pixel(fx,fy) = rand()%256;
			}
			compM[i]=scc;
			scc++;
		}
		else{
			if(print_color){
				r.pixel(fx,fy) = 0;
				g.pixel(fx,fy) = 0;
				b.pixel(fx,fy) = 0;
			}
			compM[i] = -1;
		}
	}
}

void Gradient::read_params(){
	//to do zmiany, sciezka
	FILE *params = fopen("../src/edge-detection/params.conf", "r");
	char name[20]={0}; 
	double ep1, ep2, ep3, sigma;
	bool print_color, do_matching;
	int union_ray, thresh_ray;
	while(fscanf(params, "%s", name)!=EOF){
		if(strcmp(name,"ep1")==0) fscanf(params,"%lf", &ep1);
		if(strcmp(name,"ep2")==0) fscanf(params,"%lf", &ep2);
		if(strcmp(name,"ep3")==0) fscanf(params,"%lf", &ep3);
		if(strcmp(name,"print_color")==0) { int v; fscanf(params,"%d", &v); print_color=(bool)v;}
		if(strcmp(name,"union_ray")==0) fscanf(params,"%d", &union_ray);
		if(strcmp(name,"thresh_ray")==0) fscanf(params,"%d", &thresh_ray);
		if(strcmp(name,"gaussian_sigma")==0) fscanf(params,"%lf", &sigma);
		if(strcmp(name,"do_matching")==0) { int v; fscanf(params,"%d", &v); do_matching=(bool)v;}
	}
	fclose(params);
}

image Gradient::gradient(const image& img1, int high_threshold, int low_threshold, int supp_radius, int kto){
	
	R = supp_radius;
	n = img1.width();
	m = img1.height();
	this->high_threshold = high_threshold;
	this->low_threshold = low_threshold;
	
	//image img = sharpen(gaussian(img1,sigma));
	img = gaussian(img1,sigma);
	const char *pp = "../output/edge-detection/magnified.pgm";
	if(!exists(boost::filesystem::path(pp)))	
	pgm_export(img, boost::filesystem::path(pp));
	
	out = image(img);
	
	compute_gradients();
	suppress();
	union_find_join();
	
	
	int cc = 0;
	int ile[n*m], scc=0;
	srand(time(NULL));
	compM = new int[n*m];
	int father,fx,fy,ktos,y;
	
	
	
	compound.resize(scc);
	std::vector<std::pair<int,int> >V;
	for(int i = 0; i < n*m; i++){
		ile[Find(i)]++;
	}
	
	for(int i = 0; i < n*m; i++) if(p[i]==i){
		V.push_back(std::make_pair(ile[i],i));
	}
	std::sort(V.begin(), V.end());
	std::reverse(V.begin(), V.end());
	
	for(int i = 0; i < 40 && i < V.size(); i++) printf("%d ", V[i].first);
	printf("\n");
	
	//TEST
	int ff;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			ff = compM[Find(i*m+j)];
			if(ff==-1) continue;
			compound[ff].X.push_back(i);
			compound[ff].Y.push_back(j);
			compound[ff].ind.push_back(i*m+j);
			compound[ff].mapa[i*m+j] = compound[ff].n;
			compound[ff].n++;
		}
	}
	
	for(int i = 0; i < scc; i++)
		compound[i].graf.resize(compound[i].n);
	
	
	for(int hh = 0; hh < scc; hh++)	
		for(int i = 0; i < compound[hh].n; i++){
			int x = compound[hh].ind[i];
			for(int j = 0; j < detector.G[x].size(); j++){
				int y = detector.G[x][j];
				compound[hh].graf[i].push_back(compound[hh].mapa[y]);
			}
		}
	
	/*image imgC[5];
	for(int i = 0; i < 5; i++) imgC[i] = compound[compM[V[i].second]].print_me();
	for(int i = 0; i < 5; i++){
		char path[100];
		sprintf(path, "../output/edge-detection/comp%d_%d_%d_%d_%d.pgm\n",
			high_threshold, low_threshold, supp_radius, kto, i);
		pgm_export(imgC[i], boost::filesystem::path(path));
	}*/
	
	
	char sciezka[100];
	sprintf(sciezka, "../output/edge-detection/scc%d_%d_%d_%d_%d.ppm\n",
			high_threshold, low_threshold, supp_radius, kto, 0);
	if(print_color)
		print_compounds(0,sciezka);
	
	int mode;
	if(do_matching) mode = 0;
	else mode = 1;
	
	for(int i = 0; i < scc; i++)
		compound[i].join_furthest(mode);
	
	if(do_matching) join_by_matching(compound);
	//laczenie!
	//redukcja kosztu - wersja "light"
	
	sprintf(sciezka, "../output/edge-detection/scc%d_%d_%d_%d_%d.ppm\n",
			high_threshold, low_threshold, supp_radius, kto, 1);
	if(print_color)
		print_compounds(1,sciezka);
	
	/*
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			//out.pixel(i,j) = 0;
			if(print_color){
				r.pixel(i,j) = 0;
				g.pixel(i,j) = 0;
				b.pixel(i,j) = 0;
			}
			if(!supressed[i][j]){
				if(print_color){
					father = Find(i*m+j);
					fx = father/m;
					fy = father%m;
					r.pixel(i,j) = r.pixel(fx,fy);
					g.pixel(i,j) = g.pixel(fx,fy);
					b.pixel(i,j) = b.pixel(fx,fy);
				}
				if(Find(i*m+j)==V[kto].second)  out.pixel(i,j) = 255;
			}
				//out.pixel(i,j) = col[Find(i*m+j)];
		}
	}*/
	/*image lalala = compound[compM[V[0].second]].print_me();
	char compo[100];
	sprintf(compo, "../output/edge-detection/comp%d_%d_%d_%d.pgm\n",
		high_threshold, low_threshold, supp_radius, kto);
	pgm_export(lalala, boost::filesystem::path(compo));*/
	
	return out;
	//return res;
}

void Gradient::print_compounds(int mode, char *path)
{	
	int n = r.width();
	int m = r.height();
	int fx,fy,ktos,y;
	int scc = compound.size();
	
	if(mode==0)
	for(int i = 0; i < n*m; i++) if(p[i] == i){
		ktos = compM[i];
		fx = i/m;
		fy = i%m;
		compound[ktos].cR = r.pixel(fx,fy);
		compound[ktos].cG = g.pixel(fx,fy);
		compound[ktos].cB = b.pixel(fx,fy);
	}
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++){
			r.pixel(i,j)=0;
			g.pixel(i,j)=0;
			b.pixel(i,j)=0;
		}
	
	for(int i = 0; i < scc; i++){
	//		compound[i].deforest_me();
		//backward
		printf("%d ", compound[i].cR);
		for(int x = 0; x < compound[i].n; x++){
			r.pixel(compound[i].X[x], compound[i].Y[x]) = compound[i].cR;
			g.pixel(compound[i].X[x], compound[i].Y[x]) = compound[i].cG;
			b.pixel(compound[i].X[x], compound[i].Y[x]) = compound[i].cB;
		
			int q = compound[i].graf[x].size();
			for(int j = 0; j < q; j++){
				y = compound[i].graf[x][j];
				join(compound[i].X[x], compound[i].Y[x],
					 compound[i].X[y], compound[i].Y[y],
					 r,compound[i].cR);
				join(compound[i].X[x], compound[i].Y[x],
					 compound[i].X[y], compound[i].Y[y],
					 g,compound[i].cG);
				join(compound[i].X[x], compound[i].Y[x],
					 compound[i].X[y], compound[i].Y[y],
					 b,compound[i].cB);	 
			}
		}
	}
		/*printf("Exporting color image to output/edge-detection/scc%d_%d_%d_%d.ppm\n",
			high_threshold, low_threshold, supp_radius, kto);*/
		//char sciezka[1000];
		/*sprintf(sciezka, "../output/edge-detection/scc%d_%d_%d_%d_%d.ppm\n",
			high_threshold, low_threshold, supp_radius, kto, mode);*/
	ppm_export(r,g,b, boost::filesystem::path(path));
}

