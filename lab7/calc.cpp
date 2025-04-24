#include <iostream>
#include <vector>

using std::vector;
using std::pair;

vector<pair<double, double>> endDif(double (*p) (double), double (*q) (double), double (*r) (double), double (*f) (double), double leftCond, double rightCond, double leftBound, double rightBound, int partitions) {
    double h = (rightBound - leftBound) / (partitions - 1);
    vector<pair<double, double>> answer(partitions);
    for (int i = 0; i < partitions; ++i) {
        answer[i].first = leftBound + i * h;
    }

    vector<double> A(partitions), B(partitions), C(partitions), D(partitions);

    A[0] = 0;
    B[0] = 1;
    C[0] = 0;
    D[0] = leftCond;

    A[partitions - 1] = 0;
    B[partitions - 1] = 1;
    C[partitions - 1] = 0;
    D[partitions - 1] = rightCond;

    // Заполнение коэффициентов трёхдиагональной системы
    for (int i = 1; i < partitions - 1; ++i) {
        double x_i = leftBound + i * h;
        double pi = p(x_i);
        double qi = q(x_i);
        double ri = r(x_i);

        A[i] = (pi - qi * h / 2);
        B[i] = (h * h * ri - 2 * pi);
        C[i] = (pi + qi * h / 2);
        D[i] = f(x_i) * h * h;
    }

    vector<double> alpha(partitions), beta(partitions);
    alpha[0] = 0;
    beta[0] = leftCond;

    for (int i = 1; i < partitions; ++i) {
        double denom = B[i] + A[i]*alpha[i-1];
        alpha[i] = -C[i] / denom;
        beta[i]  =  (D[i] - A[i]*beta[i-1]) / denom;
    }

    answer[0].second = leftCond;
    answer[partitions - 1].second = rightCond;

    for (int i = partitions - 2; i >= 1; --i) {
        answer[i].second = alpha[i] * answer[i+1].second + beta[i];
    }

    return answer;
}