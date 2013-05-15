#include "skeleton_simplifier.hpp"

void simplifier::dfs(int x, graph * pgraf){
    visited[x] = 1;
    int y, q = pgraf->G[x].size();
    for(int i = 0; i < q; i++){
        y = pgraf->G[x][i];
        if(visited[y] == 0){
            father[y] = x;
            dfs(y, pgraf);
        }
    }
    
    if(father[x] != -1 && pgraf->G[x].size() == 1){
        y = pgraf->G[x][0];
        if(geom.are_close(pgraf->P[father[x]], pgraf->P[y], pgraf->P[x]))
            toconsume[y] = 1;
    }
}
    
//zwraca indeks x w nowym grafie
int simplifier::build_new(int x, graph * pgraf){
    
    int y, q = pgraf->G[x].size(), ind, myind;
    myind = newgraf.P.size();
    newgraf.P.push_back(pgraf->P[x]);
    newgraf.G.push_back(std::vector<int>(0));
    for(int i = 0; i < q; i++){
        y = pgraf->G[x][i];
        int consume_counter = 0;
        while(toconsume[y] && consume_counter < CONSUME_PARAM){
            y = pgraf->G[y][0];
            consume_counter++;
        }
        ind = build_new(y, pgraf);
        newgraf.G[myind].pb(ind);
    }
    
    return myind;
}
    
graph simplifier::simplify(graph graf){
    CONSUME_PARAM = 5;
    int n = graf.P.size();
    //newgraf = new graph;
    //geom = new geometry;
    visited.resize(n);
    toconsume.resize(n);
    father.resize(n);
    
    for(int i = 0; i < n; i++){
        visited[i] = 0;
        toconsume[i] = 0;
        father[i] = -1;
    }
    
    dfs(0, &graf);
    build_new(0, &graf);
    
    return newgraf;
}

graph::graph(){}

void graph::load_graph(char * path){
    /*
    FILE * file;
    file = fopen(path, "r");
    
    this->filepath = path;
    char prop[7]={'<','n','o','d','e','s','>'};
    char edg[8] = {'<','/','e','d','g','e','s','>'};
    char * part = (char *) calloc(100000, sizeof(char));
    int l = 0;
    while(fscanf(file, "%c", &part[l])!=EOF){
        l++;
        if(l >= 7){
            int found = 1;
            int i;
            for(i = 1; i <= 7; i++){
                if(part[l-i] != prop[7-i]){
                    found = 0;
                    break;
                }
            }
            if(found==1) break;
        }
    }
    l = 0;
    int id,x,y,z;
    while(fscanf(file, "%c", &part[l])!=EOF){
        l++;
        if(part[l-1] == 'n' && part[l-2] == '<'){
            while(fscanf(file, "%c", &part[l])!=EOF){
                l++;
                if(part[l-1] == 'd' && part[l-2] == 'i'){
                    fscanf(file, "%c", &part[l]);
                    scanf("%d", &id);
                    printf("wczytalem %d\n", id);
                }
            }
        }
    }
    while(fscanf(file, "%c", &end_part[l])!=EOF) l++;
    return;*/
}

int main(){
}
