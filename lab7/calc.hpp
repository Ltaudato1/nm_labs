#pragma once

#include <vector>

using std::vector;
using std::pair;

vector<pair<double, double>> endDif(double (*p) (double), double (*q) (double), double (*r) (double), double (*f) (double), double leftCond, double rightCond, double leftBound, double rightBound, int partitions);