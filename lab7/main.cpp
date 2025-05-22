#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "calc.hpp"
#include "functions.hpp"

#define LEFT_BOUND 0
#define RIGHT_BOUND 4

#define LEFT_CONDITION 0
#define RIGHT_CONDITION 0

#define MAX_PARTITION 1048576 // 2^20

using std::string;
using std::endl;
using std::vector;
using std::pair;

void part_errorResearch(double (*p) (double), double(*q) (double), double (*r) (double), double (*f) (double), double (*answer) (double), borderCond cond, string const filename) {
    std::ofstream out(filename);
    out << std::setprecision(20);

    out << "part,error" << endl;

    for (int partition = 4; partition <= MAX_PARTITION; partition *= 2) {
        vector<pair<double, double>> function = solveBVP(p, q, r, f, cond, partition);
        double error = fabs(function[1].second - answer(function[1].first));
        for (int i = 2; i < partition; ++i) {
            double cur = fabs(function[i].second - answer(function[i].first));
            if (cur > error) error = cur;
        }
        out << (cond.rightBound - cond.leftBound) / (partition - 1) << "," << error << endl;
    }

    out.close();
}

void startResearches() {
    borderCond cond;
    cond.alpha0 = 1;
    cond.alpha1 = 2;
    cond.beta0 = 1;
    cond.beta1 = 2;
    cond.leftBound = LEFT_BOUND;
    cond.rightBound = RIGHT_BOUND;
    cond.y_left = LEFT_CONDITION;
    cond.y_right = RIGHT_CONDITION;
    part_errorResearch(p, q, r, f, answer, cond, "data/part_error.csv");
}

int main() {
    startResearches();
    return 0;
}