#ifndef  ENEMIES_H_
#define ENEMIES_H_

#include "Enemy.h"
#include <algorithm>
#include <vector>

class Enemies {
	Renderer&			renderer;
	Map& map;
	vector<Enemy*>		container;
	int moveCount;

public:
	Enemies(Map& map)
		: renderer(Renderer::getInstance()), map(map), moveCount(0)
	{	
		//container.push_back(new Enemy(players, rand() % renderer.getScreenLength())); 

	}

	int getMoveCount() { return moveCount; }

	void update()
	{
		// // spawn enemies periodically.
		// if (n_remainings_for_respawn <= 0) {
		// 	// reset the timer for the next enemy spawning
		// 	if (container.size() < max_enemies)
		// 		container.push_back(new Enemy(players, rand() % renderer.getScreenLength()));
		// 	n_remainings_for_respawn = 30;
		// } else {
		// 	n_remainings_for_respawn--;
		// }

		// // update all enemies
		// for (auto enemy : container) enemy->update();
		
		// int size = container.size();
		// container.erase(remove_if(container.begin(), container.end(), 
		// 	[](Enemy* enemy) { 
		// 		if (enemy->isAlive() == false) { 
		// 			delete enemy; // you need to free the dynamically allocated enemies.
		// 			return true;
		// 		}
		// 		return false; 
		// 	}), container.end());
		// n_killed += size - container.size();

		for(auto enemy : container)
			enemy->update();
		moveCount++;
	}

	void add(Position& pos, string shape)
	{
		container.push_back(new Enemy(pos, shape, map));
	}

	void draw()
	{
		int posx = 12;
		int posy = 1;
		for (auto enemy : container)
		{
			enemy->draw();
			Borland::gotoxy(posx, posy);
			
			printf("# enemy%d : %d", posy, enemy->getItemCount());

			posy++;
		}

		Borland::gotoxy(posx, posy + 2);
		//이유는 모르겠지만 한글이 깨짐
		printf("# Total Move Count : %d", moveCount);
		/*printf("# of enemies = %2d,  ", container.size());
		for (auto enemy : container) 
			printf("%2.1f %2.1f  ", enemy->getPosition()->x, enemy->getPosition()->y);*/
	}

	//사용안함
	//Enemy* findClosest(float pos)
	//{
	//	Enemy* closest = nullptr;
	//	float dist = 0.0f;
	//	if (renderer.checkRange(pos) == false) return closest;
	//	for (auto enemy : container) {
	//		float enemy_pos = enemy->getPosition();
	//		if (renderer.checkRange(enemy_pos) == false) continue;
	//		float current_dist = fabs(pos - enemy_pos);
	//		if (!closest) {
	//			dist = current_dist;
	//			closest = enemy;
	//			continue;
	//		}
	//		// closest != nullptr;
	//		if (dist > current_dist) {
	//			dist = current_dist;
	//			closest = enemy;
	//		}
	//	}
	//	return closest;
	//}

	////사용안함
	//bool isShoted(Bullet& bullet)
	//{
	//	auto enemy = findClosest(bullet.getPosition());
	//	if (!enemy) return false;
	//	return enemy->getDamagedIfAttacked(bullet);
	//}
};


#endif

