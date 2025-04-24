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

void part_errorResearch(double (*p) (double), double(*q) (double), double (*r) (double), double (*f) (double), double (*answer) (double), double leftBound, double rightBound, double leftCondition, double rightCondition, string const filename) {
    std::ofstream out(filename);
    out << std::setprecision(20);

    out << "part,error" << endl;

    for (int partition = 4; partition <= MAX_PARTITION; partition *= 2) {
        vector<pair<double, double>> function = endDif(p, q, r, f, leftCondition, rightCondition, leftBound, rightBound, partition);
        double error = fabs(function[1].second - answer(function[1].first));
        for (int i = 2; i < partition; ++i) {
            double cur = fabs(function[i].second - answer(function[i].first));
            if (cur > error) error = cur;
        }
        out << partition << "," << error << endl;
    }

    out.close();
}

void startResearches() {
    part_errorResearch(p, q, r, f, answer, LEFT_BOUND, RIGHT_BOUND, LEFT_CONDITION, RIGHT_CONDITION, "data/part_error.csv");
}

int main() {
    startResearches();
    return 0;
}