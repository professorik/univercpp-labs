#include "Rectangle.h"

Rectangle::Rectangle(double a, double b) {
    this->a = a;
    this->b = b;
    name = "rectangle";
}

double Rectangle::calcArea() {
    return a * b;
}

double Rectangle::calcPerimeter() {
    return 2 * (a + b);
}

double Rectangle::getRadiusFactor() {
    return sqrt(a * a + b * b) / 2;
}
