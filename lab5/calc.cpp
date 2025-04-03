#include <iostream>
#include <vector>

using std::vector;
using std::pair;

vector<pair<long double, long double>> runge_cutta4(long double (*equation) (long double, long double), long double startCondition, long double leftBound, long double rightBound, int partitions) {
    vector<pair<long double, long double>> answer;
    answer.push_back({leftBound, startCondition});
    double h = (rightBound - leftBound) / partitions;

    for (int k = 1; k <= partitions; ++k) {
        long double x_next = answer[0].first + k * h; 
        long double x_prev = answer[k-1].first;
        long double y_prev = answer[k-1].second;

        long double k1 = equation(x_prev, y_prev);
        long double k2 = 2 * equation(x_prev + h / 2, y_prev + h * k1 / 2);
        long double k3 = 2 * equation(x_prev + h / 2, y_prev + h * k2 / 2);
        long double k4 = equation(x_prev + h, y_prev + h * k3);

        answer.push_back({x_next, y_prev + h * (k1 + k2 + k3 + k4) / 6});
    }

    return answer;
}