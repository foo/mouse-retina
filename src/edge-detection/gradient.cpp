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

double angle_from_two(double x, double y){
  if(iszero(x) && iszero(y)) return 0;
  return atan2(y,x);
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

struct union_find
{
  int p[1000000];

  int Find(int x){
    if(p[x] == x) return x;
    p[x] = Find(p[x]);
    return p[x];
  }

  bool Union(int x, int y){
    if(Find(x) == Find(y)) return false;
    p[p[x]] = p[y];
    return true;
  }

  bool OwnRank(int x) const
  {
    return p[x] == x;
  }
};


void print_compounds(std::vector<Compound>&compound, int mode, char *path, image &r, image &g, image &b, int *compM, const union_find& det_unionfind);

inline int min(int a, int b){
  if(a < b) return a; return b;
}

inline int max(int a, int b){
  if(a > b) return a; return b;
}

void join(int x1,int y1,int x2,int y2,image& out, int color){
  if(x1 > x2){ std::swap(x1,x2); std::swap(y1,y2);}
  if(x1 != x2){
    for(int x = 1; x < x2-x1; x++){
      int y = (int)(y1 + x*(double)(y2-y1)/(double)(x2-x1));
      if(out.pixel(x1+x,y)==0) out.pixel(x1+x,y) = color;
    }
  }
  else for(int y = min(y1,y2)+1; y < max(y1,y2); y++)
         if(out.pixel(x1,y)==0) out.pixel(x1,y) = color;
}

image detect_edges(const image& img1, int high_threshold, int low_threshold, int supp_radius, int kto,
               float ep1, float ep2, float ep3, float sigma, bool print_color, bool do_matching,
               int union_ray, int thresh_ray)
{
  int R = supp_radius;
  int n = img1.width();
  int m = img1.height();

  union_find det_unionfind;

  gradient gradients[n][m];
  int supressed[n][m];

  image img = gaussian(img1,sigma);
  const char *pp = "../output/edge-detection/magnified.pgm";
  if(!exists(boost::filesystem::path(pp)))
    pgm_export(img, boost::filesystem::path(pp));

  for(int i = 1; i < n-1; i++){
    for(int j = 1; j < m-1; j++){
      std::pair<float, float> gradient_vector = sobel_vector(img, i, j);
      float y = gradient_vector.first;
      float x = gradient_vector.second;
      gradients[i][j].x = x;
      gradients[i][j].y = y;
      gradients[i][j].mag = sqrt(x*x + y*y);
      gradients[i][j].angle = angle_from_two(y, x);

      //czy spelnione non-maximum suppression?
    }
  }

  image out(img);
  std::stack<std::pair<int,int> >edges;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      supressed[i][j] = 0;

      gradient g = gradients[i][j];
      for(int x = -R; x <= R; x++){
        for(int y = -R; y <= R; y++){
          if((x==0 && y==0) || !img.is_inside(i+x, j+y))
	    continue;

	  gradient g_translated = gradients[i+x][j+y];
	  
          if(corners_on_different_sides(x, y, g.x, g.y) ||
             corners_on_different_sides(x, y, -g.x, -g.y)) {
            if(g_translated.mag > g.mag && clos(g.angle, g_translated.angle, ep1)){
              supressed[i][j] = 1;
              break;
            }
          }
        }
      }
      if(supressed[i][j] != 1 && g.mag < high_threshold){
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
  while(!edges.empty()){
    int i = edges.top().first;
    int j = edges.top().second;
    edges.pop();

    gradient g = gradients[i][j];

    for(int x = -thresh_ray; x <= thresh_ray; x++){
      for(int y = -thresh_ray; y <= thresh_ray; y++){
        int I = i+x;
	int J = j+y;
        if((x==0 && y==0) || !img.is_inside(I, J)) continue;
        if(supressed[I][J]!=2) continue;

	gradient g_translated = gradients[I][J];

        if(corners_on_different_sides(x, y, g.y, -g.x) ||
           corners_on_different_sides(x, y, -g.y,g.x)){
          if(g_translated.mag > low_threshold && abs(g.angle-g_translated.angle) < ep2){
            supressed[I][J] = 0;
            out.pixel(I,J) = 140;
            edges.push(std::make_pair(I,J));
          }
        }
      }
    }
  }
  for(int i = 0; i < n*m; i++) det_unionfind.p[i] = i;
  //laczymy prostopadle

  Detector detector;
  detector.G.resize(n*m);

  int clx, cly; int dist;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(supressed[i][j]) continue;
      dist = 10000000.;
      for(int x = -union_ray; x <= union_ray; x++){
        for(int y = -union_ray; y <= union_ray; y++){
          int I = i+x;
	  int J = j+y;
          if((x==0 && y==0) || I < 0 || I >= n || J < 0 || J>=m) continue;
          if(supressed[I][J]) continue;
          //prostopadle
          if(corners_on_different_sides(x,y,-gradients[i][j].y,gradients[i][j].x) ||
             corners_on_different_sides(x,y,gradients[i][j].y,-gradients[i][j].x)){

            if(x*x+y*y < dist){
              dist = x*x+y*y; clx=I;cly=J;
            }
            if(clos(gradients[i][j].angle,gradients[I][J].angle,ep3)){
              if(det_unionfind.Union(i*m+j, I*m+J))
		{
	        detector.G[i*m+j].push_back(I*m+J);
		detector.G[I*m+J].push_back(i*m+j);
		}
            }
          }
        }
      }
    }
  }

  int cc = 0;
  int ile[n*m], scc=0;
  int compM[n*m];
  int father,fx,fy,ktos,y;

  image r,g,b;
  if(print_color){
    r = image(img);
    g = image(img);
    b = image(img);
  }

  for(int i = 0; i < n*m; i++){
    ile[i] = 0;
    fx = i/m;
    fy = i%m;
    if(!supressed[fx][fy] && det_unionfind.p[i] == i) {
      if(print_color){
        cc = (cc+20)%200;
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
  std::vector<Compound>compound(scc);
  std::vector<std::pair<int,int> >V;
  for(int i = 0; i < n*m; i++){
    ile[det_unionfind.Find(i)]++;
  }

  for(int i = 0; i < n*m; i++) if(det_unionfind.p[i]==i){
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
      ff = compM[det_unionfind.Find(i*m+j)];
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

  char sciezka[100];
  sprintf(sciezka, "../output/edge-detection/scc%d_%d_%d_%d_%d.ppm\n",
          high_threshold, low_threshold, supp_radius, kto, 0);
  if(print_color)
    print_compounds(compound,0,sciezka,r,g,b,compM, det_unionfind);

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
    print_compounds(compound,1,sciezka,r,g,b,compM, det_unionfind);

  return out;
}

void print_compounds(std::vector<Compound>&compound, int mode, char *path, image &r, image &g, image &b, int *compM, const union_find& det_unionfind)
{
  int n = r.width();
  int m = r.height();
  int fx,fy,ktos,y;
  int scc = compound.size();

  if(mode==0)
    for(int i = 0; i < n*m; i++) if(det_unionfind.p[i] == i){
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
  ppm_export(r,g,b, boost::filesystem::path(path));
}
