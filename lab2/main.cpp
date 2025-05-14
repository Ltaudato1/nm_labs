#include <stdio.h>
#include <math.h>
#include "grid.hpp"
#include "functions.hpp"
#include "calc.hpp"

#define MAX_NODES 13
#define POINTS_FOR_SPLINE_CALC 1000
#define NODES_FOR_PLOT 8

/**
 * @brief Функция запускает процесс исследования зависимости погрешности вычисления значения функции
 * по интерполяционному полиному от количества заданных узлов
 * 
 * @param function Указатель на функцию, по которой будет построена сеточная функция
 * @param function Указатель на функцию, в которой будет обсчитываться производная сеточной функции
 * @param filename Путь до текстового файла, куда будут записаны полученные результаты
 * @param filenamePlot Путь до текстового файла, куда будут записаны данные для построения графика интерполяционного сплайна
 * @param gridType Тип исследуемой сетки
 * 
 * @note Погрешность вычисляется как наибольшее отклонение от вычисляемой функции в одной из POINTS_FOR_SPLINE_CALC точек,
 * равномерно разделённых на промежутке интерполирования
 * 
 */
void nodes_errorResearch(double (*function) (double), double (*derivative) (double), char* const filename, Type gridType) {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "nodes,error\n");
    for (int i = 1; i <= MAX_NODES; ++i) {
        int nodes = pow(2, i);
        Point *grid {new Point[nodes]};
        getGrid(gridType, grid, function, derivative, nodes);
        double error = 0;
        for (int j = 1; j < 10 * nodes; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (10 * nodes);

            double currentError = fabs(function(x) - getSplineValue(grid, x, nodes));
            if (currentError > error) error = currentError;
        }
        fprintf(fp, "%d,%.20f\n", nodes, error);
        delete[] grid;
    }
    fclose(fp);
}


void startResearches() {
    char filename[100];
    char filenamePlot[100];

    // Исследуем гладкую функцию
    sprintf(filename, "data/nodes_error_chebyshev_smooth.csv");
    sprintf(filenamePlot, "data/chebyshev_smooth_plot.csv");
    nodes_errorResearch(smoothFunction, smoothFunctionDerivative, filename, CHEBYSHEV);
    sprintf(filename, "data/nodes_error_uniform_smooth.csv");
    sprintf(filenamePlot, "data/uniform_smooth_plot.csv");
    nodes_errorResearch(smoothFunction, smoothFunctionDerivative, filename, UNIFORM);

    // Исследуем функцию с разрывом
    sprintf(filename, "data/nodes_error_chebyshev_breakdown.csv");
    sprintf(filenamePlot, "data/chebyshev_breakdown_plot.csv");
    nodes_errorResearch(breakdownFunction, breakdownFunctionDerivative, filename, CHEBYSHEV);
    sprintf(filename, "data/nodes_error_uniform_breakdown.csv");
    sprintf(filenamePlot, "data/uniform_breakdown_plot.csv");
    nodes_errorResearch(breakdownFunction, breakdownFunctionDerivative, filename, UNIFORM);
}


void makePlots() {
    char filename[100];

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/chebyshev_smooth_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(CHEBYSHEV, grid, smoothFunction, smoothFunctionDerivative, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_SPLINE_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_SPLINE_CALC - 1);
            double y = getSplineValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/chebyshev_breakdown_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(CHEBYSHEV, grid, breakdownFunction, breakdownFunctionDerivative, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_SPLINE_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_SPLINE_CALC - 1);
            double y = getSplineValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/uniform_smooth_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(UNIFORM, grid, smoothFunction, smoothFunctionDerivative, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_SPLINE_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_SPLINE_CALC - 1);
            double y = getSplineValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }

    for (int i = 2; i <= NODES_FOR_PLOT; i += 2) {
        sprintf(filename, "data/uniform_breakdown_%d.csv", i);
        Point *grid {new Point[i]};
        getGrid(UNIFORM, grid, breakdownFunction, breakdownFunctionDerivative, i);
        FILE* fp = fopen(filename, "w");
        fprintf(fp, "x,y\n");

        for (int j = 0; j < POINTS_FOR_SPLINE_CALC; ++j) {
            double x = LEFT_BOUND + (RIGHT_BOUND - LEFT_BOUND) * j / (POINTS_FOR_SPLINE_CALC - 1);
            double y = getSplineValue(grid, x, i);

            fprintf(fp, "%.20f,%.20f\n", x, y);
        }

        fclose(fp);
    }
}

int main() {
    startResearches();
    makePlots();
    return 0;
}