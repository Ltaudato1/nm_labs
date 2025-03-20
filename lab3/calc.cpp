#include <iostream>
#include <math.h>

double getIntegral(double (*function) (double), double leftBound, double rightBound, int partitions) {
    if (leftBound > rightBound) return (-1) * getIntegral(function, rightBound, leftBound, partitions);

    double h = (rightBound - leftBound) / partitions;

    double integralValue = 0;

    for (int i = 0; i < partitions; ++i) {
        integralValue += function(leftBound + i * h + h / 2);
    }

    return integralValue * h;
}