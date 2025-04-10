#include <iostream>
#include <vector>

using std::vector;
using std::pair;

vector<pair<double, double>> runge_cutta4(double (*equation) (double, double), double startCondition, double leftBound, double rightBound, int partitions) {
    vector<pair<double, double>> answer;
    answer.push_back({leftBound, startCondition});
    double h = (rightBound - leftBound) / partitions;

    for (int k = 1; k <= partitions; ++k) {
        double x_next = answer[0].first + k * h; 
        double x_prev = answer[k-1].first;
        double y_prev = answer[k-1].second;

        double k1 = equation(x_prev, y_prev);
        double k2 = 2 * equation(x_prev + h / 2, y_prev + h * k1 / 2);
        double k3 = 2 * equation(x_prev + h / 2, y_prev + h * k2 / 2);
        double k4 = equation(x_prev + h, y_prev + h * k3);

        answer.push_back({x_next, y_prev + h * (k1 + k2 + k3 + k4) / 6});
    }

    return answer;
}