/*
Теория принятия решения
Множество Парето, метод прямоугольника
nn, x, y
*/

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
	string fname, s_temp;
	cout << "type in file's name" << endl;
	cin >> fname;
	
	//читаем
	map<string, vector<double>> dots;
	std::ifstream in(fname, ifstream::in);
	double x, y;
	int n = 0;
	while (in.good())
	{
		if(n==0) //skip the header 
		{	
			n++;
			continue;
		}
		in >> s_temp >> x >> y;
		dots[s_temp].push_back(x);
		dots[s_temp].push_back(y);
		n++;
	}
	in.close();
	
	map<string, vector<double>> res;
	
	
	return 0;
}
