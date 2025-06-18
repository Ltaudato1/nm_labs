#include <iostream>
#include <vector>

using std::vector;
using std::pair;

vector<pair<double, double>> runge_cutta4_speedup(double (*equation) (double, double), double startCondition, double leftBound, double h) {
    vector<pair<double, double>> answer;
    answer.push_back({leftBound, startCondition});

    for (int k = 1; k <= 3; ++k) {
        double x_prev = answer[k-1].first;
        double y_prev = answer[k-1].second;

        double k1 = equation(x_prev, y_prev);
        double k2 = equation(x_prev + h / 2, y_prev + h * k1 / 2);
        double k3 = equation(x_prev + h / 2, y_prev + h * k2 / 2);
        double k4 = equation(x_prev + h, y_prev + h * k3);

        answer.push_back({x_prev + h, y_prev + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6});
    }

    return answer;
}

vector<pair<double, double>> adams4(double (*equation) (double, double), double startCondition, double leftBound, double rightBound, int partitions) {
    double h = (rightBound - leftBound) / partitions;
    vector<pair<double, double>> answer = runge_cutta4_speedup(equation, startCondition, leftBound, h);

    double f_0 = equation(answer[0].first, answer[0].second);
    double f_1 = equation(answer[1].first, answer[1].second);
    double f_2 = equation(answer[2].first, answer[2].second);
    double f_3 = equation(answer[3].first, answer[3].second);

    for (int k = 4; k <= partitions; ++k) {
        double x_new = leftBound + k * h;
        double y_new = answer[k-1].second + h * (-9 * f_0 + 37 * f_1 - 59 * f_2 + 55 * f_3) / 24;
        answer.push_back({x_new, y_new});

        f_0 = f_1;
        f_1 = f_2;
        f_2 = f_3;
        f_3 = equation(x_new, y_new);
    }

    return answer;
}

vector<pair<double, double>> runge_cutta4(double (*equation) (double, double), double startCondition, double leftBound, double rightBound, int partitions) {
    vector<pair<double, double>> answer;
    answer.push_back({leftBound, startCondition});
    double h = (rightBound - leftBound) / partitions;

    for (int k = 1; k <= partitions; ++k) {
        double x_prev = answer[k-1].first;
        double y_prev = answer[k-1].second;

        double k1 = equation(x_prev, y_prev);
        double k2 = equation(x_prev + h / 2, y_prev + h * k1 / 2);
        double k3 = equation(x_prev + h / 2, y_prev + h * k2 / 2);
        double k4 = equation(x_prev + h, y_prev + h * k3);

        answer.push_back({x_prev + h, y_prev + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6});
    }

    return answer;
}