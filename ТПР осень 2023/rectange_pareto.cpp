/*
Теория принятия решения
Множество Парето, метод прямоугольника, мин мин

описание:
на вход файл
	nn, x, y
	строка, 2 - число 14 после запятой
считаваем, получаем массив точек
цикл
	берем мин по х (и там мин по у) = тП
	берем мин по у (и там мин по х) = тП
	отбрасываем все точки меньше или равно этим двум
выводим тП
*/

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void show(map<string, vector<long double>> &graph)
//void show(map<string, vector<string>> &graph)
{
	//вывод текущих списков смежности в читабельном виде.
	for (const auto &kvp : graph)
	{
		cout << kvp.first << "\t: ";
		for (auto v : kvp.second)
			cout << v << " ";
		cout << endl;
	}
}

int main() {
	string fname;
	//cout << "type in file's name" << endl;
	//cin >> fname;
	fname = "data.txt";

	//читаем
	map<string, vector<long double>> dots;
	//map<string, vector<string>> dots;
	ifstream in(fname, ifstream::in);
	long double x, y;
	int n = 0;
	string nn, xt, yt;
	while (in.good())
	{
		if (n == 0) //skip the header 
		{
			in >> xt >> yt;
			n++;
			continue;
		}
		in >> nn >> xt >> yt;
		x = stold(xt);
		y = stold(yt);
		cout << nn << "\t" << x << y << endl;
		dots[nn].push_back(x);
		dots[nn].push_back(y);
		n++;
	}
	in.close();

	show(dots);

	map<string, vector<long double>> res;


	return 0;
}
