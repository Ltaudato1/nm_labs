#include <iostream>
#include "grid.hpp"
#include "calc.hpp"
#include <math.h>

double functionForChebyshev(int i, int n) {
    return (LEFT_BOUND + RIGHT_BOUND) / 2 + (RIGHT_BOUND - LEFT_BOUND) / 2 * cos(M_PI * (2 * i + 1) / (2 * n));
}

double functionForUniformGrid(int i, int n) {
    return LEFT_BOUND + i * (RIGHT_BOUND - LEFT_BOUND) / (n - 1);
}

double getDividedDifference(Point* grid, int start, int end) {
    if (end == start) {
        return grid[end].y;
    } else {
        return (getDividedDifference(grid, start+1, end) - getDividedDifference(grid, start, end-1)) / (grid[end].x - grid[start].x);
    }
}

void getChebyshevGrid(Point *grid, double (*function) (double), int nodes) {
    double x = functionForChebyshev(0, nodes);
    grid[0].x = x;
    grid[0].y = function(x);
    grid[0].dividedDifference = getDividedDifference(grid, 0, 0);
    for (int i = 1; i < nodes; ++i) {
        x = functionForChebyshev(i, nodes);
        grid[i].x = x;
        grid[i].y = function(x);
        grid[i].dividedDifference = (getDividedDifference(grid, 1, i) - grid[i-1].dividedDifference) / (grid[i].x - grid[0].x);
    }
}

void getUniformGrid(Point* grid, double (*function) (double), int nodes, double x_0) {
    double x = functionForUniformGrid(0, nodes);
    grid[0].x = x;
    grid[0].y = function(x);
    grid[0].dividedDifference = getDividedDifference(grid, 0, 0);
    for (int i = 1; i < nodes; ++i) {
        x = functionForUniformGrid(i, nodes);
        grid[i].x = x;
        grid[i].y = function(x);
        grid[i].dividedDifference = (getDividedDifference(grid, 1, i) - grid[i-1].dividedDifference) / (grid[i].x - grid[0].x);
    }
}