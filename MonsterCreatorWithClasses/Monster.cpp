#include <iostream>
#include "Monster.h"

using namespace std;
using namespace chrono;

Monster::Monster(string name, int health, int maxHealth, int level, int regenRate)
{
	m_name = name;
	m_health = health;
	m_maxHealth = maxHealth;
	m_level = level;
	m_regenRate = regenRate;
}

void Monster::TakeDamage(int damage)
{
	m_health -= static_cast<int>(round(damage / m_level));
}

void Monster::EditMonster()
{
	cout << endl << "------ Edit Monster ------" << endl << endl;
	cout << "Monster's New Name: ";
	cin >> m_name;
	cout << "Monster's New Max Health: ";
	cin >> m_maxHealth;
	cout << "Monster's New Level: ";
	cin >> m_level;
	cout << "Monster's New Regeneration Rate: ";
	cin >> m_regenRate;
	cout << endl << "'" << m_name << "' has been edited." << endl;
	cout << "--------------------------" << endl << endl;

	m_health = m_maxHealth;
}

int Monster::FightMonster(GameData gameData)
{
	cout << "----- Fighting '" << m_name << "' -----" << endl << "Health: " << m_health << endl << "Light attack: "
		<< round(gameData.playerLightDamage / m_level) << "hp, Heavy Attack: "
		<< round(gameData.playerHeavyDamage / m_level) << "hp" << endl;

	bool isMonsterDead = false;
	int currentAttackCount = 0;

	time_point<steady_clock> lastRegenTime = steady_clock::now();

	while (!isMonsterDead)
	{
		if (m_health <= 0)
			return 0;

		if (m_health < m_maxHealth)
			RegenerateHealth(lastRegenTime);

		cout << "Current Health: " << m_health << endl << "Enter 'l' or 'h' for light/heavy attack. Enter 'back' to leave." << endl << ">>";

		string userOption;
		cin >> userOption;

		if (userOption == "back")
			return 1;

		if (userOption == "l")
		{
			TakeDamage(gameData.playerLightDamage);
			currentAttackCount++;
		}
		else if (userOption == "h")
		{
			if (currentAttackCount >= gameData.heavyAttackCount)
			{
				TakeDamage(gameData.playerHeavyDamage);
				currentAttackCount = 0;
			}
			else
			{
				cerr << "Error: You can only perform a heavy attack every " << gameData.heavyAttackCount << " attacks." << endl;
			}
		}
		else
		{
			cerr << "Error: Invalid option. Please enter 'l', 'h' or 'back'." << endl;
		}
	}

	return -1;
}

void Monster::RegenerateHealth(time_point<steady_clock>& lastRegenTime)
{
	int timeSinceLastRegen = static_cast<int>(duration_cast<seconds>(steady_clock::now() - lastRegenTime).count());

	if (timeSinceLastRegen > 0)
	{
		m_health += (timeSinceLastRegen * m_regenRate);

		if (m_health > m_maxHealth)
			m_health = m_maxHealth;

		lastRegenTime += seconds(timeSinceLastRegen);
	}
}