#pragma once

struct Complex {
    double Re;
    double Im;
};

Complex add(Complex a, Complex b);

Complex multiple(Complex a, Complex b);

double modulo(Complex a);