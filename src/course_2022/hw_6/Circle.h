#pragma once
#include "Figure.h"
class Circle :
	public Figure
{
private:
	double radius;
public:
	Circle() { radius = 0;  name = "circle";}
	Circle(double r) { radius = r; name = "circle";}
	double calcArea() override;
	double calcPerimeter() override;
    double getRadiusFactor() override;
};

