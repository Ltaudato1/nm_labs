#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::make_pair;

vector<pair<double,double>> solveBVP(
    double (*p)(double),
    double (*q)(double),
    double (*r)(double),
    double (*f)(double),
    double leftBound,
    double rightBound,
    double leftCond,
    double rightCond,
    int partitions
) {
    vector<pair<double, double>> result(partitions);
    double h = (rightBound - leftBound) / (partitions - 1);

    for (int i = 0; i < partitions; ++i) {
        result[i].first = leftBound + i * h;
    }
    result[0].second = leftCond;
    result[partitions - 1].second = rightCond;

    int m = partitions - 2;
    vector<double> a(m), b(m), c(m), d(m);

    for (int i = 0; i < m; ++i) {
        double xi = result[i+1].first;
        double pi = p(xi);
        double qi = q(xi);
        double ri = r(xi);
        double fi = f(xi);
        a[i] = pi - qi * h / 2.0;
        b[i] = -2.0 * pi + ri * h * h;
        c[i] = pi + qi * h / 2.0;
        d[i] = fi * h * h;
    }
    a[0] = 0.0;
    c[m-1] = 0.0;

    vector<double> cp(m), dp(m);
    cp[0] = c[0] / b[0];
    dp[0] = d[0] / b[0];
    for (int i = 1; i < m; ++i) {
        double denom = b[i] - a[i] * cp[i-1];
        cp[i] = c[i] / denom;
        dp[i] = (d[i] - a[i] * dp[i-1]) / denom;
    }
    result[m].second = dp[m-1];
    for (int i = m - 2; i >= 0; --i) {
        result[i + 1].second = dp[i] - cp[i] * result[i + 2].second;
    }

    return result;
}