#pragma once

#include <iostream>

using namespace std;


class Shape
{
	float x, y;

public:
	Shape(float x, float y);

	virtual void draw() const;

	float getX() const;

	float getY() const;
};