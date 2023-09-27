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
        g[fin]; //конец дуги тоже узел. (появится, если не было, ничего не случится, если был.)
    }
    in.close();
}

bool isFound(std::vector<int> &p, int f){
	bool r = false;
	for(auto v:p)
		if(v==f){r=true; break;}
	return r;
}
void foo(int init_node, int fin_node, std::map<int,std::vector<int>> &graph, std::string path, bool base,std::vector<int> &p)
{
    if (init_node == fin_node || (base && isFound(p, init_node)))
    {
        //путь найден, печатаем и возвращаемся.        
        std::cout<<path<<std::endl;
        return;
    }
 
    path += std::to_string(init_node) + " "; // добавляем в путь текущую ноду
 		p.push_back(init_node);
		    
		if (graph[init_node].empty() )
        return; // Это сток графа, путь не найден
 
    //рекурсивно продолжаем поиск для дочерних нод 
    for (auto subnode:graph[init_node])
    {
    		foo(subnode,fin_node,graph,path, false,p);
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
void bitmapConverter()
{
	std::string fname = "./d1.txt", res="";
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
    std::string fname = "./data.txt";
 
    //читаем дуги из фаила
    init_graph(fname,graph);
		show(graph);
	
    //спрашиваем о пути
    int start, end;
    std::cout<<"узлы начала и конца через пробел: ";
    std::cin>>start>>end;
    
    //вычисляем и отображаем пути
    std::string path = "-->: ";
		vector <int> p;
    foo(start,end,graph,path, true, p);
    std::cout<<"все варианты проверены"<<std::endl;
		
		//bitmapConverter();
    return 0;
}
