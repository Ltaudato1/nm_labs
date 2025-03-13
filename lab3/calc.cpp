#include <iostream>
#include <math.h>

double getIntegral(double (*function) (double), double leftBound, double rightBound, double precision) {
    if (leftBound > rightBound) return (-1) * getIntegral(function, rightBound, leftBound, precision);

    double h = (rightBound - leftBound) / 2;
    int points = 2;
    double I_n = 2 * h * function(h);
    double I_2n = h * (function(h / 2) + function(3 * h / 2));

    while (fabs(I_2n - I_n) > precision) {
        I_n = I_2n;
        I_2n = 0;
        h /= 2;
        points *= 2;

        for (int i = 0; i < points; ++i) {
            I_2n += function(leftBound + i * h + h / 2);
        }
        I_2n *= h;
    }

    return I_2n;
}