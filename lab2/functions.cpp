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
    return 3*x - 14 + exp(abs(x + log(2)));
}

/**
 * @brief Возвращает значение производной гладкой функции с разрывом производной в заданной точке
 */
double breakdownFunctionDerivative(double x) {
    return 3 + (x + log(2)) * exp(abs(x + log(2))) / abs(x + log(2));
}