#pragma once
#include <string>
#include <vector>
#include "Monster.h"

class FileManager
{
public:
	std::string coutPath;
	std::string savePath;

	void PrintFileToConsole(std::string filePath);

	void SaveGame(std::vector<Monster*>& monsters);
	void LoadGame(std::vector<Monster*>& monsters, int maxMonsterCount);
};