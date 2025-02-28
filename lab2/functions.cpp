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
 * @brief Возвращает значение гладкой функции с разрывом в заданной точке
 */
double breakdownFunction(double x) {
    return smoothFunction(x) / (x + log(2));
}

/**
 * @brief Возвращает значение производной гладкой функции с разрывом в заданной точке
 */
double breakdownFunctionDerivative(double x) {
    return (-x + exp(x) * (14 + log(8)) - (1 + log(2))) / (exp(x) * (x + log(2)) * (x + log(2)));
}