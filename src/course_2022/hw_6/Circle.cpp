#include "Circle.h"

#define PI 3.1415

double Circle::calcArea()
{
	return 3.14159265 * radius * radius;
}

double Circle::calcPerimeter() {
    return 2 * PI * radius;
}

double Circle::getRadiusFactor() {
    return radius;
}

