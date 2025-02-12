#include <math.h>

double smoothFunction(double x) {
    return 3 * x - 14 + exp(-x);
}

double breakdownFunction(double x) {
    return smoothFunction(x) / (x + 0.60742786528740884936);
}