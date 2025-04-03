#include <iostream>
#include <math.h>

/**
 * @brief Возвращает значение f(x, y) из уравнения y' = f(x, y)
 */
long double equation(long double x, long double y) {
    return 2 * x - 3 + y;
}

/**
 * @brief Возвращает значение решения ДУ для вычисления погрешности
 */
long double answer(long double x) {
    return 1 - 2 * x - exp(x);
}
