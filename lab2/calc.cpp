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
        int c = (l + r) / 2;
        if (x < grid[c].x) r = c;
        else l = c;
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

    long double diffSquared = (grid[r].x - grid[l].x) * (grid[r].x - grid[l].x);
    double tr = x - grid[r].x;
    double tl = x - grid[l].x;

    double psi_l = tl * tr * tr / diffSquared;
    double psi_r = tr * tl * tl / diffSquared;
    double phi_l = (1 - 2 * tl / (grid[l].x - grid[r].x)) * tr * tr / diffSquared;
    double phi_r = (1 - 2 * tr / (grid[r].x - grid[l].x)) * tl * tl / diffSquared;

    return grid[l].y * phi_l + grid[l].yDerivative * psi_l + grid[r].y * phi_r + grid[r].yDerivative * psi_r;
}