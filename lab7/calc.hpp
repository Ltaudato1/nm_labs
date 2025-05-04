#pragma once

#include <vector>

using std::vector;
using std::pair;

vector<pair<double, double>> solveBVP(
    double (*p) (double),
    double (*q) (double), 
    double (*r) (double), 
    double (*f) (double), 
    double leftBound, 
    double rightBound, 
    double leftCond, 
    double rightCond, 
    int partitions
);