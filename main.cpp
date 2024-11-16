#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

const int maxMonsterCount = 5;

struct Monster
{
	string monsterName = "";
	int monsterHealth;
	int monsterMaxHealth;
	int monsterRegenRate;
	int monsterLevel;
};

void InitMonster(Monster& monster)
{
	int health;
	int level;
	int regenRate;
	string name;

	cout << "Enter Monsters Name: ";
	cin >> name;
	cout << "Enter Monsters Health: ";
	cin >> health;
	cout << "Enter Monsters Level: ";
	cin >> level;
	cout << "Enter Monsters Regen Rate (per second): ";
	cin >> regenRate;

	cout << endl << "Monster: " << name << " has been created." << endl << "--------------------------" << endl;

	monster.monsterName = name;
	monster.monsterHealth = health;
	monster.monsterMaxHealth = health;
	monster.monsterLevel = level;
	monster.monsterRegenRate = regenRate;
}

void DisplayMonsters(Monster monsters[])
{
	for (int i = 0; i < maxMonsterCount; i++)
	{
		if (monsters[i].monsterName != "") 
		{
			cout << "---- Monster " << i + 1 << ": ----" << endl;
			cout << "Name: " << monsters[i].monsterName << endl;
			cout << "Health: " << monsters[i].monsterHealth << endl;
			cout << "Level: " << monsters[i].monsterLevel << endl;
			cout << "--------------------" << endl;
		}
	}
}

void EditMonster(Monster monsters[])
{
	cout << "---- Edit a Monster ----" << endl;
	cout << "Name of Monster: ";

	string monsterName;
	cin >> monsterName;

	int monsterIndex = NULL;

	for (int i = 0; i < maxMonsterCount; i++)
	{
		if (monsterName == monsters[i].monsterName)
		{
			monsterIndex = i;
			break;
		}
	}

	if (monsterIndex != NULL)
	{
		cout << endl << "-- Current Stats --" << endl;
		cout << "Monster: " << monsters[monsterIndex].monsterName << endl;
		cout << "Health: " << monsters[monsterIndex].monsterHealth << endl;
		cout << "Level: " << monsters[monsterIndex].monsterLevel << endl << endl;
		cout << "-- New Stats -- " << endl;

		InitMonster(monsters[monsterIndex]);
	}
}

void DamageMonster(Monster& monster, int damage)
{
	monster.monsterHealth -= damage;
}

void FightSpecificMonster(Monster& monster)
{
	cout << endl << "You are fighting: " << monster.monsterName << endl;

	bool isMonsterDead = false;
	int currentAttackCount = 0;

	auto lastRegenTime = chrono::steady_clock::now();

	while (!isMonsterDead)
	{
		auto currentTime = chrono::steady_clock::now();
		auto timeSinceLastRegen = chrono::duration_cast<chrono::seconds>(currentTime - lastRegenTime).count();
		
		if (timeSinceLastRegen > 0)
		{
			int regenAmount = timeSinceLastRegen * monster.monsterRegenRate;
			monster.monsterHealth += regenAmount;

			if (monster.monsterHealth > monster.monsterMaxHealth)
				monster.monsterHealth = monster.monsterMaxHealth;

			lastRegenTime += chrono::seconds(timeSinceLastRegen);
		}

		cout << "Monsters Health: " << monster.monsterHealth << endl << endl;
		cout << "Light attack (l) or Heavy Attack (h): ";

		string userInput;
		cin >> userInput;

		cout << endl;

		if (userInput == "l")
		{
			DamageMonster(monster, 10);
			currentAttackCount++;
		}
		else if (userInput == "h")
		{
			if (currentAttackCount >= 3)
			{
				DamageMonster(monster, 35);
				currentAttackCount = 0;
			}
			else
				cout << "You can only Heavy Attack every three attacks." << endl;
		}
		else
			cout << "Invalid attack option." << endl;

		if (monster.monsterHealth <= 0)
			isMonsterDead = true;

		this_thread::sleep_for(chrono::milliseconds(10));
	}

	if (isMonsterDead)
		cout << "You have successfully defeated " << monster.monsterName << endl;
}

void FightMonsters(Monster monsters[], int& numMonstersCreated)
{
	cout << "---- Fight the Monster(s) ----" << endl << endl;
	cout << "List of Monsters to fight: " << endl;

	DisplayMonsters(monsters);

	cout << endl << "Choose which Monster you want to fight first (number): ";

	int userInput;
	cin >> userInput;
	userInput--;

	if (userInput <= maxMonsterCount)
	{
		if (monsters[userInput].monsterName != "")
		{
			FightSpecificMonster(monsters[userInput]);
			numMonstersCreated--;

			for (int i = userInput; i < maxMonsterCount - 1; i++)
			{
				monsters[i] = monsters[i + 1];
			}

			if (numMonstersCreated == 0)
			{
				cout << endl << "-----------------------------------------------" << endl;
				cout << "Well Done! You have successfully defeated\nall monsters and have won the game!" << endl;
				cout << "-----------------------------------------------" << endl << endl;
			}
			else
			{
				cout << "Do you want to keep fighting? (y/n): ";

				string input;
				cin >> input;

				if (input == "y")
					FightMonsters(monsters, numMonstersCreated);
			}
		}
		else
		{
			cout << "Error: That Monster does not exist." << endl << endl;
			FightMonsters(monsters, numMonstersCreated);
		}
	}
	else
	{
		cout << "Invalid choice." << endl << endl;
		FightMonsters(monsters, numMonstersCreated);
	}
}

int HandleUserOptions()
{
	cout << endl << "1 - Create a Monster" << endl;
	cout << "2 - Edit a Monster" << endl;
	cout << "3 - Display all Monsters" << endl;
	cout << "4 - FIGHT!" << endl;
	cout << "5 - Quit" << endl;

	cout << endl << "Option: ";

	int userOption;
	cin >> userOption;

	if (userOption >= 1 && userOption <= 5)
	{
		cout << endl;
		return userOption;
	}
	else
	{
		cout << "Error: Invalid Option." << endl << endl;
		return HandleUserOptions();
	}
}

int main()
{
	Monster monsters[maxMonsterCount];

	cout << "Welcome to Monster Creator!" << endl;

	int numMonstersCreated = 0;
	bool isGameOver = false;

	while (!isGameOver)
	{
		int userOption = HandleUserOptions();

		switch (userOption)
		{
			case 1:
				if (numMonstersCreated < maxMonsterCount) 
				{
					cout << "---- Create a Monster ----" << endl;
					InitMonster(monsters[numMonstersCreated]);
					numMonstersCreated++;
				}
				else
					cout << "Cannot created anymore Monsters. The maximum limmit has been reached." << endl;

				break;
			case 2:
				if (numMonstersCreated > 0)
					EditMonster(monsters);
				else
					cout << "Error: No Monsters created yet." << endl;

				break;
			case 3:
				if (numMonstersCreated > 0)
					DisplayMonsters(monsters);
				else
					cout << "Error: No Monsters created yet." << endl;

				break;
			case 4:
				if (numMonstersCreated > 0)
					FightMonsters(monsters, numMonstersCreated);
				else
					cout << "Error: No Monsters created yet." << endl;

				break;
			case 5:
				isGameOver = true;
			default:
				break;
		}
	}

	return 0;
}