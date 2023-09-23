/*
 Системный анализ и моделирование систем
 Зонирование районов региона по близости к внешней границе
 (Цициашвили Г.Ш., Бочарников В.Н., Краснопеев С.М)
 Кратчайший путь к границе региона
*/
#include <iostream>
#include <vector>

using namespace std;

class Zone {
	public:
	int regions = 0;
	int lenghTypes = 0;
	vector <vector<int>> connections;
	vector <vector<int>> types;

	Zone(){
		cout << "Number of regions and distanse types" << endl;
		cin >> regions >> lenghTypes;

		for (int i=0; i<regions; i++) 
			for (int j=0; j<regions; j++)
				connections[i][j] = 0;
		
		for (int i=0; i<lenghTypes; i++) 
			for (int j=0; j<regions; j++)
				types[i][j]=0;
	}
	~Zone(){
		connections.clear();
		types.clear();
}
	void fillInConnections(){
		cout << "Matrix of connections" << endl;
		for (auto i=0; i<connections.size(); i++) 
			for (auto j=0; j<connections[i].size(); j++){
				cin >> connections[i][j];
		}
	}
	void fillInTypes(){
		cout << "Matrix of distanse types" << endl;
		for (auto i=0; i<types.size(); i++) 
			for (auto j=0; j<types[i].size(); j++){
				cin >> types[i][j];
		}
	}

	void fun(){
		vector <vector<int>> res;
		for (int i=0; i<regions; i++){ 
			if(types[lenghTypes-1][int]==0) continue;//самые дальние
	
			res.push_back(vector<int> (0));
			
			int currDot = i;
			for(int j=0; j<regions; j++){
				if(connections[currDot][j]==0) continue;
	
				res[i].push_back(j); //собираем путь до крайних
				if(types[0][j]==0){
						
				}
		}
		
	}
};

int main() {
	Zone z;
	z.fillInConnections();
	z.fillInTypes();	
}
