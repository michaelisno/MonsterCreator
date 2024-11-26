#pragma once
#include <vector>
#include "Monster.h"
#include "GameData.h"
#include "FileManager.h"

class GameManager
{
private:
	FileManager fileManager;
	GameData gameData;

public:
	GameManager(GameData _gameData, FileManager _fileManager);

	int GameLoop();

	Monster* CreateMonster();
	void DisplayMonsters(std::vector<Monster*> monsters);
	void EditMonsters(std::vector<Monster*>& monsters);
	void ChooseMonsterToFight(std::vector<Monster*>& monsters);

	int FightMonster(Monster*& monster);

	void HandlePlayerInput(int userOption, std::vector<Monster*>& monsters, int maxMonsterCount, bool& isGameEnded);
	int GetPlayerInput();

};