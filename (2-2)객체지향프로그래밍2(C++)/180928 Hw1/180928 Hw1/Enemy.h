#pragma once

class Enemy
{
	int pos;
	char shape[20];
	char shapeAttacked[20];
	char shapeNormal[20];
	float hp;
	bool isSurvive;
	bool isAttacked;
	int countAtk;
	float damage;
	int countMove;
public:
	Enemy(char* shape, char* shapeAttacked, int pos, float hp);
	void update();
	void move(Player* sub);
	bool reverseBool(bool b);
	void attacked(float damage);

	int getPos();
	char* getShape();
	bool getIsAttacked();
	bool getIsSurvive();
	float getDamage();

	bool onAttacked();
};

Enemy::Enemy(char* shape = "(*_*)", char* shapeAttacked = "(T_T)", int pos = 90, float hp = 10)
	: pos(pos), hp(hp), isSurvive(true), isAttacked(false), countAtk(0), damage(0.2f), countMove(5)
{
	strcpy(this->shape, shape);
	strcpy(this->shapeNormal, shape);
	strcpy(this->shapeAttacked, shapeAttacked);
}

void Enemy::update()
{
	if (countAtk > 0)
	{
		//strcpy(shape, shapeAttacked);
		countAtk--;
	}
	else if(isAttacked && countAtk <= 0)
	{
		strcpy(shape, shapeNormal);
		isAttacked = false;
	}
	if (hp == 0)
	{
		isSurvive = false;
	}
}

void Enemy::move(Player* sub)
{
	if (countMove < 5)
	{
		countMove++;
		return;
	}
	if (pos > sub->getPos())
		pos--;
	else if (pos < sub->getPos())
		pos++;

	countMove = 0;
}

bool Enemy::reverseBool(bool b)
{
	if (b)
		b = false;
	else
		b = true;

	return b;
}

void Enemy::attacked(float damage)
{
	hp -= damage;
	isAttacked = true;

	strcpy(shape, shapeAttacked);

	countAtk = 10;
}

int Enemy::getPos()
{
	return pos;
}

char* Enemy::getShape()
{
	return shape;
}

bool Enemy::getIsAttacked()
{
	return isAttacked;
}

bool Enemy::getIsSurvive()
{
	return isSurvive;
}

float Enemy::getDamage()
{
	return damage;
}

bool Enemy::onAttacked()
{
	return isAttacked;
}