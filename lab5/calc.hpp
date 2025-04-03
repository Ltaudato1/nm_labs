#pragma once

#include <vector>

using std::vector;
using std::pair;

vector<pair<long double, long double>> runge_cutta4(long double (*equation) (long double, long double), long double startCondition, long double leftBound, long double rightBound, int partitions);