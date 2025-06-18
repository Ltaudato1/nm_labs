#include <iostream>
#include <math.h>

/**
 * @brief Возвращает значение f(x, y) из уравнения y' = f(x, y)
 */
double equation(double x, double y) {
    return 2 * x - 3 + y;
}

/**
 * @brief Возвращает значение решения ДУ для вычисления погрешности
 */
double answer(double x) {
    return 1 - 2 * x - exp(x);
}
