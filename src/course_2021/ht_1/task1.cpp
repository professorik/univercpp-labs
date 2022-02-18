#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

void cppStyle() {
    double a, b, c;
    cout << "(cpp)\nInput data:" << endl;
    cin >> a >> b >> c;
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                cout << "Infinitely many solutions";
            } else {
                cout << "No solution";
            }
        } else {
            cout << "anc = " << static_cast<double>(-c / b);
        }
    } else {
        double D = b * b - 4 * a * c;
        if (D < 0) {
            cout << "No solution for real numbers\n";
            D = sqrt(-D);
            cout << "anc[0,1] = " << static_cast<double>(-b / (2 * a)) << "+-" << static_cast<double>(D / (2 * a))
                 << "*i\n";
        } else if (D == 0) {
            cout << "anc = " << static_cast<double>(-b / (2 * a));
        } else {
            cout << "x1 = " << static_cast<double>((-b + sqrt(D)) / (2 * a)) << "\n";
            cout << "x2 = " << static_cast<double>((-b - sqrt(D)) / (2 * a));
        }
    }
}

void cStyle() {
    double a, b, c;
    printf("(c)\nInput data:\n");
    scanf("%lf%lf%lf", &a, &b, &c);
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("Infinitely many solutions");
            } else {
                printf("No solution");
            }
        } else {
            printf("anc = %lf", (double) (-c / b));
        }
    } else {
        double D = b * b - 4 * a * c;
        if (D < 0) {
            printf("No solution for real numbers\n");
            D = sqrt(-D);
            printf("anc[0,1] = %lf+-%lf*i", (double) (-b / (2 * a)), (double) (D / (2 * a)));
        } else if (D == 0) {
            printf("anc = %lf", (double) (-b / (2 * a)));
        } else {
            printf("anc[0] = %lf\n", (double) ((-b + sqrt(D)) / (2 * a)));
            printf("anc[1] = %lf", (double) ((-b - sqrt(D)) / (2 * a)));
        }
    }
}

int main() {
    //cStyle();
    cppStyle();
    return 0;
}