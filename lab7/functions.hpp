#pragma once
#include <functional>

double equation(double x, double y);
double answer(double x);

using std::function;

double f(double x);
double p(double q);
double q(double x);
double r(double x);

struct borderCond {
    double alpha0, alpha1;
    double beta0, beta1;
    double leftBound, rightBound;
    double y_left, y_right;
};