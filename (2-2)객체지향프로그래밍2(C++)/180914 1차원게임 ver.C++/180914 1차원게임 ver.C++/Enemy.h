#pragma once
#include <string>

class Enemy
{
	std::string shape;
	int pos;

public:
	Enemy(std::string enemy, int pos);
};

Enemy::Enemy(std::string enemy, int pos) : shape(shape), pos(pos)
{

}