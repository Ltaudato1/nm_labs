#include <iostream>
#include "grid.hpp"

/**
 * @brief Функция вычисляет значение интерполяционного полинома в форме Ньютона для заданной точки
 * 
 * @param grid Указатель на массив структур Point, где хранятся узлы и значения сеточной функции
 * @param x Значение, для которого вычисляется значение полинома
 * @param nodes Общее количество узлов
 * 
**/
double getPolynomValue(const Point* const grid, double x, int nodes) {
    double result = 0;
    double product = 1;

    for (int i = 0; i < nodes; ++i) {
        result += grid[i].dividedDifference * product;
        product *= (x - grid[i].x);
    }

    return result;
}