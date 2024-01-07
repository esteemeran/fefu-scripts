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
#include <algorithm>
#include <iomanip>

using namespace std;



void show(map<int, vector<long double>> &graph)
//void show(map<string, vector<string>> &graph)
{
	//вывод текущих списков смежности в читабельном виде.
	for (const auto &kvp : graph)
	{
		cout << kvp.first << "\t";
		for (auto v : kvp.second)
			cout << std::setprecision(15) << v << "\t";
		cout << endl;
	}
	cout << endl;
}

int main() {
	map<int, vector<long double>> dots;

	//читаем
	{
		string fname;
		//cout << "type in file's name" << endl;
		//cin >> fname;
		fname = "data.txt";

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
			nn.erase(remove(nn.begin(), nn.end(), '"'), nn.end());
			n = stoi(nn);
			dots[n].push_back(x);
			dots[n].push_back(y);
		}
		in.close();
	}
	map<int, vector<long double>> res; //тП's
	
	show(dots);
	
	while (dots.size() != 0)
	{
		if (dots.size() == 1)
		{
			for (auto cd : dots)
			{
				res[cd.first].push_back(cd.second[0]);
				res[cd.first].push_back(cd.second[1]);
			}
			dots.clear();
			break;
		}

		long double x1, y1, x2, y2;
		int n1, n2;
		bool start = true;
		
		for (auto cd : dots)
		{
			if (start)
			{
				n1 = cd.first;
				x1 = cd.second[0];
				y1 = cd.second[1];
				n2 = cd.first;
				x2 = cd.second[0];
				y2 = cd.second[1];
				start = false;
			}
			if (cd.second[0] < x1 || (cd.second[0] == x1 && cd.second[1] < y1))
			{
				n1 = cd.first;
				x1 = cd.second[0];
				y1 = cd.second[1];
			}
			if (cd.second[1] < y2 || (cd.second[0] == y2 && cd.second[1] < x2))
			{
				n2 = cd.first;
				x2 = cd.second[0];
				y2 = cd.second[1];
			}
		}
		res[n1].push_back(x1);
		res[n1].push_back(y1);
		res[n2].push_back(x2);
		res[n2].push_back(y2);
	
		cout << n1 << "\t" << std::setprecision(15) <<  x1 << "\t" << std::setprecision(15) << y1 << endl;
		cout << n2 << "\t" << std::setprecision(15) << x2 << "\t" << std::setprecision(15) << y2 << endl;
		cout << endl;

		vector<int> del;// = { n1, n2 };
		long double xmin, ymin, xmax, ymax;
		xmin = min(x1, x2);
		ymin = min(y1, y2);
		xmax = max(x1, x2);
		ymax = max(y1, y2);

		for (auto cd : dots)
		{
			auto x = cd.second[0];
			auto y = cd.second[1];
			if ((x <= xmin || y <= ymin) ||
				(x >= xmax || y >= ymax))
			{
				del.push_back(cd.first);
				cout << cd.first << " ";
			}
		}
		cout << endl;
		for (auto i : del) dots.erase(i);
		show(dots);
	}
	show(res);

	return 0;
}
