#include "Equilateral.h"

Equilateral::Equilateral(double size) {
    this->size = size;
    name = "equilateral";
}

double Equilateral::calcArea() {
    return sqrt(3) * size * size / 4;
}

double Equilateral::calcPerimeter() {
    return 3 * size;
}

double Equilateral::getRadiusFactor() {
    return pow(size, 3) / (4 * calcArea());
}

