#pragma once

#include <iostream>


#include "Renderer.h"


using namespace std;

class Player
{
	Renderer& renderer;
	string nickname;
	int hp;
	int energy;
public:
	Player(string& name, int hp) : renderer(Renderer::getInstance()), nickname(name), hp(hp), energy(0) {}

	void ChargeEnergy();

	void Attack();
	void FirstAttack();
	void DoubleAttack();

	void Defend();
	void FirstDefend();
	void DoubleDefend();

	int GetHp();
	int GetEn();
	string GetName();

	virtual void Draw(string& shape, int pos)
	{
		renderer.draw(shape, pos);
	}
};