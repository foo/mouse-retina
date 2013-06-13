#include "compound.hpp"

Compound::Compound(){
	n=0;
}

void joindet(int x1,int y1,int x2,int y2,image& out){
	if(x1 > x2){ std::swap(x1,x2); std::swap(y1,y2);}
	if(x1 != x2){
		for(int x = 1; x < x2-x1; x++){
			int y = (int)(y1 + x*(double)(y2-y1)/(double)(x2-x1));
			if(out.pixel(x1+x,y)==0) out.pixel(x1+x,y) = 255;
		}
	}
	else for(int y = std::min(y1,y2)+1; y < std::max(y1,y2); y++)
			if(out.pixel(x1,y)==0) out.pixel(x1,y) = 255;	
}

void Compound::paint_ball(image &img, int &x, int &y, int R){
	for(int i = -R; i <=R; i++)
		for(int j = -R; j<=R; j++){
			if(i+x<0||i+x>=Xbound||j+y<0||j+y>=Ybound) continue;
			img.pixel(i+x,j+y) = 255;
		}	
}

double Compound::dist(int i, int j){
	return sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]));
}

void Compound::join_furthest(int mode=false){
	std::priority_queue<std::pair<double,int> >Q;
	//zaczynamy od kogokolwiek - dijkstra!!!
	int x,y;
	Q.push(std::make_pair(-0,0));
	bool odw[n]; for(int i = 0; i < n; i++) odw[i] = 0;
	double d;
	int last=0;
	while(!Q.empty()){
		x = Q.top().second;
		d = -Q.top().first;
		Q.pop();
		if(odw[x]) continue;
		odw[x] = 1;
		last = x;
		for(int i = 0; i < graf[x].size(); i++){
			y = graf[x][i]; if(odw[y]) continue;
			//lamerskie liczenie, potrzeba ztablicowac
			Q.push(std::make_pair(-dist(x,y)-d,y));
		}
	}
	//teraz 3z last
	for(int i = 0; i < n; i++) odw[i] = 0;
	int f = last;
	Q.push(std::make_pair(-0,last));
	while(!Q.empty()){
		x = Q.top().second;
		d = -Q.top().first;
		Q.pop();
		if(odw[x]) continue;
		odw[x] = 1;
		last = x;
		for(int i = 0; i < graf[x].size(); i++){
			y = graf[x][i]; if(odw[y]) continue;
			Q.push(std::make_pair(-dist(x,y)-d,y));
		}
	}
	//poki co zakladam ze nie sa polaczone, e.g. graf jest drzewem
	//na czas testowania matchingu nie laczymy
	if(mode==1){
		graf[last].push_back(f);
		graf[f].push_back(last);
	}
	ends[0] = last; ends[1] = f;
}

void Compound::deforest_me(){
	std::queue<int>Q;
	int det[n];
	for(int i = 0; i < n; i++){
		det[i] = graf[i].size();
		//printf("det %d %d\n", i, det[i]); 
		if(det[i]<=1) Q.push(i);
	}
	int x,y;
	while(!Q.empty()){
		x = Q.front();
		Q.pop();
		for(int i = 0; i < graf[x].size(); i++){
			y = graf[x][i];
			det[y]--;
			if(det[y]==1) Q.push(y);
		}
	}
	std::vector<int>ng;
	for(int x = 0; x < n; x++){
		if(det[x] <= 1) graf[x].clear();
		else{
			ng.clear();
			for(int i = 0; i < graf[x].size(); i++){
				y = graf[x][i];
				if(det[y] > 1) ng.push_back(y);
			}
			graf[x] = ng;
		}
	}
}

image Compound::print_me()
{
	int Xmin=1000000, Xmax=0, Ymin=1000000, Ymax=0;
	printf("compound n %d\n", n);
	for(int i = 0; i < n; i++){
		if(X[i] < Xmin) Xmin = X[i];
		if(X[i] > Xmax) Xmax = X[i];
		if(Y[i] < Ymin) Ymin = Y[i];
		if(Y[i] > Ymax) Ymax = Y[i];
	}
	//najpierw same wierzcholki
	//przeskalowanie na Xbound, Ybound
	
	image img;
	img.allocate(Xbound,Ybound);
	for(int i = 0; i < Xbound; i++)
		for(int j = 0; j < Ybound; j++)
			img.pixel(i,j) = 0;
	nX.resize(n);
	nY.resize(n);
	
	for(int i = 0; i < n; i++){
		nX[i] = (int)((double)(X[i]-Xmin)*Xbound/(Xmax-Xmin));
		nY[i] = (int)((double)(Y[i]-Ymin)*Ybound/(Ymax-Ymin));
		if(nX[i]<0) nX[i]=0; if(nY[i]<0) nY[i]=0; 
		if(nX[i]>=Xbound) nX[i]=Xbound-1; if(nY[i]>=Ybound) nY[i]=Ybound-1;
		paint_ball(img,nX[i],nY[i],0);
	}
	
	join_furthest(true);
	deforest_me();
	
	
	for(int i = 0; i < n; i++){
		for(int q = 0; q < graf[i].size(); q++){
			int j = graf[i][q];
			joindet(nX[i],nY[i],nX[j],nY[j],img);
		}
	}
	return img;
}

std::string Compound::print_me_to_string(){
	//compound forms a cycle because it is (due to the way we join points
	//during edge detection) a tree, with one edge added, then deforested
	
	//assert that compound is a cycle
	bool assert_cycle = true;
	for(int i = 0; i < n; i++)
		if(graf[i].size() != 0 && graf[i].size() != 2){
			assert_cycle = false;
			break;
		}
		
	if(assert_cycle == false) 
		return std::string("Error!!! Compound does not form a cycle!");
	
	//look for a vertex on the cycle
	int beg = 0, iter;
	while(beg < n && graf[beg].size() != 2) beg++;
	if(beg == n)
		return std::string("Error!!! All vertices of the compound are isolated!");
	
	bool *odw = new bool[n];
	for(int i = 0; i < n; i++) odw[i] = false;
	iter = beg;
	int left,right;
	std::stringstream ss;
	
	while(true){	
		odw[iter] = true;
		ss << X[iter] << " " << Y[iter] << "  ";
		
		left = graf[iter][0];
		right = graf[iter][1];
		
		if(odw[right] && odw[left]) break;
		if(!odw[left]) iter = left;
		else iter = right;
	}
	//adding the first vertex once again - for boost::geometry polygon syntax
	ss << X[beg] << " " << Y[beg] << "  -1 -1" << std::endl;
	
	delete []odw;
	return ss.str();
}

//zwraca cykle
std::vector<std::vector<std::pair<double,double> > >
	Compound::read_us(std::stringstream &ss){
	
	std::vector<std::vector<std::pair<double,double> > > c;
	
	int num=0, push_new=false;
	double x,y;
	//az do -1 -1
	c.push_back(std::vector<std::pair<double,double> >());
	
	while(ss>>x){
		if(!(ss>>y)) break;
		
		//std::cout << x << " " << y << std::endl;
		if(x==-1 && y==-1){
			//compound ends
			push_new = true;
			num++;
			continue;
		}
		if(push_new){
			c.push_back(std::vector<std::pair<double,double> >());
			push_new = false;
		}
			
		c[num].push_back(std::make_pair(x,y));
	}
	
	std::cout << "Trud skonczony " << std::endl;
	return c;
}


