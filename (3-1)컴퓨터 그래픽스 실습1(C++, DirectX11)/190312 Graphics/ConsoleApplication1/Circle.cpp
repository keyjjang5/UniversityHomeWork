#include "Circle.h"

Circle::Circle(float x, float y, float radius) : Shape(x, y), radius(radius)
{

}

void Circle::draw() const
{
	cout << "[Circle] Position : ('" << getX() << "', '" << getY() << "'), Radius = ('" << radius << "')" << endl;
}