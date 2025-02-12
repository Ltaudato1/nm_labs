#include <iostream>
#include <stdio.h>
#include <math.h>
#include "grid.hpp"
#include "functions.hpp"
#include "calc.hpp"

#define MAX_NODES 20
#define POINTS_FOR_ERROR_CALC 100

using std::ofstream;

void nodes_errorChebyshev(double (*function) (double), char* const filename) {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "nodes,error\n");
    for (int i = 2; i <= MAX_NODES; ++i) {
        Point *grid {new Point[i]};
        getChebyshevGrid(grid, function, i);
        double error = 0;
        for (int j = 1; j < POINTS_FOR_ERROR_CALC; ++j) {
            double x = LEFT_BOUND + RIGHT_BOUND / POINTS_FOR_ERROR_CALC * j;
            double currentError = fabs(function(x) - getPolynomValue(grid, x, i));
            if (currentError > error) error = currentError;
        }
        fprintf(fp, "%d,%.20f\n", i, error);
        delete[] grid;
    }
    fclose(fp);
}

void nodes_errorUniform(double (*function) (double), char* const filename) {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "nodes,error\n");
    for (int i = 2; i <= MAX_NODES; ++i) {
        Point *grid {new Point[i]};
        getUniformGrid(grid, function, i, LEFT_BOUND);
        double error = 0;
        for (int j = 1; j < POINTS_FOR_ERROR_CALC; ++j) {
            double x = LEFT_BOUND + RIGHT_BOUND / POINTS_FOR_ERROR_CALC * j;
            double currentError = fabs(function(x) - getPolynomValue(grid, x, i));
            if (currentError > error) error = currentError;
        }
        fprintf(fp, "%d,%.20f\n", i, error);
        delete[] grid;
    }
    fclose(fp);
}
int main() {
    // Исследуем гладкую функцию
    char filename[100];
    sprintf(filename, "data/nodes_error_chebyshev_smooth.csv");
    nodes_errorChebyshev(smoothFunction, filename);
    sprintf(filename, "data/nodes_error_uniform_smooth.csv");
    nodes_errorUniform(smoothFunction, filename);

    //Исследуем функцию с разрывом
    sprintf(filename, "data/nodes_error_chebyshev_breakdown.csv");
    nodes_errorChebyshev(breakdownFunction, filename);
    sprintf(filename, "data/nodes_error_uniform_breakdown.csv");
    nodes_errorUniform(breakdownFunction, filename);
    return 0;
}