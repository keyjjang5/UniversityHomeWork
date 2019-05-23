#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, float width, float height) : Shape(x, y), width(width), height(height)
{

}

void Rectangle::draw() const
{
	cout << "[Rectangle] Position : ('" << getX() << "', '" << getY() << "'), Size = ('" << width << "', '" << height << "')" << endl;
}