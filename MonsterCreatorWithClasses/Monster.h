#pragma once

#include <string>
#include <chrono>

#include "GameData.h"

class Monster
{
private:
	std::string m_name;
	int m_health;
	int m_maxHealth;
	int m_level;
	int m_regenRate;

	void TakeDamage(int damage);
	void RegenerateHealth(std::chrono::time_point<std::chrono::steady_clock>& lastRegenTime);

public:
	Monster(std::string name, int health, int maxHealth, int level, int regenRate);

	void EditMonster();
	int FightMonster(GameData gameData);

	// getters
	std::string GetName() const { return m_name; }
	int GetHealth() const { return m_health; }
	int GetLevel() const { return m_level; }
	int GetRegenRate() const { return m_regenRate; }
	int GetMaxHealth() const { return m_maxHealth; }

	// setters
	void SetName(std::string name) { m_name = name; }
	void SetHealth(int health) { m_health = health; }
	void SetLevel(int level) { m_level = level; }
	void SetRegenRate(int regenRate) { m_regenRate = regenRate; }
	void SetMaxHealth(int maxHealth) { m_maxHealth = maxHealth; }

};