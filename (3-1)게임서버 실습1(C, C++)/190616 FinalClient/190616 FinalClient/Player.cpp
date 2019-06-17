#include "Player.h"

void Player::ChargeEnergy()
{
	++energy;
	printf("%s�� ������⸦ �����ߴ�.", nickname);

	return;
}

void Player::Attack()
{
	if (energy <= 0)
	{
		printf("����� �����մϴ�. ������ �������� ���߽��ϴ�.");

		return;
	}

	printf("%s�� ���� �����ߴ�.", nickname);
	energy -= 1;
}

void Player::FirstAttack()
{
	if (energy <= 1)
	{
		printf("����� �����մϴ�. ���������� �������� ���߽��ϴ�.");

		return;
	}

	printf("%s�� ���� ���������ߴ�.", nickname);
	energy -= 2;
}

void Player::DoubleAttack()
{
	if (energy <= 2)
	{
		printf("����� �����մϴ�. �̴ܰ����� �������� ���߽��ϴ�.");

		return;
	}

	printf("%s�� ���� �̴ܰ����ߴ�.", nickname);
	energy -= 3;
}

void Player::Defend()
{
	printf("%s�� ����ߴ�.", nickname);
}

void Player::FirstDefend()
{
	if (energy <= 0)
	{
		printf("����� �����մϴ�. ������ �������� ���߽��ϴ�.");

		return;
	}

	printf("%s�� �̸� ����ߴ�.", nickname);
	energy -= 1;
}

void Player::DoubleDefend()
{
	if (energy <= 1)
	{
		printf("����� �����մϴ�. ���߹� �������� ���߽��ϴ�.");

		return;
	}

	printf("%s�� �ι� ����ߴ�.", nickname);
	energy -= 2;
}

int Player::GetHp()
{
	return hp;
}

int Player::GetEn()
{
	return energy;
}

string Player::GetName()
{
	return nickname;
}