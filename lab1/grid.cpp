#include <iostream>
#include "grid.hpp"
#include "calc.hpp"
#include <math.h>

/**
 * @brief Функция по номеру узла и общему количеству узлов вычисляет соответствующее значение для чебышёвской сетки
 * 
 * @param i Индекс вычисляемого узла
 * @param n Общее количество узлов
 * @return i-ый узел сетки Чебышёва
 * 
 */
double functionForChebyshev(int i, int n) {
    return (LEFT_BOUND + RIGHT_BOUND) / 2 + (RIGHT_BOUND - LEFT_BOUND) / 2 * cos(M_PI * (2 * i + 1) / (2 * n));
}

/**
 * @brief Функция по номеру узла и общему количеству узлов вычисляет соответствующее значение для равномерной сетки
 * 
 * @param i Индекс вычисляемого узла
 * @param n Общее количество узлов
 * @return i-ый узел равномерной сетки
 * 
 */
double functionForUniform(int i, int n) {
    return LEFT_BOUND + i * (RIGHT_BOUND - LEFT_BOUND) / (n - 1);
}

/**
 * @brief Функция вычисляет заданное число узлов для сетки определённного типа и вычисляет для каждого узла значение функции,
 * а так же коэффициенты gamma_k = [y_0, ..., y_k] для всех k от 0 до nodes
 * 
 * @param gridType Тип сетки (Чебышёвская или равномерная)
 * @param grid Указатель на массив структур Point, в который записывается все вычисляемые значения
 * @param function Указатель на функцию, по которой строится сеточная функция
 * @param nodes Общее количество узлов
 * 
 */
void getGrid(Type gridType, Point *grid, double (*function) (double), int nodes) {
    for (int i = 0; i < nodes; ++i) {
        double x;
        if (gridType == CHEBYSHEV) x = functionForChebyshev(i, nodes);
        if (gridType == UNIFORM) x = functionForUniform(i, nodes);
        grid[i] = {x, function(x)};
    }

    double* divDifferencesCalc {new double[nodes] {}};

    for (int i = 0; i < nodes; ++i) divDifferencesCalc[i] = grid[i].y;

    grid[0].dividedDifference = divDifferencesCalc[0];

    for (int i = 1; i < nodes; ++i) {
        for (int j = 0; j < nodes - i; ++j) {
            divDifferencesCalc[j] = (divDifferencesCalc[j + 1] - divDifferencesCalc[j]) / (grid[j + i].x - grid[j].x);
        }
        grid[i].dividedDifference = divDifferencesCalc[0];
    }

    delete[] divDifferencesCalc;
}