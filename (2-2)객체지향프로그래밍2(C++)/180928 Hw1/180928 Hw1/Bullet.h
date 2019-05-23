#pragma once

class Bullet
{
	int pos;
	char shape[10];
	float damage;
	int speed;
	bool isSurvive;

public:
	Bullet(int pos, float damage, char* shape);
	void update();
	void move();
	bool checkRange();

	void setPos(int pos);
	void setDamage(float damage);
	void setShape(char* shape);
	void setSpeed(int speed);

	int getPos();
	char* getShape();
	float getDamage();

	bool onSurvive();
};

Bullet::Bullet(int pos = 0, float damage = 0, char* shape = "-")
	: pos(pos), damage(damage), isSurvive(true)
{
	strcpy(this->shape, shape);
}

void Bullet::update()
{
	
}

void Bullet::move()
{
	if (!checkRange())
		return;
	pos += speed;
}

bool Bullet::checkRange()
{
	if (pos <= 0 || pos >= 120)
		return false;

	return true;
}

void Bullet::setPos(int pos)
{
	this->pos = pos;
}

void Bullet::setDamage(float damage)
{
	this->damage = damage;
}

void Bullet::setShape(char* shape)
{
	strcpy(this->shape, shape);
}

void Bullet::setSpeed(int speed)
{
	this->speed = speed;
}

int Bullet::getPos()
{
	return pos;
}

char* Bullet::getShape()
{
	return shape;
}

float Bullet::getDamage()
{
	return damage;
}

bool Bullet::onSurvive()
{
	return isSurvive;
}