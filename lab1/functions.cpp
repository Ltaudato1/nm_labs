#include <math.h>

/**
 * @brief Возвращает значение гладкой функции в заданной точке
 */
double smoothFunction(double x) {
    return 3 * x - 14 + exp(-x);
}
/**
 * @brief Возвращает значение гладкой функции с разрывом в заданной точке
 */
double breakdownFunction(double x) {
    return smoothFunction(x) / (x + log(2));
}