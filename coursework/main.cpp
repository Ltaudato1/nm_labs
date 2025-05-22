#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "calc.hpp"
#include "functions.hpp"

#define LEFT_BOUND 0
#define RIGHT_BOUND 6

#define START_CONDITION 0

#define MAX_PARTITION 1048576 // 2^20

using std::string;
using std::endl;
using std::vector;
using std::pair;

void part_errorResearch(double (*equation) (double, double), double (*answer) (double), double leftBound, double rightBound, double startCondition, string const filename) {
    std::ofstream out(filename);
    out << std::setprecision(20);

    out << "part,error_rk,error_adams" << endl;

    for (int partition = 4; partition <= MAX_PARTITION; partition *= 2) {
        vector<pair<double, double>> function_adams = adams4(equation, startCondition, leftBound, rightBound, partition);
        vector<pair<double, double>> function_rk = runge_cutta4(equation, startCondition, leftBound, rightBound, partition);
        double error_adams = fabs(function_adams[1].second - answer(function_adams[1].first));
        double error_rk = fabs(function_rk[1].second - answer(function_rk[1].first));
        for (int i = 2; i <= partition; ++i) {
            double cur = fabs(function_adams[i].second - answer(function_adams[i].first));
            if (cur > error_adams) error_adams = cur;
            cur = fabs(function_rk[i].second - answer(function_rk[i].first));
            if (cur > error_rk) error_rk = cur;
        }
        out << (rightBound - leftBound) / partition << "," << error_rk << "," << error_adams << endl;
    }

    out.close();
}

void startResearches() {
    part_errorResearch(equation, answer, LEFT_BOUND, RIGHT_BOUND, START_CONDITION, "data/part_error.csv");
}

int main() {
    startResearches();
    return 0;
}