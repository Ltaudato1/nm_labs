#include <iostream>
#include <math.h>

double p(double x) {
    return 2 * x + 1;
}

double q(double x) {
    return 2 * x - 1;
}

double r(double x) {
    return -2;
}

double f(double x) {
    return x * x + x;
}

/**
 * @brief Возвращает значение решения ДУ для вычисления погрешности
 */
double answer(double x) {
    double e = exp(-4);
    double c1 = -(e + 31) /  (22 - 6 * e);
    double c2 = 3 * c1 - 0.5;
    return c1 * (2 * x - 1) + c2 * exp(-x) + (x * x + 1) / 2;
}



