#include <math.h>

/**
 * @brief Возвращает значение гладкой функции в заданной точке
 */
double smoothFunction(double x) {
    return 3 * x - 14 + exp(-x);
}

/**
 * @brief Возвращает значение производной гладкой функции в заданной точке
 */
double smoothFunctionDerivative(double x) {
    return 3 - exp(-x);
}

/**
 * @brief Возвращает значение гладкой функции с разрывом производной в заданной точке
 */
double breakdownFunction(double x) {
    return abs(x + log(2)) * sin(x) + 1;
}

/**
 * @brief Возвращает значение производной гладкой функции с разрывом производной в заданной точке
 */
double breakdownFunctionDerivative(double x) {
    return (x + log(2)) * (sin(x) + (x + log(2)) * cos(x)) / abs(x + log(2));
}