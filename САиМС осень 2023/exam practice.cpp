/*
Теория игр. Множество оптимальных стратегий
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip> 
#include <vector>
using namespace std;

void printMatrix(vector <vector<int>> &m);
void getSubMatrix(vector <vector<int>> &m, vector <vector<int>> &bMatrix, int noLine, int noColm);

int main ()
{
	int n;
	ifstream fin ("input.txt");
	fin >> n;
	
	vector <vector<int>> m (n, vector<int>(n,0));
	for(int i = 0; i<n;i++)
		for(int j = 0; j<n;j++)
			{
				fin >> m[i][j];
			}
	fin.close(); //matrix

	//minmax fast check
	vector<int> minLine (n);
	vector<int> maxCol (n);
	for(int i = 0; i<n;i++)
		{
			auto me = min_element(m[i].begin(), m[i].end());
			minLine[i] = *me; //line
			
			int temp = m[i][0]; 
			for(int j = 0; j<n;j++)
				if(m[i][j] > temp) temp = m[i][j];
			maxCol[i] = temp; //colomn
		}
	auto a = max_element(minLine.begin(), minLine.end());
	auto b = min_element(maxCol.begin(), maxCol.end());
	if(*a==*b) cout << "saddle point, strategy ("<< distance(minLine.begin(), a) << ", " << distance(maxCol.begin(), b) << ")" << endl;
	else cout<<"no saddle points"<<endl;

	//subMatrixes
	
	// собираем подматрицу без тек строки-столбца
	int bsize = n-1;
	int noLine = 0, noColm = 0;
	vector <vector<int>> bMatrix (bsize, vector<int> (bsize, 0));
	getSubMatrix(m, bMatrix, noLine, noColm);
	printMatrix(bMatrix);

	//находим определитель матрицы
	// можно искать для матрицы любого размера, смотри https://ru.wikipedia.org/wiki/%D0%9E%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B8%D1%82%D0%B5%D0%BB%D1%8C#%D0%97%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B8%D1%82%D0%B5%D0%BB%D1%8F_%D0%BC%D0%B0%D1%82%D1%80%D0%B8%D1%86%D1%8B
	
	/*ofstream fout ("output.txt");
	for(int i = 0; i<n; i++)
		//if(m[i][i] > 0) 
			cout << i+1 << " ";
	fout.close();*/
	
	
	return 0;
}

// собираем подматрицу без тек строки-столбца
void getSubMatrix(vector <vector<int>> &m, vector <vector<int>> &bMatrix, int noLine, int noColm)
{	
	int bi = 0;
	for(auto i = 0; i<m.size();i++)
		{
			if(noLine != i)
			{
				int bj = 0;
				for(auto j = 0; j<m[i].size();j++) 
					{
						if(noColm != j)
						{
							bMatrix[bi][bj] = m[i][j];
							bj++;
						}					
					}
				bi++;
			}					
		}
}
void printMatrix(vector <vector<int>> &m)
{
	for(auto i:m)
	{
		for(auto j:i)
			{
				cout<< j << " ";
			}
		cout << endl;
	}
}
