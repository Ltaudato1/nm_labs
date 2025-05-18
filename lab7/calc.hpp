#pragma once

#include <vector>
#include "functions.hpp"

using std::vector;
using std::pair;

vector<pair<double, double>> solveBVP(
    double (*p) (double),
    double (*q) (double), 
    double (*r) (double), 
    double (*f) (double), 
    borderCond cond,
    int partitions
);