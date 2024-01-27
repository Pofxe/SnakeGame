#pragma once

#include "Snake.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

class Result
{
private:

#define FILE "D:\\resultGame.txt" // файл для записи
	vector<pair<string, int>> table; // пара для результатов

public:

	Result() = default;
	void resultGameIn(string, int);
	void resultGameOut();
	~Result() {};

};

