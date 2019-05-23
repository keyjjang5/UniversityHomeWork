#pragma once

#include "Shape.h";

class Circle : public Shape
{
	float radius;

public:
	Circle(float x, float y, float radius);

	void draw() const;
};