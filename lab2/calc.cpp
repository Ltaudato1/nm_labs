#include "grid.hpp"


/**
 * @brief Функция ищет, между какими двумя узлами сетки лежит передаваемое значение x
 * 
 * @param grid Указатель на массив структур Point, где хранятся узлы и значения сеточной функции и её производной
 * @param x Значение, для ищется промежуток интерполирования
 * @param nodes Общее количество узлов
 * 
 */
int findInterpolationInterval(const Point* const grid, double const x, int const nodes){
    int l = 0;
    int r = nodes - 1;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (x < grid[mid].x) r = mid;
        else l = mid;
    }
    return r;
}

/**
 * @brief Функция вычисляет значение интерполяционного сплайна в форме Эрмита для заданной точки
 * 
 * @param grid Указатель на массив структур Point, где хранятся узлы и значения сеточной функции и её производной
 * @param x Значение, для которого вычисляется значение полинома
 * @param nodes Общее количество узлов
 * 
 */
double getSplineValue(const Point* const grid, double const x, int const nodes) {
    int r = findInterpolationInterval(grid, x, nodes);

    return grid[r].a * x * x * x + grid[r].b * x * x + grid[r].c * x + grid[r].d;
}