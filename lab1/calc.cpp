#include <iostream>
#include "grid.hpp"


double getPolynomValue(Point* grid, double x, int nodes) {
    double result = 0;
    double product = 1;

    for (int i = 0; i < nodes; ++i) {
        result += grid[i].dividedDifference * product;
        product *= (x - grid[i].x);
    }

    return result;
}