#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double eps = 1e-6;
int stepsNum[3] = {0,0,0};

long factorial(int num) {
    if (num < 0) return -1;
    return num < 2 ? 1 : num * factorial(num - 1);
}

double F(double x) {
    return x * x - 4;
}

double getDer(double x) {
    return (F(x + eps) - F(x)) / eps;
}

double newton(double l = 0, double r = 10) {
    double x = (l + r) / 2;
    do {
        x -= F(x) / getDer(x);
        ++stepsNum[0];
    } while (abs(F(x)) > eps);
    return x;
}

//it doesn't work if no solution on interval
double binSearch(double l = 0, double r = 10) {
    double x = (l+r)/2;
    while (r - l > eps){
        if (F(l) * F(x) <= 0){
            r = x;
        }else{
            l = x;
        }
        x = (l + r) / 2;
        ++stepsNum[1];
    }
    return x;
}

double secant(double l = 0, double r = 10) {
    while (abs(l - r) > eps){
        l = r - (r - l) * F(r) / (F(r) - F(l));
        r = l - (l - r) * F(l) / (F(l) - F(r));
        ++stepsNum[2];
    }
    return l;
}

int main() {
    double l,r;
    cout << "Input the left and right sides (abs(l) != abs(r)): \n";
    cin >> l >> r;
    if (l > r) swap(l,r);
    cout << setw(15) << "Method " << setw(5) << "Steps " << setw(8) << "Solution" << endl;
    cout << setw(15) << "Newton Method " << setw(5) << stepsNum[0] << setw(8) << newton(l, r)  << endl;
    cout << setw(15) << "Binary Search " << setw(5) << stepsNum[1] << setw(8) << binSearch(l, r) << endl;
    cout << setw(15) << "Secant Method " << setw(5) << stepsNum[2] << setw(8) << secant(l, r) << endl;
    cout << factorial(5) << " " << factorial(0);
    return 0;
}