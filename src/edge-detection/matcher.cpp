#include "matcher.hpp"

void join_by_matching(std::vector<Compound>&C){
	int **w = prepare_table(C);
	int n = 2*C.size(),a,b;
	std::vector<int>match = matching(n,w);
	std::queue<int>Q;
	bool odw[n]; for(int i = 0; i < n; i++) odw[i]=0;
	std::vector<Compound>N;	
	
	//najlpierw sprobujmy sam kolor
	for(int i = 0; i < n; i+=2){
		if(odw[i]) continue;
		Q.push(i); Q.push(i+1);
		odw[i] = true; odw[i+1] = true;
		int colR = C[i/2].cR;
		int colG = C[i/2].cG;
		int colB = C[i/2].cB;
		
		
		while(!Q.empty()){
			a = Q.front();
			Q.pop();
			C[a/2].cR = colR;
			C[a/2].cG = colG;
			C[a/2].cB = colB;
			
			b = match[a];
			if(!odw[b]){
				Q.push(b);
				odw[b] = true;
			}
			if(b%2==0) b++; else b--;
			if(!odw[b]){
				Q.push(b);
				odw[b] = true;
			}
		}
		
	}
	for(int i=0; i<n; i++) delete w[i];
	delete []w;
}

int** prepare_table(std::vector<Compound>&C){
	int n = 2*C.size();
	int **w = new int*[n];
	int a,b;
	for(int i = 0; i < n ; i++) w[i] = new int[n];
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			if(i==j){ w[i][j] = -1000000; continue;}
			//poki co kwadrat...
			a = C[i/2].ends[i%2];
			b = C[j/2].ends[j%2];
			w[i][j] = (C[i/2].X[a]-C[j/2].X[b])*(C[i/2].X[a]-C[j/2].X[b]) +
					  (C[i/2].Y[a]-C[j/2].Y[b])*(C[i/2].Y[a]-C[j/2].Y[b]);
			w[i][j] = -w[i][j];
			//modyfikacja z doopy:D
			if(i/2==j/2) w[i][j]/=2;
		}
	return w;
}

std::vector<int> matching(int n, int **w){
//Najdroższe skojarzenie w grafie dwudzielnym - algorytm węgierski

	printf("HUNGARY!!!!\n");
	int INF = -1000000000;
    int lx[n], ly[n], skojx[n], skojy[n];
    int markx[n], marky[n], sl[n], par[n], q[n];
    for(int i=0;i<n;i++){
        skojx[i] = skojy[i] = -1;
        ly[i] = 0;
        lx[i] = *std::max_element(w[i], w[i]+n);    
    }
    for(int k=0;k<n;k++){
        int v = -1, qb =0, qe = 0;
        for(int i=0;i<n;i++){
            marky[i]=markx[i] = 0;
            sl[i]=-1;
            if(skojx[i]==-1) q[qe++] = i;    
        }
        while(v==-1){
            while(qb<qe){
                int i = q[qb++];
                markx[i]=1;
                for(int j=0;j<n;j++)
                if(!marky[j] && 
                (sl[j]==-1 || sl[j]> lx[i] + ly[j] - w[i][j])){
                        if((sl[j] = lx[par[j]=i] + ly[j] - w[i][j]) ==0){
                            marky[j]=1;
                            if(skojy[j]!=-1) q[qe++]= skojy[j];
                            else{
                                    v = j;
                                    goto end;
                            }
                            
                        }
                }
            }
            int x = -1;
            for(int i=0;i<n;i++)
                if(!marky[i] && (x==-1 || sl[i] < x)) x = sl[i];
            for(int i=0;i<n;i++){
                if(markx[i]) lx[i]-=x;
                if(marky[i]) ly[i]+=x;
                else if((sl[i]-=x) ==0 ){
                        marky[i]=1;
                        if(skojy[i]!=-1) q[qe++] = skojy[i];
                        else v = i;
                }
            } 
        }
        end:
        while(v!=-1){
          int y = skojx[par[v]];
          skojx[par[v]]=v;
          skojy[v] = par[v];
          v=y;
        }  
    }
    for(int u = 0; u < n; u++) printf("%d ", skojx[u]);
    printf("\n");
    return std::vector<int>(skojx, skojx+n);
}

