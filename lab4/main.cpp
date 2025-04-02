#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <string>
#include "calc.hpp"
#include "functions.hpp"

#define LEFT_BOUND_SMOOTH 0
#define RIGHT_BOUND_SMOOTH M_PI

#define LEFT_BOUND_BREAKDOWN 0
#define RIGHT_BOUND_BREAKDOWN 2 * M_PI

#define INTEGRAL_VALUE 4

#define MAX_PARTITION 10000000

using std::endl;

void part_errorResearch(long double (*function) (long double), long double leftBound, long double rightBound, std::string filename) {
    std::ofstream out(filename);
    out << std::setprecision(20);

    out << "part,error" << endl;

    for (int partition = 1; partition <= MAX_PARTITION; partition *= 10) {
        out << partition << "," << fabs(INTEGRAL_VALUE - gauss3(function, leftBound, rightBound, partition)) << endl;
    }

    out.close();
}

void startResearches() {
    part_errorResearch(smoothFunction, LEFT_BOUND_SMOOTH, RIGHT_BOUND_SMOOTH, "data/part_error_smooth.csv");
    part_errorResearch(breakdownFunction, LEFT_BOUND_BREAKDOWN, RIGHT_BOUND_BREAKDOWN, "data/part_error_breakdown.csv");
}

int main() {
    startResearches();
    return 0;
}