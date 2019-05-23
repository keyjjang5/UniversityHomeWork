#pragma once

#include "Shape.h"

class Rectangle : public Shape
{
	float width, height;

public:
	Rectangle(float x, float y, float width, float height);

	void draw() const;
};