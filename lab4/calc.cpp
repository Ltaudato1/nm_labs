#include <iostream>
#include <math.h>
#include <vector>

using std::vector;

long double gauss3(long double (*function) (long double), long double leftBound, long double rightBound, int partitions) {
    if (leftBound > rightBound) return (-1) * gauss3(function, rightBound, leftBound, partitions);

    long double h = (rightBound - leftBound) / partitions;

    vector<long double> coefficients = {
        5.0,
        8.0,
        5.0
    };
    
    vector<long double> roots = {
        -sqrt(3.0 / 5.0),
        0,
        sqrt(3.0 / 5.0)
    };

    long double integralValue = 0;

    for (int i = 0; i < partitions; ++i) {
        long double mid = leftBound + i * h + h / 2;  // (a + b) / 2

        for (int j = 0; j < 3; ++j) {
            integralValue += coefficients[j] * function(mid + h * roots[j] / 2);
        }
    }

    return integralValue * h / 18;
}