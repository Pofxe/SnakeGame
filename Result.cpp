#include "Result.h"

void Result::resultGameIn(string n, int s)
{
	ofstream in(FILE, ios_base::app);

	if (in.is_open() != true) { cout << "Ошибка открытия файла!" << endl; exit(0); } // если файл не открылся,то выводим сообщение и выходим из программы
	if (in.is_open() == true) { in << n << " " << s << endl; } // если файл открылся,то записываем в него данные

	in.close(); // закрываем файл
}

void Result::resultGameOut()
{
	ifstream out(FILE);
	string str = "";

	if (out.is_open() == true) // проверяем на открытость файла
	{
		while (getline(out, str)) // построчно считываем из файла и записываем в переменную
		{
			string n = "";
			int s = 0;
			
			for (int i = 0; i < str.size(); i++) // проходимся циклом по записанным строкам
			{
				if (str[i] != ' ') // если не пробел
				{
					n += str[i]; // записываем в переменную для имени 
				}
				else // в противном случае
				{
					s = stoi(str.substr(i + 1)); // записываем в переменную очков
					break;
				}
			}
			table.push_back({ n, s }); // создаем пару и записываем ее в конец вектора
		}
	}
	out.close(); // закрываем файл

	sort(table.begin(), table.end(), [](const pair<string, int>& p1, const pair<string, int>& p2)
		{
			if (p1.second != p2.second)
			{
				// сравниваем вторые значения
				return p1.second > p2.second;
			}
			// сравниваем первые, если вторые значения равны
			return p1.first < p2.first;
		}
	);

	for (const auto& [n, s] : table) // проходимся по коллекции
	{
		cout << n << " " << s << endl; // и выводим её
	}
}