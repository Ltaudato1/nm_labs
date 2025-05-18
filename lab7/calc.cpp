#include <iostream>
#include "functions.hpp"
#include <vector>

using std::vector;
using std::pair;
using std::make_pair;

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

    // Initialize x coordinates
    for (int i = 0; i < partitions; ++i) {
        result[i].first = cond.leftBound + i * h;
    }

    vector<double> a(partitions), b(partitions), c(partitions), d(partitions);

    // Fill the tridiagonal matrix coefficients for internal points
    for (int i = 1; i < partitions - 1; ++i) {
        double x = result[i].first;
        double pi = p(x);
        double qi = q(x);
        double ri = r(x);
        double fi = f(x);

        // Second-order finite difference coefficients
        a[i] = pi - qi * h / 2.0;  // Lower diagonal
        b[i] = -2.0 * pi + ri * h * h;  // Main diagonal
        c[i] = pi + qi * h / 2.0;  // Upper diagonal
        d[i] = fi * h * h;  // Right-hand side
    }

    // Handle left boundary condition (x = a)
    double x0 = result[0].first;
    double p0 = p(x0);
    double q0 = q(x0);
    double r0 = r(x0);
    double f0 = f(x0);
    
    // Second-order formula for left boundary
    a[0] = 0.0;
    b[0] = h * h * r0 - 2 * p0 + h * cond.alpha0 * (2 * p0 - h * q0) / cond.alpha1;
    c[0] = 2 * p0;
    d[0] = h * h * f0 + cond.y_left * (2 * p0 - h * q0) / cond.alpha1;

    // Handle right boundary condition (x = b)
    double xn = result[partitions-1].first;
    double pn = p(xn);
    double qn = q(xn);
    double rn = r(xn);
    double fn = f(xn);
    
    // Second-order formula for right boundary
    a[partitions-1] = 2 * pn;
    b[partitions-1] = h * h * rn - 2 * pn - h * cond.beta0 * (2 * pn + h * qn) / cond.beta1;
    c[partitions-1] = 0.0;
    d[partitions-1] = h * h * fn - cond.y_right * (2 * pn + h * qn) / cond.beta1;

    // Thomas algorithm for solving tridiagonal system
    vector<double> alpha(partitions), beta(partitions);
    
    // Forward sweep
    alpha[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];

    for (int i = 1; i < partitions; ++i) {
        double m = b[i] + a[i] * alpha[i-1];
        alpha[i] = -c[i] / m;
        beta[i] = (d[i] - a[i] * beta[i-1]) / m;
    }

    // Backward substitution
    result[partitions-1].second = beta[partitions-1];
    for (int i = partitions-2; i >= 0; --i) {
        result[i].second = alpha[i] * result[i+1].second + beta[i];
    }

    return result;
}