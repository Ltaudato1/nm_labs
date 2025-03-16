#include <stdio.h>
#include <math.h>
#include "calc.hpp"
#include "functions.hpp"

#define LEFT_BOUND_SMOOTH 0
#define RIGHT_BOUND_SMOOTH M_PI
#define SMOOTH_INTEGRAL_VALUE 2

#define LEFT_BOUND_BREAKDOWN 0
#define RIGHT_BOUND_BREAKDOWN 2 * M_PI
#define BREAKDOWN_INTEGRAL_VALUE 4

#define MAX_PARTITION 7

void part_errorResearch(double (*function) (double), double leftBound, double rightBound, double integralValue, char* const filename) {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "part,error\n");

    for (int i = 0; i <= MAX_PARTITION; ++i) {
        int partition = pow(10, i);
        fprintf(fp, "%d,%.20f\n", partition, fabs(integralValue - getIntegral(function, leftBound, rightBound, partition)));
    }

    fclose(fp);
}

void startResearches() {
    char filename[100];
    sprintf(filename, "data/part_error_smooth.csv");
    part_errorResearch(smoothFunction, LEFT_BOUND_SMOOTH, RIGHT_BOUND_SMOOTH, SMOOTH_INTEGRAL_VALUE, filename);
    sprintf(filename, "data/part_error_breakdown.csv");
    part_errorResearch(breakdownFunction, LEFT_BOUND_BREAKDOWN, RIGHT_BOUND_BREAKDOWN, BREAKDOWN_INTEGRAL_VALUE, filename);
}

int main() {
    startResearches();
    return 0;
}