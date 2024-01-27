#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Snake
{
private:
	static const int mapWidth = 20; // ширина
	static const int mapHeigth = 40; // высота
	static const int size = mapWidth * mapHeigth; // размер карты
	int map[size]{}; // сама карта

	int headXPos; // позиция головы по Х
	int headYPos; // позиция головы по У
	int direction; // направление движения

	int speed; // скорость змеи

    int food; // количество съеденных фруктов и по совместительству длина змейки

	bool running; // работает ли игра

	int fruitX;
	int fruitY;

public:

	int score; // количество очков

	Snake();

	void printMap();
	void initMap();
	void move(int, int);
	void update();
	void changeDirection(char);
	void generateFood();
	char getMapValue(int);
	void run();
};

