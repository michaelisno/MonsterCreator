#pragma once
#include <string>
#include <chrono>
#include "GameData.h"

class Monster
{
private:
	std::string name;
	int health;
	int maxHealth;
	int level;
	int regenRate;

protected:
	void TakeDamage(int damage);
	void RegenerateHealth(std::chrono::time_point<std::chrono::steady_clock>& lastRegenTime);

public:
	// Constructor
	Monster(std::string _name, int _health, int _maxHealth, int _level, int _regenRate);

	// Functions
	void EditMonster();
	int FightMonster(GameData gameData);

	// Getters
	std::string GetName();
	int GetHealth();
	int GetLevel();
	int GetRegenRate();
	int GetMaxHealth();

	// Setters
	void SetName(std::string _name);
	void SetHealth(int _health);
	void SetLevel(int _level);
	void SetRegenRate(int _regenRate);
	void SetMaxHealth(int _maxHealth);

};