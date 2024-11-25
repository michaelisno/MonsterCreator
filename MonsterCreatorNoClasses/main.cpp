#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

const int maxMonsterCount = 5;
const int defaultPlayerDamage[] = { 10, 40 };

struct Monster
{
	string monsterName = "";

	int monsterHealth;
	int monsterMaxHealth;
	int monsterRegenRate;
	int monsterLevel;
};

void SaveMonstersToFile(Monster monsters[], int numMonstersCreated)
{
	ofstream file("savedMonsters.txt");

	if (!file.is_open())
	{
		cout << "Error: Unable to open save monsters file." << endl;
		return;
	}

	for (int i = 0; i < numMonstersCreated; i++)
	{
		file << monsters[i].monsterName << "," << monsters[i].monsterHealth << "," << monsters[i].monsterMaxHealth
			<< "," << monsters[i].monsterLevel << "," << monsters[i].monsterRegenRate << endl;
	}

	file.close();

	cout << "Monsters saved to file." << endl;
}

int LoadMonstersFromFile(Monster monsters[])
{
	ifstream file("savedMonsters.txt");

	int numMonstersCreated = 0;

	if (!file.is_open())
	{
		cout << "Error: Unable to open save monsters file." << endl;
		return numMonstersCreated;
	}

	string line;
	while (getline(file, line) && numMonstersCreated < maxMonsterCount)
	{
		stringstream stream(line);

		string name, temp;
		int health, maxHealth, level, regenRate;

		getline(stream, name, ',');
		getline(stream, temp, ',');
		health = stoi(temp);
		getline(stream, temp, ',');
		maxHealth = stoi(temp);
		getline(stream, temp, ',');
		level = stoi(temp);
		getline(stream, temp, ',');
		regenRate = stoi(temp);

		monsters[numMonstersCreated] = { name, health, maxHealth, regenRate, level };
		numMonstersCreated++;
	}

	file.close();

	return numMonstersCreated;
}

void PrintFileToConsole(string fileName)
{
	ifstream file("Console Outputs/" + fileName);

	if (!file.is_open())
		return;

	string content;
	char ch;

	while (file.get(ch))
	{
		cout << ch;
	}

	file.close();
}

void InitMonster(Monster& monster, int& numMonstersCreated, bool isEditingMonster = false)
{
	if (numMonstersCreated < maxMonsterCount)
	{
		if (!isEditingMonster)
		{
			cout << "---- Create a Monster ----" << endl;
			numMonstersCreated++;
		}

		int health;
		int level;
		int regenRate;
		string name;

		cout << "Enter Monsters Name: ";
		cin >> name;
		cout << "Enter Monsters Max Health: ";
		cin >> health;
		cout << "Enter Monsters Level: ";
		cin >> level;
		cout << "Enter Monsters Regen Rate (per second): ";
		cin >> regenRate;

		cout << endl << "Monster: " << name << " has been initiated." << endl << "--------------------------" << endl;

		monster.monsterName = name;
		monster.monsterHealth = health;
		monster.monsterMaxHealth = health;
		monster.monsterLevel = level;
		monster.monsterRegenRate = regenRate;
	}
	else
	{
		cout << "Cannot created anymore Monsters. The maximum limmit has been reached." << endl;
	}
}

void DisplayMonsters(Monster monsters[], int numMonstersCreated)
{
	if (numMonstersCreated == 0)
	{
		cout << "Error: No Monsters created yet." << endl;
		return;
	}

	cout << endl << "---- List of Monsters ----" << endl;

	for (int i = 0; i < maxMonsterCount; i++)
	{
		if (monsters[i].monsterName != "")
		{
			cout << "---- Monster " << i + 1 << ": ----" << endl;
			cout << "Name: " << monsters[i].monsterName << endl;
			cout << "Health: " << monsters[i].monsterHealth << endl;
			cout << "Level: " << monsters[i].monsterLevel << endl;
			cout << "Regen Rate: " << monsters[i].monsterRegenRate << endl;
			cout << "--------------------" << endl;
		}
	}
}

void EditMonster(Monster monsters[], int& numMonstersCreated)
{
	if (numMonstersCreated == 0)
	{
		cout << "Error: No Monsters created yet." << endl;
		return;
	}

	cout << "---- Edit a Monster ----" << endl << "Name of Monster: ";

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

	if (monsterIndex >= 0 && monsterIndex <= maxMonsterCount)
	{
		cout << endl << "-- Current Stats --" << endl;
		cout << "Monster: " << monsters[monsterIndex].monsterName << endl;
		cout << "Health: " << monsters[monsterIndex].monsterHealth << endl;
		cout << "Level: " << monsters[monsterIndex].monsterLevel << endl;
		cout << "Regen Rate: " << monsters[monsterIndex].monsterRegenRate << endl << endl;
		cout << "-- New Stats -- " << endl;

		InitMonster(monsters[monsterIndex], numMonstersCreated, true);
	}
}

void DamageMonster(Monster& monster, int damage)
{
	int monsterLevel = monster.monsterLevel;

	int damageToDeal = static_cast<int>(round(damage / monsterLevel));

	monster.monsterHealth -= damageToDeal;
}

void RegenerateMonsterHealth(time_point<steady_clock>& lastRegenTime, Monster& monster)
{
	int timeSinceLastRegen = static_cast<int>(duration_cast<seconds>(steady_clock::now() - lastRegenTime).count());

	if (timeSinceLastRegen > 0)
	{
		monster.monsterHealth += (timeSinceLastRegen * monster.monsterRegenRate);

		if (monster.monsterHealth > monster.monsterMaxHealth)
			monster.monsterHealth = monster.monsterMaxHealth;

		lastRegenTime += seconds(timeSinceLastRegen);
	}
}

void FightSpecificMonster(Monster& monster)
{
	cout << endl << "You are fighting: " << monster.monsterName << endl;
	cout << "Due to " << monster.monsterName << "'s level: " << monster.monsterLevel << ", Your light attack is: "
		<< round(defaultPlayerDamage[0] / monster.monsterLevel) << "hp, Your heavy attack is: "
		<< round(defaultPlayerDamage[1] / monster.monsterLevel) << "hp." << endl;

	bool isMonsterDead = false;
	int currentAttackCount = 0;

	time_point<steady_clock> lastRegenTime = steady_clock::now();

	while (!isMonsterDead)
	{
		if (monster.monsterHealth < monster.monsterMaxHealth)
			RegenerateMonsterHealth(lastRegenTime, monster);

		cout << "Monster: " << monster.monsterName << "'s Health: " << monster.monsterHealth << endl << endl << "Light attack (l) or Heavy Attack (h): ";

		string userInput;
		cin >> userInput;

		cout << endl;

		if (userInput == "l")
		{
			DamageMonster(monster, defaultPlayerDamage[0]);
			currentAttackCount++;
		}
		else if (userInput == "h")
		{
			if (currentAttackCount >= 3)
			{
				DamageMonster(monster, defaultPlayerDamage[1]);
				currentAttackCount = 0;
			}
			else
			{
				cout << "You can only Heavy Attack every three attacks." << endl;
			}
		}
		else
		{
			cout << "Invalid attack option." << endl;
		}

		if (monster.monsterHealth <= 0)
			isMonsterDead = true;
	}

	if (isMonsterDead)
		cout << "You have successfully defeated Monster: " << monster.monsterName << endl;
}

void FightMonsters(Monster monsters[], int& numMonstersCreated)
{
	if (numMonstersCreated == 0)
	{
		cout << "Error: No Monsters created yet." << endl;
		return;
	}

	cout << "---- Fight the Monster(s) ----" << endl;
	cout << "Default light attack: 15hp. Default heavy attack: 40hp." << endl << endl;

	DisplayMonsters(monsters, numMonstersCreated);

	cout << endl << "Choose which Monster you want to fight first (number): ";

	int userInput;
	cin >> userInput;
	userInput--;

	if (userInput <= maxMonsterCount && monsters[userInput].monsterName != "")
	{
		FightSpecificMonster(monsters[userInput]);
		numMonstersCreated--;

		for (int i = userInput; i < maxMonsterCount - 1; i++)
			monsters[i] = monsters[i + 1];

		SaveMonstersToFile(monsters, numMonstersCreated);

		if (numMonstersCreated == 0)
		{
			PrintFileToConsole("AllMonstersDefeated.txt");
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
		cout << "Invalid choice." << endl << endl;
		FightMonsters(monsters, numMonstersCreated);
	}
}

int GetUserInput()
{
	int userOption = -1;

	while (true)
	{
		PrintFileToConsole("UserMenuOptions.txt");

		cin >> userOption;

		if (cin.fail())
		{
			cout << "Error: Invalid input. Please enter a number." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
		{
			break;
		}
	}

	return userOption;
}

void HandleUserOption(int userOption, int& numMonstersCreated, Monster monsters[], bool& isGameOver)
{
	switch (userOption)
	{
	case 1:
		InitMonster(monsters[numMonstersCreated], numMonstersCreated);
		break;
	case 2:
		EditMonster(monsters, numMonstersCreated);
		break;
	case 3:
		DisplayMonsters(monsters, numMonstersCreated);
		break;
	case 4:
		FightMonsters(monsters, numMonstersCreated);
		break;
	case 5:
		isGameOver = true;
		break;
	default:
		cout << "Error: Invalid Option." << endl;
		HandleUserOption(GetUserInput(), numMonstersCreated, monsters, isGameOver);
		break;
	}
}

int main()
{
	cout << "Welcome to Monster Creator!" << endl;

	Monster monsters[maxMonsterCount];

	int numMonstersCreated = LoadMonstersFromFile(monsters);
	bool isGameOver = false;

	while (!isGameOver)
	{
		HandleUserOption(GetUserInput(), numMonstersCreated, monsters, isGameOver);
	}

	SaveMonstersToFile(monsters, numMonstersCreated);

	return 0;
}
