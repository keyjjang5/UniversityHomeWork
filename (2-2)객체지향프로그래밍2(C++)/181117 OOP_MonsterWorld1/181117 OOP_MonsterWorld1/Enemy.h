#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"
#include "Map.h"


class Enemy : public GameObject{
	string face;
	Map& map;
	int itemCount;
	
public:
	Enemy(Position& pos, const string& face, Map& map)
		: GameObject(pos, face), face(face), itemCount(0), map(map)
	{}

	void update()
	{
		move();

		checkItem();
	}

	void move()
	{
		Position& pos = *getPosition();

		int randx = rand() % 3 - 1;
		int randy = rand() % 3 - 1;

		randx = rand() % 3 - 1;
		randy = rand() % 3 - 1;

		pos.x += randx;

		pos.y += randy;

		if (pos.x > 9)
			pos.x = 9;
		if (pos.x < 0)
			pos.x = 0;

		if (pos.y > 9)
			pos.y = 9;
		if (pos.y < 0)
			pos.y = 0;
	}

	void checkItem()
	{
		Position& pos = *getPosition();

		if (map.checkItem(pos.x, pos.y))
		{
			map.deleteItem(pos.x, pos.y);
			itemCount++;
		}
	}

	int getItemCount()
	{
		return itemCount;
	}

	//bool getDamagedIfAttacked(const GameObject& attacker)
	//{
	//	auto bullet = dynamic_cast<const Bullet *>(&attacker); // it only gets attacked when bullets attack.
	//	if (!bullet) return false;
	//	Direction bullet_direction = bullet->getDirection();
	//	float bullet_pos = bullet->getPosition();
	//	float pos = getPosition();
	//	if ((bullet_direction == Direction::Left && pos < bullet_pos && bullet_pos - pos <= 1.0f)
	//		|| (bullet_direction == Direction::Right && bullet_pos < pos && pos - bullet_pos <= 1.0f)
	//		|| (int)pos == (int)bullet_pos) {
	//		hp -= getDamage();
	//		nAnimations = 30;
	//		setShape(faceAttacked);
	//		return true;
	//	}
	//	return false;
	//}
};

#endif
