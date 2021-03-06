#include <cstdio>
#include "graph.hpp"

graph::graph(){}

int graph::parse_num(char * num){
	return 0;
}

void graph::load_graph(char * path){
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
    int id,x,y,z,a;
    char * num;
    while(fscanf(file, "%c", &part[l])!=EOF){
    
    	//printf("%c", part[l]);
        if(part[l-1] == 'n' && part[l-2] == '<'){
        	printf("%s", part);
            while(fscanf(file, "%c", &part[l])!=EOF){
                l++;
                //printf("%c", part[l]);
                if(part[l-1] == 'd' && part[l-2] == 'i'){
                    fscanf(file, "%c", &part[l]);
                    printf("
                    scanf("%s", num);
		            printf("wczytalem %s\n", num);
		            a = parse_num(num);
                    printf("wczytalem %d\n", a);
                }
            }
            //wczytaj wspolrzedne
            for(int j = 0; j < 3; j++){
		        while(fscanf(file, "%c", &part[l])!=EOF){
		            l++;
		            if(part[l-1] != ' '){
		                scanf("%s", num);
		                printf("wczytalem %s\n", num);
		                a = parse_num(num);
				        if(part[l-1] == 'x') x = a;
				        else if(part[l-1] == 'y') y = a;
				        else z = a;
				    }
		        }
            }
        }
        
        l++;
    }
    while(fscanf(file, "%c", &part[l])!=EOF) l++;
    return;
}

int main(int argc, char *argv[]){
	graph graf;
	printf("%s\n", argv[1]);
	graf.load_graph(argv[1]);
}

