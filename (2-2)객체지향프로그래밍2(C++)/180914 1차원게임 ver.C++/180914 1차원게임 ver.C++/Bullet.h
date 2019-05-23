#pragma once
using namespace std;

class Bullet
{
	std::string shape;
	int pos;
	//Bullet* nextBulletP;

public:
	Bullet(std::string shape, int pos);
};

Bullet::Bullet(std::string shape, int pos) : shape(shape), pos(pos)
{

}

//class BulletManager
//{
//	
//
//public :
//	addLast();
//
//};