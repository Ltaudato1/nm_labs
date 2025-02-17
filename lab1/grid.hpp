#pragma once
#include <math.h>

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#define LEFT_BOUND -4.0
#define RIGHT_BOUND 5.0

struct Point {
    double x;
    double y;
    double dividedDifference; // в массиве данное поле i-го элемента хранит в себе [y_0, ..., y_i]
};

enum Type {
    CHEBYSHEV,
    UNIFORM
};

void getGrid(Type gridType, Point *grid, double (*function) (double), int nodes);

#endif