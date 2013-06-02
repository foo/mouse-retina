#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>
#include "compound.hpp"

void join_by_matching(std::vector<Compound>&C);
int** prepare_table(std::vector<Compound>&C);
std::vector<int>matching(int n,int **w);
