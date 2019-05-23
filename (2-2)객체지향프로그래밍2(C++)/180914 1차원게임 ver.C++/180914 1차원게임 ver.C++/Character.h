#pragma once
using namespace std;

class Character
{
	std::string shape;
	int pos;

public:
	Character(std::string shape, int pos);
	void setShape(std::string shape);
	void increasePos();
	void decreasePos();
	int returnPos();
	std::string returnShape();
};

Character::Character(std::string shape, int pos) : shape(shape), pos(pos)
{
	
}

void Character::setShape(std::string shape)
{
	this->shape = shape;
}

void Character::increasePos()
{
	pos++;
}

void Character::decreasePos()
{
	pos--;
}

int Character::returnPos()
{
	return pos;
}

std::string Character::returnShape()
{
	return shape;
}