#include <iostream>
#include "GameManager.h"
#include "FileManager.h"
#include "GameData.h"

using namespace std;

int main()
{
	// Pre-Game Setup
	GameData gameData;
	gameData.maxMonsterCount = 5;
	gameData.playerDamage = { 15, 40 };
	gameData.heavyAttackCount = 3;

	FileManager fileManager;
	fileManager.coutPath = "Console Outputs/";
	fileManager.savePath = "Saves/";

	// Creation of game manager auto starts game
	GameManager* gameManager = new GameManager(gameData, fileManager);

	// When game is 'quit' this runs
	delete gameManager;
	gameManager = nullptr;

	return 0;
}

