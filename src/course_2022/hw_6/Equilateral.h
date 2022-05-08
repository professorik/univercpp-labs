#pragma once
#include "Figure.h"
class Equilateral :
        public Figure
{
private:
    double size;
public:
    Equilateral() { size = 0;  name = "equilateral";}
    Equilateral(double size);
    double calcArea() override;
    double calcPerimeter() override;
    double getRadiusFactor() override;
};
