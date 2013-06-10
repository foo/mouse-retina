#include "edge-detection.hpp"


bool is_zero(float x)
{
  float eps = 0.0000001f;
  return x < eps && x > -eps;
}

double angle_from_two(double x, double y){
  if(is_zero(x) && is_zero(y)) return 0;
  return atan2(y,x);
}

bool inline clos(double a, double b, double ep)
{
  float pi = 3.14159265358979323846264;
  if(abs(a-b) < ep || abs(a-b-2*pi) < ep || abs(a-b+2*pi) < ep) return true;
  return false;
}

bool corners_on_different_sides(int Sx, int Sy, double Gx, double Gy){
  //czy rogi kwadraciku o srodku w S sa po dwoch stronach wektora do G?
  return (((Sx+0.5)*Gy - (Sy+0.5)*Gx) * ((Sx-0.5)*Gy - (Sy-0.5)*Gx) < 0 ||
          ((Sx+0.5)*Gy - (Sy-0.5)*Gx) * ((Sx-0.5)*Gy - (Sy+0.5)*Gx) < 0 );
}


rgb_image color_compounds(std::vector<Compound>&compound, int mode, image &r, image &g, image &b, int *compM, const union_find& det_unionfind, bool print_compounds);

void join(int x1,int y1,int x2,int y2,image& out, int color){
  if(x1 > x2){ std::swap(x1,x2); std::swap(y1,y2);}
  if(x1 != x2){
    for(int x = 1; x < x2-x1; x++){
      int y = (int)(y1 + x*(double)(y2-y1)/(double)(x2-x1));
      if(out.pixel(x1+x,y)==0) out.pixel(x1+x,y) = color;
    }
  }
  else for(int y = std::min(y1,y2)+1; y < std::max(y1,y2); y++)
         if(out.pixel(x1,y)==0) out.pixel(x1,y) = color;
}

std::tuple<image, rgb_image, rgb_image>
detect_edges(const image& img, int high_threshold, int low_threshold, int supp_radius, int kto,
             float ep1, float ep2, float ep3, bool print_compounds, bool do_matching,
             int union_ray, int thresh_ray)
{
  int R = supp_radius;
  int n = img.width();
  int m = img.height();

  union_find det_unionfind(n * m);

  gradient gradients[n][m];
  int supressed[n][m];

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
  //laczymy prostopadle

  Detector detector;
  detector.G.resize(n*m);

  int clx, cly; int dist;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(supressed[i][j]) continue;
      dist = INT_MAX;
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
  r = image(img);
  g = image(img);
  b = image(img);

  for(int i = 0; i < n*m; i++){
    ile[i] = 0;
    fx = i/m;
    fy = i%m;
    if(!supressed[fx][fy] && det_unionfind.OwnRank(i)) {
      cc = (cc+20)%200;
      r.pixel(fx,fy) = rand()%256;
      g.pixel(fx,fy) = rand()%256;
      b.pixel(fx,fy) = rand()%256;
      compM[i]=scc;
      scc++;
    }
    else{
      r.pixel(fx,fy) = 0;
      g.pixel(fx,fy) = 0;
      b.pixel(fx,fy) = 0;
      compM[i] = -1;
    }
  }
  std::vector<Compound>compound(scc);
  std::vector<std::pair<int,int> >V;
  for(int i = 0; i < n*m; i++){
    ile[det_unionfind.Find(i)]++;
  }

  for(int i = 0; i < n*m; i++) if(det_unionfind.OwnRank(i)){
      V.push_back(std::make_pair(ile[i],i));
    }
  std::sort(V.begin(), V.end());
  std::reverse(V.begin(), V.end());

  if(print_compounds)
    {
      for(int i = 0; i < 40 && i < V.size(); i++) printf("%d ", V[i].first);
      printf("\n");
    }
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

  rgb_image img_before_join = color_compounds(compound,0,r,g,b,compM, det_unionfind, print_compounds);

  int mode;
  if(do_matching) mode = 0;
  else mode = 1;

  for(int i = 0; i < scc; i++)
    compound[i].join_furthest(mode);

  if(do_matching) join_by_matching(compound);
  //laczenie!
  //redukcja kosztu - wersja "light"

  rgb_image img_after_join = color_compounds(compound,1,r,g,b,compM, det_unionfind, print_compounds);
  return std::make_tuple(out, img_before_join, img_after_join);
}

rgb_image color_compounds(std::vector<Compound>&compound, int mode, image &r, image &g, image &b, int *compM, const union_find& det_unionfind, bool print_compounds)
{
  int n = r.width();
  int m = r.height();
  int fx,fy,ktos,y;
  int scc = compound.size();

  if(mode==0)
    for(int i = 0; i < n*m; i++) if(det_unionfind.OwnRank(i)){
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
    if(print_compounds)
      {
        // backward
        std::cout << compound[i].cR << " ";
      }
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
  return std::make_tuple(r, g, b);
}
