#pragma once

#include <vector>

using std::vector;
using std::pair;

vector<pair<double, double>> adams4(double (*equation) (double, double), double startCondition, double leftBound, double rightBound, int partitions);
vector<pair<double, double>> runge_cutta4(double (*equation) (double, double), double startCondition, double leftBound, double rightBound, int partitions);