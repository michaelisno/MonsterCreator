#include <iostream>
#include <fstream>
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