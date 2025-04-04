#include <iostream>
#include <math.h>

/**
 * @brief Возвращает значение гладкой функции в заданной точке
 */
long double smoothFunction(long double x) {
    return 2 * sin(x);
}

/**
 * @brief Возвращает значение функции с разрывом производной в заданной точки
 */
long double breakdownFunction(long double x) {
    return fabs(x - M_E) * cos(x);
}