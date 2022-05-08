#pragma once
#include "Figure.h"

class Rectangle :
        public Figure
{
private:
    double a;
    double b;
public:
    Rectangle() { a = b = 0;  name = "rectangle";}
    Rectangle(double a, double b);
    double calcArea() override;
    double calcPerimeter() override;
    double getRadiusFactor() override;
};
