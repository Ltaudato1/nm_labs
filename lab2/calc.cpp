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
    int l = r - 1;

    double tr = x - grid[r].x;
    double tl = x - grid[l].x;

    double psi_l = tl * tr * tr / (grid[r].diff * grid[r].diff);
    double psi_r = tr * tl * tl / (grid[r].diff * grid[r].diff);
    double phi_l = (1 + 2 * tl / grid[r].diff) * tr * tr / (grid[r].diff * grid[r].diff);
    double phi_r = (1 - 2 * tr / grid[r].diff) * tl * tl / (grid[r].diff * grid[r].diff);

    return grid[l].y * phi_l + grid[l].yDerivative * psi_l + grid[r].y * phi_r + grid[r].yDerivative * psi_r;
}