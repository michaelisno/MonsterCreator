#include <iostream>
#include "GameManager.h"
#include "FileManager.h"
#include "GameData.h"

using namespace std;

int main()
{
	GameData gameData;
	gameData.maxMonsterCount = 5;
	gameData.playerLightDamage = 15;
	gameData.playerHeavyDamage = 40;
	gameData.heavyAttackCount = 3;

	FileManager fileManager;
	fileManager.coutPath = "Console Outputs/";
	fileManager.savePath = "Saves/saves.txt";

	GameManager* gameManager = new GameManager(gameData, fileManager);

	delete gameManager;
	gameManager = nullptr;

	return 0;
}

