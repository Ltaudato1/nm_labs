#include <iostream>
#include "grid.hpp"

double getDividedDifference(Point* grid, int nodes) {
    double result = 0;
    for (int j = 0; j < nodes; ++j) {
        double delimiter = 1;
        for (int i = 0; i < nodes; ++i) {
            if (i != j) delimiter *= (grid[j].x - grid[i].x);
        }
        result += grid[j].y / delimiter;
    }
    return result;
}

double getPolynomValue(Point* grid, double x, int nodes) {
    double result = grid[0].y;
    for (int i = 1; i < nodes; ++i) {
        double dividedDifference = getDividedDifference(grid, i+1);
        double product = 1;
        for (int j = 1; j < i; ++j) {
            product *= (x - grid[j].x);
        }
        result += dividedDifference * product;
    }
    return result;
}