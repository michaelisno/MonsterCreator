#include <iostream>
#include "Monster.h"

using namespace std;

Monster::Monster(string _name, int _maxHealth, int _level, int _regenRate)
{
	name = _name;
	health = _maxHealth;
	maxHealth = _maxHealth;
	level = _level;
	regenRate = _regenRate;
}

void Monster::TakeDamage(int damage)
{
	health -= damage;
}

void Monster::EditMonster()
{
	cout << endl << "------ Edit Monster ------" << endl << endl;
	cout << "Monster's New Name: ";
	cin >> name;
	cout << "Monster's New Max Health: ";
	cin >> maxHealth;
	cout << "Monster's New Level: ";
	cin >> level;
	cout << "Monster's New Regeneration Rate: ";
	cin >> regenRate;
	cout << endl << "'" << name << "' has been edited." << endl;
	cout << "--------------------------" << endl << endl;

	health = maxHealth;
}

// Getters
string Monster::GetName() { return name; }
int Monster::GetHealth() { return health; }
int Monster::GetLevel() { return level; }
int Monster::GetRegenRate() { return regenRate; }

// Setters
void Monster::SetName(string _name) { name = _name; }
void Monster::SetHealth(int _health) { health = _health; }
void Monster::SetLevel(int _level) { level = _level; }
void Monster::SetRegenRate(int _regenRate) { regenRate = _regenRate; }