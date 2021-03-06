#pragma once

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include "geometry.hpp"
#include "graph.hpp"

#define REP(i,a,b) for(i=a; i<b; i++)
#define DOWN(i,a,b) for(int i=a; i>=b; i--)
#define mp make_pair
#define pb push_back
#define ft first
#define sd second

class simplifier{
public:
    
    int CONSUME_PARAM;
    std::vector<int>visited;
    std::vector<int>toconsume;
    std::vector<int>father;
    graph newgraf;
    geometry geom;
    
    void dfs(int x, graph * pgraf);
    //zwraca indeks x w nowym grafie
    int build_new(int x, graph * pgraf);
    graph simplify(graph graf);
};
