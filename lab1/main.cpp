#include <iostream>
#include <math.h>
#include "grid.hpp"
#include "functions.hpp"
#include "calc.hpp"

int main() {
    Point *grid {new Point[10]};
    getUniformGrid(grid, smoothFunction, 10, -4);
    for (int i = 0; i < 10; ++i) {
        printf("x = %.15f\npolynom = %.15f\nactual = %.15f\n\n", grid[i].x, getPolynomValue(grid, grid[i].x, 10), smoothFunction(grid[i].x));
    }
    return 0;
}