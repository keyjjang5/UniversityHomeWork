#include "Player.h"

void Player::ChargeEnergy()
{
	++energy;
	printf("%s는 기모으기를 시전했다.", nickname);

	return;
}

void Player::Attack()
{
	if (energy <= 0)
	{
		printf("기력이 부족합니다. 공격을 시전하지 못했습니다.");

		return;
	}

	printf("%s는 적을 공격했다.", nickname);
	energy -= 1;
}

void Player::FirstAttack()
{
	if (energy <= 1)
	{
		printf("기력이 부족합니다. 선제공격을 시전하지 못했습니다.");

		return;
	}

	printf("%s는 적을 선제공격했다.", nickname);
	energy -= 2;
}

void Player::DoubleAttack()
{
	if (energy <= 2)
	{
		printf("기력이 부족합니다. 이단공격을 시전하지 못했습니다.");

		return;
	}

	printf("%s는 적을 이단공격했다.", nickname);
	energy -= 3;
}

void Player::Defend()
{
	printf("%s는 방어했다.", nickname);
}

void Player::FirstDefend()
{
	if (energy <= 0)
	{
		printf("기력이 부족합니다. 선제방어를 시전하지 못했습니다.");

		return;
	}

	printf("%s는 미리 방어했다.", nickname);
	energy -= 1;
}

void Player::DoubleDefend()
{
	if (energy <= 1)
	{
		printf("기력이 부족합니다. 이중방어를 시전하지 못했습니다.");

		return;
	}

	printf("%s는 두번 방어했다.", nickname);
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