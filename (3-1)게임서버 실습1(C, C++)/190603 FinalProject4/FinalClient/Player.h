#pragma once

#include <iostream>


#include "Renderer.h"


using namespace std;

class Player
{
	Renderer& renderer;
	char nickname[20];
	int hp;
	int energy;
public:
	Player(char* name, int hp) : renderer(Renderer::getInstance()), hp(hp), energy(0) 
	{
		strcpy(nickname, name);
	}

	void ChargeEnergy();

	void Attack();
	void FirstAttack();
	void DoubleAttack();

	void Defend();
	void FirstDefend();
	void DoubleDefend();

	int GetHp();
	void SetHp(int hp);
	int GetEn();
	void SetEn(int en);
	string GetName();

	virtual void Draw(string& shape, int pos)
	{
		renderer.draw(shape, pos);
	}
};