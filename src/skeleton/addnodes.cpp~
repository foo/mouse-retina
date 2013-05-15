#include <cstdio>
#include <cstring>

#define REP(i,a,b) for(i=a; i<b; i++)
#define DOWN(i,a,b) for(int i=a; i>=b; i--)
#define mp make_pair
#define pb push_back
#define ft first
#define sd second

int n, m, a ,b, c, q,w,r,t;
double x,y,z;
struct point{
    double x,y,z;
};
struct edge{
    int begin, end;
};

struct point P[100];
struct edge E[100];

char path[1000];

void strip_path(char * path, char * beg_part, char * end_part){
    FILE * file;
    file = fopen(path, "r");
    
    char prop[7]={'<','n','o','d','e','s','>'};
    char edg[8] = {'<','/','e','d','g','e','s','>'};
    char * inn_part = (char *) calloc(10000, sizeof(char));
    int l = 0;
    while(fscanf(file, "%c", &beg_part[l])!=EOF){
        l++;
        if(l >= 7){
            int found = 1;
            int i;
            for(i = 1; i <= 7; i++){
                if(beg_part[l-i] != prop[7-i]){
                    found = 0;
                    break;
                }
            }
            if(found==1) break;
        }
    }
    l = 0;
    while(fscanf(file, "%c", &inn_part[l])!=EOF){
        l++;
        if(l >= 8){
            int found = 1;
            int i;
            for(i = 1; i <= 8; i++){
                if(inn_part[l-i] != edg[8-i]){
                    found = 0;
                    break;
                }
            }
            if(found==1){
                l = 8;
                for(i = 0; i < 8; i++) end_part[i] = edg[i];
                break;
            }
        }
    }
    
    while(fscanf(file, "%c", &end_part[l])!=EOF) l++;
    return;
}

int main(){
    int i;
    scanf("%s", path);
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%lf%lf%lf", &x,&y,&z);
        P[i].x = x; P[i].y = y; P[i].z = z;
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        scanf("%d%d", &a,&b);
        E[i].begin = a; E[i].end = b;
    }
    char * beg_part, * end_part;    
    beg_part = (char *) calloc(10000, sizeof(char));
    end_part = (char *) calloc(10000, sizeof(char));
    strip_path(path, beg_part, end_part);
    
    printf("%s", beg_part);
    for(int i = 0; i < n; i++){
        printf("        <node id=\"%d\" radius=\"10.000\" x=\"%lf\" y=\"%lf\" z=\"%lf\" inVp=\"2\" inMag=\"1\" time=\"%d\"/>\n", i+1, P[i].x, P[i].y, P[i].z, 120000+rand()%1000);
    }
    printf("</nodes>\n<edges>\n");
 
    for(int i = 0; i < m; i++){
        a = E[i].begin+1;
        b = E[i].end+1;
        printf("        <edge source=\"%d\" target=\"%d\"/>\n", a,b); 
    }
    printf("%s", end_part); 
}
