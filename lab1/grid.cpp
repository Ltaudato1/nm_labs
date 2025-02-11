#include <iostream>
#include "grid.hpp"
#include <math.h>

double functionForChebyshev(int i, int n) {
    return cos((M_PI * (2 * i + 1)) / (2 * n));
}

double functionForUniformGrid(int i, double x_0) {
    return x_0 + i; // h == 1
}

void getChebyshevGrid(Point *grid, double (*function) (double), int nodes) {
    for (int i = 0; i < nodes; ++i) {
        double x = functionForChebyshev(i, nodes);
        grid[i].x = x;
        grid[i].y = function(x);
    }
}

void getUniformGrid(Point* grid, double (*function) (double), int nodes, double x_0) {
    for (int i = 0; i < nodes; ++i) {
        double x = functionForUniformGrid(i, x_0);
        grid[i].x = x;
        grid[i].y = function(x);
    }
}