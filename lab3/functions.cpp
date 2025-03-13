#include <iostream>

/**
 * @brief Возвращает значение гладкой функции в заданной точке
 */
double smoothFunction(double x) {
    return 10 * x * x * (3 - x) * (3 - x) / 81;
}