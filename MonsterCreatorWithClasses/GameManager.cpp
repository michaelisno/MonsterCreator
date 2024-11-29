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
	cout << "------ Monster Creator ------" << endl;

	vector<Monster*> monsters = {};
	fileManager.LoadGame(monsters, gameData.maxMonsterCount);

	bool isGameEnded = false;

	while (!isGameEnded)
	{
		HandlePlayerInput(GetPlayerInput(), monsters, gameData.maxMonsterCount, isGameEnded);
	}

	fileManager.SaveGame(monsters);

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

	Monster* monster = new Monster(name, maxHealth, maxHealth, level, regenRate);

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

void GameManager::ChooseMonsterToFight(vector<Monster*>& monsters)
{
	DisplayMonsters(monsters);

	cout << "Enter Which Number to Fight (or back to go back): " << endl;
	string userInput;
	cin >> userInput;

	if (userInput == "back")
		return;

	int option = stoi(userInput);

	cout << "Option : " << option << endl;
	cout << "MS : " << monsters.size() << endl;

	if (option < 1 || option > monsters.size()) 
	{
		cerr << "Error: Invalid option. Please choose a number in range." << endl;
		ChooseMonsterToFight(monsters);
	}

	int result = monsters[option - 1]->FightMonster(gameData);

	if (result == 0)
	{
		cout << "Monster '" << monsters[option - 1]->GetName() << "' has been defeated!" << endl;
		delete monsters[option - 1];
		monsters[option - 1] = nullptr;
		monsters.erase(monsters.begin() + option - 1);
	}
	else if (result == 1)
	{
		cout << "You have stopped fighting '" << monsters[option - 1]->GetName() << "'." << endl;
		cout << "Their health will be " << monsters[option - 1]->GetHealth() << " when you return." << endl;
		return;
	}
	else
	{
		cerr << "Error: An unkown error has occured.";
		return;
	}

	if (monsters.size() == 0)
		fileManager.PrintFileToConsole("won_game.txt");
}

void GameManager::HandlePlayerInput(int userOption, vector<Monster*>& monsters, int maxMonsterCount, bool& isGameEnded)
{
	switch (userOption)
	{
		case 1:
			if (monsters.size() >= maxMonsterCount) 
			{
				cerr << "Error: Unable to create new monster as maximum number already created." << endl;
				break;
			}

			monsters.push_back(CreateMonster());
			fileManager.SaveGame(monsters);

			break;
		case 2:
			if (monsters.size() == 0) 
			{
				cerr << "Error: Unable to edit monsters as none have been created yet." << endl; 
				break;
			}

			EditMonsters(monsters);
			fileManager.SaveGame(monsters);

			break;
		case 3:
			if (monsters.size() == 0)
			{
				cerr << "Error: Unable to display monsters as none have been created yet." << endl;
				break;
			}

			DisplayMonsters(monsters);

			break;
		case 4:
			if (monsters.size() == 0) 
			{
				cerr << "Error: Unable to fight monsters as none have been created yet." << endl;
				break;
			}

			ChooseMonsterToFight(monsters);
			fileManager.SaveGame(monsters);

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