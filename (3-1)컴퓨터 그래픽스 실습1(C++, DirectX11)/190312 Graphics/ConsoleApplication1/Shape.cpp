#include "Shape.h";

Shape::Shape(float x, float y) : x(x), y(y)
{

}

void Shape::draw() const
{
	cout << "[Shape] Position : ('" << x << "', '" << y << "')" << endl;
}

float Shape::getX() const
{
	return x;
}

float Shape::getY() const
{
	return y;
}