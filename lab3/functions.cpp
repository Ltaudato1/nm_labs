#include <iostream>
#include <math.h>

/**
 * @brief Возвращает значение гладкой функции в заданной точке
 */
double smoothFunction(double x) {
    return sin(x);
}

/**
 * @brief Возвращает значение функции с разрывом производной в заданной точки
 */
double breakdownFunction(double x) {
    return fabs(x - M_PI) * cos(x);
}