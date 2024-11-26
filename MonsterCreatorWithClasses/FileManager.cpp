#include <iostream>
#include <fstream>
#include <sstream>
#include "FileManager.h"

using namespace std;

void FileManager::PrintFileToConsole(string filePath)
{
	ifstream file(coutPath + filePath);

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

void FileManager::SaveGame(vector<Monster*>& monsters)
{
	ofstream file(savePath);

	if (!file.is_open())
	{
		cerr << "Error: Unable to open save monsters file." << endl;
		return;
	}

	for (int i = 0; i < monsters.size(); i++)
	{
		file << monsters[i]->GetName() << "," << monsters[i]->GetHealth() << "," << monsters[i]->GetMaxHealth()
			<< "," << monsters[i]->GetLevel() << "," << monsters[i]->GetRegenRate() << endl;
	}

	file.close();
}

void FileManager::LoadGame(vector<Monster*>& monsters, int maxMonsterCount)
{
	ifstream file(savePath);

	if (!file.is_open())
	{
		cout << "Error: Unable to open save monsters file." << endl;
		return;
	}

	string line;
	while (getline(file, line) && monsters.size() < maxMonsterCount)
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

		Monster* monster = new Monster(name, health, maxHealth, level, regenRate);
		monsters.push_back(monster);
	}

	file.close();
}