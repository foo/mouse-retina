#include "gradient.hpp"

Gradient::Gradient(int x_, int y_, double ang_, double mag_){
	x = x_; y = y_; angle = ang_; mag = mag_;
}

double angle_from_two(double x, double y){
	if(iszero(x) && iszero(y)) return 0;
	return atan2(y,x);
    /*if(iszero(x)){
        if(iszero(y)) return 0;
        if(y > 0) return PI/2.;
        else return 2*PI-PI/2.;
    }
    else if(x > 0) return atan2(y,x);
    else if(iszero(y) || y > 0) return atan2(y,x)+PI;
    else return atan2(y,x)-PI;*/
}

bool inline clos(double a, double b, double ep){
	if(abs(a-b) < ep || abs(a-b-2*PI) < ep || abs(a-b+2*PI) < ep) return true;
	return false;
}

bool inline corners_on_different_sides(int &Sx, int &Sy, double Gx, double Gy){
	//czy rogi kwadraciku o srodku w S sa po dwoch stronach wektora do G?
	return (((Sx+0.5)*Gy - (Sy+0.5)*Gx) * ((Sx-0.5)*Gy - (Sy-0.5)*Gx) < 0 ||
	   	    ((Sx+0.5)*Gy - (Sy-0.5)*Gx) * ((Sx-0.5)*Gy - (Sy+0.5)*Gx) < 0 );
}

int p[1000000], col[1000000];

int Find(int x){
	if(p[x] == x) return x;
	p[x] = Find(p[x]);
	return p[x];
}

void Union(int x, int y){
	if(Find(x) == Find(y)) return;
	p[p[x]] = p[y];
}

inline int min(int a, int b){
	if(a < b) return a; return b;
}

inline int max(int a, int b){
	if(a > b) return a; return b;
}

void join(int x1,int y1,int x2,int y2,image& out){
	if(x1 > x2){ std::swap(x1,x2); std::swap(y1,y2);}
	if(x1 != x2){
		for(int x = 1; x < x2-x1; x++){
			int y = (int)(y1 + x*(double)(y2-y1)/(double)(x2-x1));
			if(out.pixel(x1+x,y)==0) out.pixel(x1+x,y) = 255;
		}
	}
	else for(int y = min(y1,y2)+1; y < max(y1,y2); y++)
			if(out.pixel(x1,y)==0) out.pixel(x1,y) = 255;	
}
//testing
//vector<Gradient> gradient(const image& img){
image gradient(const image& img, int high_threshold, int low_threshold, int supp_radius, int kto){
	int R = supp_radius;
	int n = img.width();
	int m = img.height();
	
	double LX[n][m], LY[n][m], mag[n][m], ang[n][m];
	int supressed[n][m];
	
	//for sobel
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
	
	image out(img);
	std::stack<std::pair<int,int> >edges;
	double ep1 = 0.3;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			supressed[i][j] = 0;
			
			int I,J;
			/*int x[2],y[2];
			double a = ang[i][j]; if(a<0) a+=2*PI;
			if		(a>=0 && a<PI/8)         {x[0]=1;y[0]=0;x[1]=-1;y[1]=0;}
			else if (a>=PI/8 && a<PI/4+PI/8)     {x[0]=1;y[0]=1;x[1]=-1;y[1]=-1;}
			else if (a>=PI/4+PI/8 && a<PI/2+PI/8){x[0]=0;y[0]=1;x[1]=0;y[1]=-1;}
			else if (a>=PI/2+PI/8 && a<PI/2+PI/4+PI/8)  {x[0]=-1;y[0]=1;x[1]=1;y[1]=-1;}
			else if (a>=PI/2+PI/4+PI/8 && a<PI+PI/8){x[0]=1;y[0]=0;x[1]=-1;y[1]=0;}
			else if (a>=PI+PI/8 && a<PI+PI/4+PI/8){x[0]=1;y[0]=1;x[1]=-1;y[1]=-1;}
			else if (a>=PI+PI/4+PI/8 && a<PI+PI/2+PI/8){x[0]=0;y[0]=1;x[1]=0;y[1]=-1;}
			else if (a>=PI+PI/2+PI/8 && a<PI+PI/2+PI/4+PI/8){x[0]=-1;y[0]=1;x[1]=1;y[1]=-1;}
			else if (a>=PI+PI/2+PI/4+PI/8 && a < 2*PI) {x[0]=1;y[0]=0;x[1]=-1;y[1]=0;}
			
			//for(int x = -R; x <= R; x++){
			//	for(int y = -R; y <= R; y++){
			for(int u = 0; u < 2; u++){
					I = i+x[u]; J = j+y[u];
					if(I < 0 || I >= n || J < 0 || J>=m) continue;
					
					if(corners_on_different_sides(x[u],y[u],LX[i][j],LY[i][j]) ||
					   corners_on_different_sides(x[u],y[u],-LX[i][j],-LY[i][j])){
						if(mag[I][J] > mag[i][j] && clos(ang[i][j],ang[I][J],ep1)){
							supressed[i][j] = true;
							break;
						}
					} 
				
			}*/
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
			//out.pixel(i,j) = mag[i][j]/2;
			if(!supressed[i][j]){
				//res.push_back(Gradient(i,j,ang[i][j],mag[i][j]));
				out.pixel(i,j) = 100;
				edges.push(std::make_pair(i,j));
			} else out.pixel(i,j) = 0;
			
	 	}
	}
	int I,J;
	int i,j;
	
	double ep2 = 0.1;
	while(!edges.empty()){
		i = edges.top().first;
		j = edges.top().second;
		edges.pop();
		
		for(int x = -1; x <= 1; x++){
			for(int y = -1; y <= 1; y++){
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
	int RR = 3;
	for(int i = 0; i < n*m; i++) p[i] = i;
	//laczymy prostopadle
	
	double ep3 = 0.1;
	int clx, cly; int dist;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(supressed[i][j]) continue;
			dist = 10000000.;
			for(int x = -RR; x <= RR; x++){
			for(int y = -RR; y <= RR; y++){
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
					   //join(i,j,I,J,out);
				   }
				} 
			}
			/*if(dist < 10000000.) 
				if(clos(ang[i][j],ang[clx][cly],ep3)){
					Union(i*m+j, clx*m+cly);
					join(i,j,clx,cly,out);
				}*/
		}	
		}
	}
	
	int cc = 0;
	int ile[n*m];
	
	for(int i = 0; i < n*m; i++){
		ile[i] = 0;
		if(p[i] == i) {col[i] = cc+40; cc = (cc+20)%200;}
	}
	std::vector<std::pair<int,int> >V;
	for(int i = 0; i < n*m; i++){
		ile[Find(i)]++;
	}
	for(int i = 0; i < n*m; i++) if(p[i]==i) V.push_back(std::make_pair(ile[i],i));
	std::sort(V.begin(), V.end());
	std::reverse(V.begin(), V.end());
	for(int i = 0; i < 40 && i < V.size(); i++) printf("%d\n", V[i].first);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			//out.pixel(i,j) = 0;
			if(!supressed[i][j]) 
				if(Find(i*m+j)==V[kto].second)  out.pixel(i,j) = 255;
				//out.pixel(i,j) = col[Find(i*m+j)];
		}
	}
	return out;
	//return res;
}
