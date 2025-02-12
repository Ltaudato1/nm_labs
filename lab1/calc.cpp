#include <iostream>
#include "grid.hpp"

double getDividedDifference(Point* grid, int start, int end) {
    if (end - start == 1) {
        return (grid[end].y - grid[start].y) / (grid[end].x - grid[start].x);
    } else {
        return (getDividedDifference(grid, start+1, end) - getDividedDifference(grid, start, end - 1)) / (grid[end].x - grid[start].x);
    }
}

double getPolynomValue(Point* grid, double x, int nodes) {
    double result = grid[0].y;

    for (int i = 1; i < nodes; ++i) {
        double product = getDividedDifference(grid, 0, i);
        for (int j = 0; j < i; ++j) {
            product *= (x - grid[j].x);
        }
        result += product;
    }

    return result;
}