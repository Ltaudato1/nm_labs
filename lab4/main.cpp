#include <iostream>
#include <math.h>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <string>
#include "calc.hpp"
#include "functions.hpp"

#define LEFT_BOUND_SMOOTH 0
#define RIGHT_BOUND_SMOOTH M_PI

#define LEFT_BOUND_BREAKDOWN 0
#define RIGHT_BOUND_BREAKDOWN 2 * M_PI

#define INTEGRAL_VALUE_SMOOTH 4
#define INTEGRAL_VALUE_BREAKDOWN 2 - 2 * cos(M_E)

#define MAX_PARTITION 32

using std::endl;

void part_errorResearch(double (*function) (double), double leftBound, double rightBound, double integralValue, std::string filename) {
    std::ofstream out(filename);
    out << std::setprecision(20);

    out << "part,error" << endl;

    for (int partition = 1; partition <= MAX_PARTITION; partition *= 2) {
        out << partition << "," << fabs(integralValue - gauss3(function, leftBound, rightBound, partition)) << endl;
    }

    out.close();
}

void startResearches() {
    part_errorResearch(smoothFunction, LEFT_BOUND_SMOOTH, RIGHT_BOUND_SMOOTH, INTEGRAL_VALUE_SMOOTH, "data/part_error_smooth.csv");
    part_errorResearch(breakdownFunction, LEFT_BOUND_BREAKDOWN, RIGHT_BOUND_BREAKDOWN, INTEGRAL_VALUE_BREAKDOWN, "data/part_error_breakdown.csv");
}

int main() {
    startResearches();
    return 0;
}