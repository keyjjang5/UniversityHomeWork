#pragma once
#include "Bullet.h"

class Player
{
	int pos;
	char shape[20];
	char shapeAttacked[20];
	char shapeNormal[20];
	float hp;
	bool isSurvive;
	bool isRight;
	int damage;

	Bullet* bulletP[10];
	int bulletCnt;
	int bulletCoolTime;

	bool isAttacked;
	int countAtk;

public:
	Player(char* shape, char* shapeAttacked, int pos, float hp);
	void move(int speed);
	void update();
	bool reverseBool(bool b);
	void attack();
	void attacked(float damage);
	void dead();

	void setNullptr(int i);
	void setIsRight(bool b);

	int getPos();
	char* getShape();
	bool getIsRight();
	int getBulletCnt();
	bool getIsSurvive();
	Bullet* getBullet(int i)
	{
		return bulletP[i];
	}

};

Player::Player(char* shape = "(^_^)", char* shapeAttacked = "(   )", int pos = 30, float hp = 10)
	: pos(pos), hp(hp), isSurvive(true), isRight(true), bulletCnt(0), damage(1), bulletCoolTime(0), isAttacked(false),
	countAtk(0)
{
	strcpy(this->shape, shape);
	strcpy(this->shapeNormal, shape);
	strcpy(this->shapeAttacked, shapeAttacked);

	for (int i = 0; i < 10; i++)
		bulletP[i] = nullptr;
}

void Player::move(int speed)
{
	pos += speed;
}

void Player::update()
{
	if (isAttacked)
	{
		char temp[20];
		strcpy(temp, shape);
		strcpy(shape, shapeAttacked);
		strcpy(shapeAttacked, temp);
	}
	if (countAtk > 0)
	{
		//strcpy(shape, shapeAttacked);
		countAtk--;
	}
	else if (isAttacked && countAtk <= 0)
	{
		strcpy(shape, shapeNormal);
		strcpy(shapeAttacked, "(   )");
		isAttacked = false;
	}
	if (hp <= 0)
	{
		dead();
	}

	if (bulletCnt >= 10)
	{
		bulletCoolTime++;
		if (bulletCoolTime >= 20)
		{
			bulletCoolTime = 0;
			bulletCnt = 0;
		}
		return;
	}
}

bool Player::reverseBool(bool b)
{
	if (b)
		b = false;
	else
		b = true;

	return b;
}

void Player::attack()
{
	if (bulletCnt >= 10)
		return;

	for (int i = 0; i < 10; i++)
	{
		if (bulletP[i] != nullptr)
			continue;
		if (bulletP[i] == nullptr)
		{
			bulletP[i] = new Bullet(pos, damage);
			if (isRight)
				bulletP[i]->setSpeed(1);
			else
				bulletP[i]->setSpeed(-1);

			bulletCnt++;

			break;
		}
	}
	
}

void Player::attacked(float damage)
{
	hp -= damage;
	if (isAttacked)
		return;
	
	isAttacked = true;

	strcpy(shape, shapeAttacked);
	if (countAtk == 0)
		countAtk = 1;
}

void Player::dead()
{
	isSurvive = false;
}

void Player::setNullptr(int i)
{
	bulletP[i] = nullptr;
}

void Player::setIsRight(bool b)
{
	isRight = b;
}

int Player::getPos()
{
	return pos;
}

char* Player::getShape()
{
	return shape;
}

bool Player::getIsRight()
{
	return isRight;
}

int Player::getBulletCnt()
{
	return bulletCnt;
}

bool Player::getIsSurvive()
{
	return isSurvive;
}