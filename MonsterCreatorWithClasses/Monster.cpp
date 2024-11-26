#include <iostream>
#include "Monster.h"

using namespace std;
using namespace chrono;

Monster::Monster(string _name, int _health, int _maxHealth, int _level, int _regenRate)
{
	name = _name;
	health = _health;
	maxHealth = _maxHealth;
	level = _level;
	regenRate = _regenRate;
}

void Monster::TakeDamage(int damage)
{
	health -= static_cast<int>(round(damage / level));
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

int Monster::FightMonster(GameData gameData)
{
	cout << "----- Fighting '" << name << "' -----" << endl << "Health: " << health << endl << "Light attack: "
		<< round(gameData.playerDamage[0] / level) << "hp, Heavy Attack: "
		<< round(gameData.playerDamage[1] / level) << "hp" << endl;

	bool isMonsterDead = false;
	int currentAttackCount = 0;

	time_point<steady_clock> lastRegenTime = steady_clock::now();

	while (!isMonsterDead)
	{
		if (health <= 0)
			return 0;

		if (health < maxHealth)
			RegenerateHealth(lastRegenTime);

		cout << "Current Health: " << health << endl;
		cout << "Enter 'l' or 'h' for light/heavy attack. Enter 'back' to leave." << endl;
		cout << ">>";

		string userOption;
		cin >> userOption;

		if (userOption == "back")
		{
			return 1;
		}

		if (userOption == "l")
		{
			TakeDamage(gameData.playerDamage[0]);
			currentAttackCount++;
		}
		else if (userOption == "h")
		{
			if (currentAttackCount >= gameData.heavyAttackCount)
			{
				TakeDamage(gameData.playerDamage[1]);
				currentAttackCount = 0;
			}
			else
			{
				cerr << "Error: You can only perform a heavy attack every " << gameData.heavyAttackCount << " attacks." << endl;
			}
		}
		else
		{
			cerr << "Error: Invalid option. Please enter either 'l', 'h' or 'back'." << endl;
		}
	}

	return -1;
}

void Monster::RegenerateHealth(time_point<steady_clock>& lastRegenTime)
{
	int timeSinceLastRegen = static_cast<int>(duration_cast<seconds>(steady_clock::now() - lastRegenTime).count());

	if (timeSinceLastRegen > 0)
	{
		health += (timeSinceLastRegen * regenRate);

		if (health > maxHealth)
			health = maxHealth;

		lastRegenTime += seconds(timeSinceLastRegen);
	}
}

// Getters
string Monster::GetName() { return name; }
int Monster::GetHealth() { return health; }
int Monster::GetLevel() { return level; }
int Monster::GetRegenRate() { return regenRate; }
int Monster::GetMaxHealth() { return maxHealth; }

// Setters
void Monster::SetName(string _name) { name = _name; }
void Monster::SetHealth(int _health) { health = _health; }
void Monster::SetLevel(int _level) { level = _level; }
void Monster::SetRegenRate(int _regenRate) { regenRate = _regenRate; }
void Monster::SetMaxHealth(int _maxHealth) { maxHealth = _maxHealth; }