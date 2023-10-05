/*
 Системный анализ и моделирование систем
 Зонирование районов региона по близости к внешней границе
 (Цициашвили Г.Ш., Бочарников В.Н., Краснопеев С.М)
 Кратчайший путь к границе региона
*/
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

//fname - абсолютный или относительный путь к фаилу
//в первом файле на первой строке выписаны два числа n(кол-во вершин), m(кол-во ребер).
//далее в каждой строке указаны по два числа указыающие номера вершин которые соединяют ребро.
void init_graph(std::string fname, std::map<int,std::vector<int>> &g)
{
    std::ifstream in(fname,std::ifstream::in);
    int init , fin;
    in >> init >>fin; // тут просто выкидываем строки с количеством ребер и узлов -- нам не нужны. 
    while( in.good() )
    {
        in>>init>>fin;
        g[init].push_back(fin);//добавляем fin в список смежности узла init
      //  g[fin]; //конец дуги тоже узел. (появится, если не было, ничего не случится, если был.)
    }
    in.close();
}

void foo(int init_node, int fin_node, std::map<int,std::vector<int>> &graph, std::vector<int> path,std::vector<int> &used,std::vector<std::vector<int>> &everyways)
{
    path.push_back(init_node); // добавляем в путь текущую ноду
		if (init_node == fin_node)
    {
        //путь найден, печатаем и возвращаемся.      
        //std::cout<<"-->: ";
				//for(auto p:path)cout<<p<<" ";
				//cout<<std::endl;

				everyways.push_back(path);
				path.pop_back();	
        return;
    }
        
		if (graph[init_node].empty() )
        return; // Это сток графа, путь не найден
 		if(used[init_node]==1){
			//cout<<path<<" cirlce "<<endl;
			return;
		}
    //рекурсивно продолжаем поиск для дочерних нод 
    for (auto subnode:graph[init_node])
    {
				used[init_node]=1;
    		foo(subnode,fin_node,graph,path,used,everyways);
    }
    return;
}

void show(std::map<int,std::vector<int>> &graph)
{
    //вывод текущих списков смежности в читабельном виде.
    for(const auto &kvp: graph)
    {
        std::cout << kvp.first << "\t: ";
        for(auto v: kvp.second)
            std::cout << v << " ";
        std::cout<<std::endl;
    }
}

//граф из битмап в пары
void bitmapConverter(string fname)
{
	std::string res="";
	std::ifstream in(fname,std::ifstream::in);
    int n , t=0, c=0, r=1, ca=0;
    in >> n; // тут просто выкидываем строки с количеством узлов  
    while( in.good() )
    {
        in>>t;
				c++;
			if(c>n) {r++; c=1; cout<<endl;} 
			if(t==1) {cout<<r<<" "<<c<<endl; ca++;}
    }
	cout<<ca;
    in.close();
}

int main()
{
    
		std::map<int,std::vector<int>> graph;
		std::map<int,std::vector<int>> length;
		
	
    //читаем дуги из фаила
    init_graph("./data.txt",graph);
		init_graph("./d1.txt",length);
		//show(graph);
		show(length);

		//ищем все пути
		for(auto i:length[4])
			for(auto j:length[1]){
				//cout<< "from " <<i<< " to " << j<<endl;
				int start = i, end = j;
				vector <int> path;
				vector <std::vector<int>> everyways;
				vector <int> used (graph.size()+1, 0);
    		foo(start,end,graph,path, used, everyways);
				
				int min = graph.size()+1;
				int res = 0;
				for(int i = 0;i<everyways.size();i++) 
					if(everyways[i].size()<min){
						res = i;
						min = everyways[i].size();
					}
				for(auto w:everyways[res])cout<<w<<" ";
				cout<<endl;
				//return 0;
			}
	
		return 0;
}
