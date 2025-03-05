#include <stdio.h>
#include <math.h>
#include "grid.hpp"
#include "functions.hpp"
#include "calc.hpp"

#define MAX_NODES 33
#define NODES_FOR_PLOT 8
#define POINTS_FOR_ERROR_CALC 1000

/**
 * @brief Функция запускает процесс исследования зависимости погрешности вычисления значения функции
 * по интерполяционному полиному от количества заданных узлов
 * 
 * @param function Указатель на функцию, по которой будет построена сеточная функция
 * @param filename Путь до текстового файла, куда будут записаны полученные результаты
 * @param gridType Тип исследуемой сетки
 * 
 * @note Погрешность вычисляется как наибольшее отклонение от вычисляемой функции в одной из POINTS_FOR_ERROR_CALC точек,
 * равномерно разделённых на промежутке интерполирования
 * 
 */
void nodes_errorResearch(double (*function) (double), char* const filename, Type gridType) {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "nodes,error\n");
    for (int i = 2; i <= MAX_NODES; ++i) {
        Point *grid {new Point[i]};
        getGrid(gridType, grid, function, i);

        double error = 0;
        for (int j = 1; j < POINTS_FOR_ERROR_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_ERROR_CALC - 1);
            double currentError = fabs(function(x) - getPolynomValue(grid, x, i));
            if (currentError > error) error = currentError;
        }
        fprintf(fp, "%d,%.20f\n", i, error);
        delete[] grid;
    }
    fclose(fp);
}

void makePlots() {
    char filename[100];

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/chebyshev_smooth_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(CHEBYSHEV, grid, smoothFunction, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_ERROR_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_ERROR_CALC - 1);
            double y = getPolynomValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/chebyshev_breakdown_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(CHEBYSHEV, grid, breakdownFunction, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_ERROR_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_ERROR_CALC - 1);
            double y = getPolynomValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/uniform_smooth_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(UNIFORM, grid, smoothFunction, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_ERROR_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_ERROR_CALC - 1);
            double y = getPolynomValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/uniform_breakdown_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(UNIFORM, grid, breakdownFunction, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_ERROR_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_ERROR_CALC - 1);
            double y = getPolynomValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }
}


void startResearches() {
    char filename[100];

    // Исследуем гладкую функцию
    sprintf(filename, "data/nodes_error_chebyshev_smooth.csv");
    nodes_errorResearch(smoothFunction, filename, CHEBYSHEV);
    sprintf(filename, "data/nodes_error_uniform_smooth.csv");
    nodes_errorResearch(smoothFunction, filename, UNIFORM);

    // Исследуем функцию с разрывом
    sprintf(filename, "data/nodes_error_chebyshev_breakdown.csv");
    nodes_errorResearch(breakdownFunction, filename, CHEBYSHEV);
    sprintf(filename, "data/nodes_error_uniform_breakdown.csv");
    nodes_errorResearch(breakdownFunction, filename, UNIFORM);
}

int main() {
    startResearches();
    makePlots();
    return 0;
}