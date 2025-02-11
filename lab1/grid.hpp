#pragma once
#include <math.h>

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

struct Point {
    double x;
    double y;
};

void getChebyshevGrid(Point *grid, double (*function) (double), int nodes);
void getUniformGrid(Point *grid, double (*function) (double), int nodes, double x_0);

#endif