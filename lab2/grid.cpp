#include "grid.hpp"
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
 * а так же её производной
 * 
 * @param gridType Тип сетки (Чебышёвская или равномерная)
 * @param grid Указатель на массив структур Point, в который записывается все вычисляемые значения
 * @param function Указатель на функцию, по которой строится сеточная функция
 * @param derivative Указатель на функцию, которая обсчитывает значение производной сеточной функции
 * @param nodes Общее количество узлов
 * 
 */
void getGrid(Type gridType, Point *grid, double (*function) (double), double (*derivative) (double), int nodes) {
    for (int i = 0; i < nodes; ++i) {
        double x;
        if (gridType == CHEBYSHEV) {
            x = functionForChebyshev(nodes - i - 1, nodes);
        }
        else if (gridType == UNIFORM){
            x = functionForUniform(i, nodes);
        }
        grid[i] = {x, function(x), derivative(x)};
    }
}