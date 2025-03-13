#include <iostream>
#include "calc.hpp"
#include "functions.hpp"
using namespace std;

int main() {
    cout << getIntegral(smoothFunction, 0, 3, 0.1) << endl;
    return 0;
}