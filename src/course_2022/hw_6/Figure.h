#pragma once
#include <iostream>
#include <string>
#include<vector>
class Figure
{
protected:
	std::string name;
	int x = 0;
	int y = 0;
public:
	void printInfo();
	virtual double calcArea() = 0;
	virtual double calcPerimeter() = 0;
	virtual double getRadiusFactor() = 0;
	bool isOverlapping(Figure * a);
	std::string getName() { return name; }
};

