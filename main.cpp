#include "Snake.h"
#include "Result.h"


inline void cursor() // для того что бы курсор не бегал по экрану
{
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

inline void gotoxy(int x, int y) // установка курсора в нужную позицию
{
	COORD scrn;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = x;
	scrn.Y = y;

	SetConsoleCursorPosition(hOutput, scrn);
}

inline void title() // описание и управление 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	cout << "Управление : " << endl;
	cout << "+=======+==========+\n"
		"|a      |Влево     |\n"
		"|d      |Вправо    |\n"
		"|s      |Вниз      |\n"
		"|w      |Вверх     |\n"
		"|p      |Пауза     |\n"
		"|m      |Выход     |\n"
		"+=======+==========+\n\n";

	cout << "За каждый съеденный фрукт Вы получаете 1 очко и к хвосту добавляется одно деление." << endl;
	cout << "При соприкосновении с границей поля змейка погибает и игра заканчивается." << endl;
	cout << "Чем ниже показатель скорости,тем быстрее будет двигаться змейка." << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int user = 0; // выбор пользователя
	bool menu = true; // для работы с меню
	string name = ""; // имя игрока
	int sc = 0; // количество очков 

	Snake s; // объект класса змейки
	Result r; // объект класса обрабоки результатов

	cout << "Введите имя : ";
	cin >> name;
	cout << endl;

	do
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		cout << "    Меню" << endl;
		cout << "1.Начать игру" << endl;
		cout << "2.Показать результаты" << endl;
		cout << "3.Описание" << endl;
		cout << "4.Выйти из игры" << endl;
		cin >> user;

		system("cls");

		switch (user)
		{
		case 1:
		{
			cursor();
			gotoxy(0, 0);

			s.run(); // начинаем игру

		    sc = s.score; // получаем количество очков
			
			r.resultGameIn(name, sc); // записываем результат игры

			system("pause");
		}
		break;

		case 2:
		{
			r.resultGameOut(); // выводим отсортированный результат игры

			system("pause");
		}
		break;

		case 3:
		{
			title(); // показываем правила и управление
			system("pause");
		}
		break;

		case 4:
		{
			menu = false; // выход из игры
		}
		break;

		} 
	}while (menu); // цикл продолжается пока не нажата клавиша выхода из меню
}