#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

#define _N 1e3

double darbu(double= 0, double= 5, double= _N);

double simpson(double= 0, double= 5, double= _N);

double trapez(double= 0, double= 5, double= _N);

double monteCarlo(double= 0, double= 5, double= _N);

double monteCarloRandom(double= 0, double= 5, double= _N);

double F(double x) {
    return x * x - 4;
}

int main() {
    cout << setw(25) << "Method " << setw(8) << "Solution" << endl;
    cout << setw(25) << "Darboux integral " << setw(8) << darbu() << endl;
    cout << setw(25) << "Simpson method " << setw(8) << simpson() << endl;
    cout << setw(25) << "Trapezoidal integral " << setw(8) << trapez() << endl;
    cout << setw(25) << "Monte Carlo Method " << setw(8) << monteCarlo() << endl;
    cout << setw(25) << "Rand Monte Carlo Method " << setw(8) << monteCarloRandom() << endl;
    return 0;
}

double darbu(double l, double r, double N) {
    double sum = 0, delta = (r - l) / N;
    for (int i = 0; i < N; ++i) {
        sum += F(l + delta * (i + 0.5));
    }
    return sum * delta;
}


double simpson(double l, double r, double N) {
    double sum = 0, delta = (r - l) / N;
    for (int i = 1; 2 * i <= N; ++i) {
        sum += F(l + delta * (2 * i - 2)) + 4 * F(l + delta * (2 * i - 1)) + F(l + delta * (2 * i));
    }
    return sum * delta / 3;
}

double trapez(double l, double r, double N) {
    double sum = (F(l) + F(r)) / 2, delta = (r - l) / N;
    for (int i = 1; i < N; ++i) {
        sum += F(l + delta * i);
    }
    return sum * delta;
}

double monteCarlo(double l, double r, double N) {
    double dX = (r - l) / N, yMax = F(r), yMin = F(r);
    for (int i = 0; i < N; ++i) {
        yMax = max(yMax, F(l + dX * i));
        yMin = min(yMin, F(l + dX * i));
    }
    double dY = (yMax - yMin) / N;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        double x = l + i * dX;
        for (int j = 0; j < N; ++j) {
            double y = yMin + j * dY;
            double value = F(x);
            if (abs(2 * y - value) <= abs(value)) {
                sum += (value > 0) - (value < 0);
            }
        }
    }
    return dX * dY * static_cast<double>(sum);
}

double monteCarloRandom(double l, double r, double N) {
    srand(time(0));
    double delta = (r - l) / N, yMax = F(r), yMin = F(r);
    for (int i = 0; i < N; ++i) {
        yMax = max(yMax, F(l + delta * i));
        yMin = min(yMin, F(l + delta * i));
    }
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        double x = ((double) rand() / RAND_MAX) * (r - l) + l;
        double y = ((double) rand() / RAND_MAX) * (yMax - yMin) + yMin;
        double value = F(x);
        if (abs(2 * y - value) <= abs(value)) {
            sum += (value > 0) - (value < 0);
        }
    }
    return delta * (yMax - yMin) * static_cast<double>(sum);
}