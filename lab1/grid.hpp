#pragma once
#include <math.h>

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#define LEFT_BOUND -4.0
#define RIGHT_BOUND 5.0

struct Point {
    double x;
    double y;
};

void getChebyshevGrid(Point *grid, double (*function) (double), int nodes);
void getUniformGrid(Point *grid, double (*function) (double), int nodes, double x_0);

#endif