#include <iostream>
#include "grid.hpp"
#include "calc.hpp"
#include <math.h>
#include <stdlib.h>

double functionForChebyshev(int i, int n) {
    return (LEFT_BOUND + RIGHT_BOUND) / 2 + (RIGHT_BOUND - LEFT_BOUND) / 2 * cos(M_PI * (2 * i + 1) / (2 * n));
}

double functionForUniform(int i, int n) {
    return LEFT_BOUND + i * (RIGHT_BOUND - LEFT_BOUND) / (n - 1);
}

void getGrid(Type gridType, Point *grid, double (*function) (double), int nodes) {
    for (int i = 0; i < nodes; ++i) {
        double x;
        if (gridType == CHEBYSHEV) x = functionForChebyshev(i, nodes);
        if (gridType == UNIFORM) x = functionForUniform(i, nodes);
        grid[i].x = x;
        grid[i].y = function(x);
    }

    double** divDifferencesCalc {new double*[nodes] {}};

    divDifferencesCalc[0] = new double[nodes]{};
    for (int i = 0; i < nodes; ++i) divDifferencesCalc[0][i] = grid[i].y;

    for (int i = 1; i < nodes; ++i) {
        divDifferencesCalc[i] = new double[nodes-i];
        for (int j = nodes - i - 1; j >= 0; --j) {
            divDifferencesCalc[i][j] = (divDifferencesCalc[i-1][j+1] - divDifferencesCalc[i-1][j]) / (grid[j+i].x - grid[j].x);
        }
    }

    for (int i = 0; i < nodes; ++i) {
        grid[i].dividedDifference = divDifferencesCalc[i][0];
        delete[] divDifferencesCalc[i];
    }

    delete[] divDifferencesCalc;
}