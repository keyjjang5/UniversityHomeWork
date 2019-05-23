#pragma once

class EnemySpawner
{
	int full;
	Enemy* enemyP[5];
	int cnt;
	int interval;

public:
	EnemySpawner(int interval);
	void summon(int pos, char* shape, char* shapeAttacked, float hp);
	void dead(int i);

	void setPtr(int i);

	Enemy* getEnemy(int i)
	{
		return enemyP[i];
	}
};

EnemySpawner::EnemySpawner(int interval = 0) : cnt(0), interval(interval), full(5)
{
	for (int i = 0; i < 5; i++)
	{
		enemyP[i] = nullptr;
	}
}

void EnemySpawner::setPtr(int i)
{
	enemyP[i] = nullptr;
}

void EnemySpawner::summon(int pos = 90, char* shape = "(*_*)", char* shapeAttacked = "(T_T)", float hp = 10)
{
	if (cnt >= 5)
		return;
	if (interval < 20)
	{
		interval++;
		return;
	}

	for (int i = 0; i < 5; i++)
	{
		if (enemyP[i] != nullptr)
			continue;
		if (enemyP[i] == nullptr)
		{
			enemyP[i] = new Enemy(shape, shapeAttacked, pos, hp);
			
			cnt++;
			interval = 0;

			break;
		}
	}
}

void EnemySpawner::dead(int i)
{
	cnt--;
	delete(enemyP[i]);
	enemyP[i] = nullptr;
}