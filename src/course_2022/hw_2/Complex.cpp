#include "Complex.h"
#include <cmath>

struct Complex add(Complex a, Complex b) {
    Complex c;
    c.Re = a.Re + b.Re;
    c.Im = a.Im + b.Im;
    return c;
}

struct Complex multiple(Complex a, Complex b) {
    Complex c;
    c.Re = a.Re * b.Re - a.Im * b.Im;
    c.Im = a.Re * b.Im + b.Re * a.Im;
    return c;
}

double modulo(Complex a) {
    return sqrt(a.Re * a.Re + a.Im * a.Im);
}