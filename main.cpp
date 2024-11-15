#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int maxMonsterCount = 5;

struct Monster
{
	string monsterName = "";
	int monsterHealth;
};

void InitMonster(Monster& monster)
{
	int health;
	string name;

	cout << "Enter Monster's Health: ";
	cin >> health;
	cout << "Enter Monster's Name: ";
	cin >> name;
	cout << endl;

	monster.monsterName = name;
	monster.monsterHealth = health;
}

void DisplayMonster(Monster monsters[])
{
	cout << "Enter name of Monster to Display: ";
	string monsterName;
	cin >> monsterName;

	for (int i = 0; i < maxMonsterCount; i++)
	{
		if (monsterName == monsters[i].monsterName)
		{
			cout << "Monster: " << monsters[i].monsterName << endl;
			cout << "Health: " << monsters[i].monsterHealth << endl;
			 
			break;
		}
	}
}

int HandleUserOptions()
{
	cout << "1 - Create a Monster" << endl;
	cout << "2 - Edit a Monster" << endl;
	cout << "3 - Display all Monsters" << endl;
	cout << "4 - Quit" << endl;

	int userOption;
	cin >> userOption;
	return userOption;
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
				InitMonster(monsters[numMonstersCreated]);
				numMonstersCreated++;

				break;
			case 2:
				break;
			case 3:
				DisplayMonster(monsters);
				break;
			case 4:
				isGameOver = true;
			default:
				break;
		}
	}

	return 0;
}