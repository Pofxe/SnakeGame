#include "Snake.h"

Snake::Snake() // конструктор по умолчанию
{
	headXPos = mapWidth / 2 - 1; // голова распологается посередине карты
	headYPos = mapHeigth / 2 - 1;

	direction = 0; // движение изначально вверх

	food = 1; // 1 деление у змейки в начале игры(только голова)

	score = 0; // изначально 0 очков

	speed = 600; // начальная скорость

	running = true; // игра работает

	fruitX = 0;
	fruitY = 0;
}

void Snake::printMap() // показ карты
{
	for (int i = 0; i < mapWidth; ++i)
	{
		for (int j = 0; j < mapHeigth; ++j)
		{
			cout << getMapValue(map[i + j * mapWidth]); // обрабатывает значение,что бы показать на карте нужную фигуру
		}
		cout << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << endl << "Координаты головы : " << '(' << headXPos << ';' << headYPos << ")\t"; // показывает координаты головы
	cout << "Координаты еды: " << '(' << fruitX << ';' << fruitY << ")" << endl;
	cout << "Очки : " << score << endl;
	cout << "Текущая скорость : " << speed << endl;
}

void Snake::initMap() // инициализация карты
{
	map[headXPos + headYPos * mapWidth] = 1; // примем карту за единицу

	for (int i = 0; i < mapWidth; ++i) // инициализируем верхнюю и нижнюю границы
	{
		map[i] = -1;
		map[i + (mapHeigth - 1) * mapWidth] = -1;
	}

	for (int j = 0; j < mapHeigth; j++) // инициализирем правую и левую границы
	{
		map[0 + j * mapWidth] = -1;
		map[(mapWidth - 1) + j * mapWidth] = -1;
	}

	generateFood(); // генерируем фрукт
}

void Snake::move(int dx, int dy) // перемещение 
{
	int newX = headXPos + dx; // новое положение головы по Х
	int newY = headYPos + dy; // новое положение головы по У

	if (map[newX + newY * mapWidth] == -2) // проверяем что еда съедена
	{
		food++; // увеличиваем тело на единицу
		score += 10; // добавляем 10 очков
		speed -= 3; // увеличиваем скорость

		generateFood(); // генерируем новый фрукт
	}

	else if (map[newX + newY * mapWidth] != 0) // если голова уперлась в ограждение
	{
		running = false; // конец игры
	}

	headXPos = newX; // перезаписываем положение головы по Х
	headYPos = newY; // перезаписываем положение головы по У
	map[headXPos + headYPos * mapWidth] = food + 1; // добавляет на карте более длинную змейку
}

void Snake::update() // обновление карты
{
	switch (direction) // движение в указанном направлении
	{
	case 0: move(-1, 0); break;

	case 1: move(0, 1); break;

	case 2: move(1, 0); break;

	case 3: move(0, -1); break;
	}

	for (int i = 0; i < size; i++) // уменьшение змеи на карте
	{
		if (map[i] > 0)
		{
			map[i]--;
		}
	}
}

void Snake::changeDirection(char key) // управление
{
	switch (key)
	{
	case 'w': if (direction != 2) { direction = 0; } break;
	case 'd': if (direction != 3) { direction = 1; } break;
	case 's': if (direction != 4) { direction = 2; } break;
	case 'a': if (direction != 5) { direction = 3; } break;

	case 'p': system("pause"); break; // пауза
	case 'm': running = false; break; // выход
	}
}

void Snake::generateFood() // генерация еды
{
	do // задаём цикл для постоянной генерации
	{
		fruitX = rand() % (mapWidth - 2) + 1; // генерируем в случайных позициях
		fruitY = rand() % (mapHeigth - 2) + 1;

	} while (map[fruitX + fruitY * mapWidth] != 0); // пока место не занято

	map[fruitX + fruitY * mapWidth] = -2; // размещаем новую еду на карте
}

char Snake::getMapValue(int value) // установка значений для символов
{
	if (value > 0) // если значение больше нуля то тело змеи
	{ 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 36); 
		return 'O';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	} 

	switch (value) // проверяем значение
	{
	case -1: // если -1 то граница поля
	{ 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32);
		return '#';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	} 
	case -2: // если -2 то еда
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 37);
		return 'o';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	} 
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34);
	return ' '; // поле заполненно пробелами
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Snake::run() // сама игра
{
	initMap(); // инициализируем карту

	while (running) // пока игра истинна
	{

		if (_kbhit()) // проверяем нажатие клавиши
		{
			changeDirection(_getch()); // сразу же обрабатываем нажатую клавишу
		}

		update(); // обновляем карту
		system("cls"); // очищаем экран
		printMap(); // выводим карту
		Sleep(speed); // делаем небольшую задeржку
	}
}
