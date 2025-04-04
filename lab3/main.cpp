#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include "calc.hpp"
#include "functions.hpp"

#define LEFT_BOUND_SMOOTH 0
#define RIGHT_BOUND_SMOOTH M_PI

#define LEFT_BOUND_BREAKDOWN 0
#define RIGHT_BOUND_BREAKDOWN 2 * M_PI

#define INTEGRAL_VALUE_SMOOTH 4
#define INTEGRAL_VALUE_BREAKDOWN 2 - 2 * cos(M_E)

#define MAX_PARTITION 10000000

using std::ofstream;
using std::string;
using std::endl;
using std::setprecision;

void part_errorResearch(double (*function) (double), double leftBound, double rightBound, double integralValue, string filename) {
    ofstream out(filename);
    out << setprecision(20);
    out << "part,error" << endl;

    for (int partition = 1; partition <= MAX_PARTITION; partition *= 10) {
        out << partition << "," << fabs(integralValue - getIntegral(function, leftBound, rightBound, partition)) << endl;
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