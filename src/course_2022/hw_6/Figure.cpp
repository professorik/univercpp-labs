#include "Figure.h"

void Figure::printInfo() {
    std::cout << "this is a " << name << std::endl;
    std::cout << " area: " << calcArea() << "\t perimeter: " << calcPerimeter() << std::endl;
    std::cout << "radius factor: " << getRadiusFactor() << std::endl;
}

bool Figure::isOverlapping(Figure *a) {
    return this->getRadiusFactor() >= a->getRadiusFactor();
}
