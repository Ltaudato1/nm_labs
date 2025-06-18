#include <iostream>
#include "functions.hpp"
#include <vector>

using std::vector;
using std::pair;

vector<pair<double,double>> solveBVP(
    double (*p)(double),
    double (*q)(double),
    double (*r)(double),
    double (*f)(double),
    borderCond cond,
    int partitions
) {
    vector<pair<double, double>> result(partitions);
    double h = (cond.rightBound - cond.leftBound) / (partitions - 1);

    for (int i = 0; i < partitions; ++i) {
        result[i].first = cond.leftBound + i * h;
    }

    vector<double> a(partitions), b(partitions), c(partitions), d(partitions);

    for (int i = 1; i < partitions - 1; ++i) {
        double x = result[i].first;
        double pi = p(x);
        double qi = q(x);
        double ri = r(x);
        double fi = f(x);

        a[i] = pi - qi * h / 2.0;
        b[i] = h * h * ri - 2 * pi;
        c[i] = pi + qi * h / 2.0;
        d[i] = fi * h * h;
    }

    double a0 = cond.alpha0 - 3 * cond.alpha1 / (2 * h);
    double b0 = 2 * cond.alpha1 / h;
    double c0 = -cond.alpha1 / (2 * h);
    double d0 = cond.y_left;

    a[0] = 0.0;
    if (c[1] == 0) { 
        b[0] = a[1];
        c[0] = b[1];
        d[0] = d[1];

        a[1] = a0;
        b[1] = b0;
        c[1] = c0;
        d[1] = d0;
    } else {
        c[0] = b0 - c0 * b[1] / c[1];
        b[0] = a0 - c0 * a[1] / c[1];
        d[0] = d0 - c0 * d[1] / c[1];
    }

    a0 = cond.beta1 / (2 * h);
    b0 = -2 * cond.beta1 / h;
    c0 = cond.beta0 + 3 * cond.beta1 / (2 * h);
    d0 = cond.y_right;

    c[partitions - 1] = 0.0;
    if (a[partitions - 2] == 0) {
        a[partitions - 1] = b[partitions - 2];
        b[partitions - 1] = c[partitions - 2];
        d[partitions - 1] = d[partitions - 2];

        a[partitions - 2] = a0;
        b[partitions - 2] = b0;
        c[partitions - 2] = c0;
        d[partitions - 2] = d0;
    } else {
        a[partitions - 1] = b0 - a0 * b[partitions - 2] / a[partitions - 2];
        b[partitions - 1] = c0 - a0 * c[partitions - 2] / a[partitions - 2];
        d[partitions - 1] = d0 - a0 * d[partitions - 2] / a[partitions - 2];
    }


    vector<double> alpha(partitions), beta(partitions);
    alpha[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];

    for (int i = 1; i < partitions; ++i) {
        double m = b[i] + a[i] * alpha[i-1];
        alpha[i] = -c[i] / m;
        beta[i] = (d[i] - a[i] * beta[i-1]) / m;
    }

    result[partitions-1].second = beta[partitions-1];
    for (int i = partitions-2; i >= 0; --i) {
        
        result[i].second = alpha[i] * result[i+1].second + beta[i];
    }

    return result;
}