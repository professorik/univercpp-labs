#pragma once
#include "Rectangle.h"
class Square :
	public Rectangle
{
public:
	Square(): Rectangle() { name = "square"; };
	Square(double a);
};

