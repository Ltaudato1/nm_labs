#pragma once
#include <math.h>
#include "structures.hpp"

#define LEFT_BOUND -4.0     ///< Левая граница промежутка интерполирования
#define RIGHT_BOUND 5.0     ///< Правая граница промежутка интерполирования



void getGrid(Type gridType, Point *grid, double (*function) (double), double (*derivative) (double), int nodes);
