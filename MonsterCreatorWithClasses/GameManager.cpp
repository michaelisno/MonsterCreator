#include <iostream>
#include "GameManager.h"

using namespace std;

GameManager::GameManager(GameData _gameData, FileManager _fileManager)
{
	gameData = _gameData;
	fileManager = _fileManager;

	GameLoop();
}

int GameManager::GameLoop()
{
	vector<Monster*> monsters;
	bool isGameEnded = false;

	cout << "------ Monster Creator ------" << endl;

	while (!isGameEnded)
	{
		HandlePlayerInput(GetPlayerInput(), monsters, gameData.maxMonsterCount, isGameEnded);
	}

	for (int i = 0; i < monsters.size(); i++)
	{
		delete monsters[i];
		monsters[i] = nullptr;
	}

	return 0;
}

Monster* GameManager::CreateMonster()
{
	string name;
	int maxHealth;
	int level;
	int regenRate;

	cout << endl << "----- Create a Monster -----" << endl;
	cout << "To Create a new Monster," << endl << "please enter the following: " << endl << endl;
	cout << "Monster's Name: ";
	cin >> name;
	cout << "Monster's Max Health: ";
	cin >> maxHealth;
	cout << "Monster's Level: ";
	cin >> level;
	cout << "Monster's Regeneration Rate: ";
	cin >> regenRate;

	Monster* monster = new Monster(name, maxHealth, level, regenRate);

	cout << endl << "'" << name << "' has been created." << endl;
	cout << "----------------------------" << endl << endl;

	return monster;
}

void GameManager::DisplayMonsters(vector<Monster*> monsters)
{
	cout << "---- List of Monsters ----" << endl;

	for (int i = 0; i < monsters.size(); i++)
	{
		cout << "#" << (i + 1) << " - Name: " << monsters[i]->GetName() << ", Health: " << monsters[i]->GetHealth() << ", Level: " <<
			monsters[i]->GetLevel() << ", Regeneration Rate: " << monsters[i]->GetRegenRate() << endl;
	}

	cout << "--------------------------" << endl << endl;
}

void GameManager::EditMonsters(vector<Monster*>& monsters)
{
	DisplayMonsters(monsters);

	cout << "Enter Number of Monster to Edit: ";
	int userInput;
	cin >> userInput;

	if (userInput < 1 || userInput > monsters.size())
	{
		cerr << "Error: That Monster does not exist." << endl;
		return;
	}

	monsters[userInput - 1]->EditMonster();
}

void GameManager::HandlePlayerInput(int userOption, vector<Monster*>& monsters, int maxMonsterCount, bool& isGameEnded)
{
	switch (userOption)
	{
	case 1:
		if (monsters.size() >= maxMonsterCount)
			cerr << "Error: Unable to create new monster as maximum number already created." << endl; break;

		monsters.push_back(CreateMonster());

		break;
	case 2:
		if (monsters.size() == 0)
			cerr << "Error: Unable to edit monsters as non have been created yet." << endl; break;

		EditMonsters(monsters);

		break;
	case 3:
		if (monsters.size() == 0)
			cerr << "Error: Unable to display monsters as non have been created yet." << endl; break;

		DisplayMonsters(monsters);

		break;
	case 4:
		// Fight Monsters
		break;
	case 5:
		isGameEnded = true;
		break;
	default:
		cout << "Error: Invalid Option." << endl;
		HandlePlayerInput(GetPlayerInput(), monsters, maxMonsterCount, isGameEnded);
		break;
	}
}

int GameManager::GetPlayerInput()
{
	int userOption = -1;

	while (true)
	{
		fileManager.PrintFileToConsole("menu.txt");

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