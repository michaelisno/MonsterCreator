#pragma once
#include <string>

class Monster
{
private:
	std::string name;
	int health;
	int maxHealth;
	int level;
	int regenRate;

public:
	// Constructor
	Monster(std::string _name, int _maxHealth, int _level, int _regenRate);

	// Functions
	void TakeDamage(int damage);
	void EditMonster();

	// Getters
	std::string GetName();
	int GetHealth();
	int GetLevel();
	int GetRegenRate();

	// Setters
	void SetName(std::string _name);
	void SetHealth(int _health);
	void SetLevel(int _level);
	void SetRegenRate(int _regenRate);

};