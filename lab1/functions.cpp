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
    return abs(x - log(2)) * sin(x) + 1;
}