#pragma once
#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <array>

struct GameData
{
	int maxMonsterCount;
	std::array<int, 2> playerDamage = {};
	int heavyAttackCount;
};

#endif