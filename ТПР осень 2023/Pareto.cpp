/*
Теория принятия решения
Задача на Метод Парето

A 11 - количество объектов
B 8 - количество критериев
(A 11) - имена объектов
(B 8) - имена критериев
(A*B 11*8) - оценка
*/

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void act1();
void act2();

// fname - абсолютный или относительный путь к фаилу
//в первом файле на первой строке выписаны два числа n(кол-во вершин), m(кол-во
//ребер). далее в каждой строке указаны по два числа указыающие номера вершин
//которые соединяют ребро.
void init_graph(std::string fname, std::map<int, std::vector<int>> &g) {
  std::ifstream in(fname, std::ifstream::in);
  int init, fin;
  in >> init >> fin; // тут просто выкидываем строки с количеством ребер и узлов
                     // -- нам не нужны.
  while (in.good()) {
    in >> init >> fin;
    g[init].push_back(fin); //добавляем fin в список смежности узла init
    //  g[fin]; //конец дуги тоже узел. (появится, если не было, ничего не
    //  случится, если был.)
  }
  in.close();
}

void foo(int init_node, int fin_node, std::map<int, std::vector<int>> &graph,
         std::vector<int> path, std::vector<int> &used,
         std::vector<std::vector<int>> &everyways) {
  path.push_back(init_node); // добавляем в путь текущую ноду
  if (init_node == fin_node) {
    //путь найден, печатаем и возвращаемся.
    // std::cout<<"-->: ";
    // for(auto p:path)cout<<p<<" ";
    // cout<<std::endl;

    everyways.push_back(path);
    path.pop_back();
    return;
  }

  if (graph[init_node].empty())
    return; // Это сток графа, путь не найден
  if (used[init_node] == 1) {
    // cout<<path<<" cirlce "<<endl;
    return;
  }
  //рекурсивно продолжаем поиск для дочерних нод
  for (auto subnode : graph[init_node]) {
    used[init_node] = 1;
    foo(subnode, fin_node, graph, path, used, everyways);
  }
  return;
}

void show(std::map<int, std::vector<int>> &graph) {
  //вывод текущих списков смежности в читабельном виде.
  for (const auto &kvp : graph) {
    std::cout << kvp.first << "\t: ";
    for (auto v : kvp.second)
      std::cout << v << " ";
    std::cout << std::endl;
  }
}

//граф из битмап в пары, на вход файл:
//колво вершин
//сама матрица
void bitmapConverter(string fname) {
  std::string res = "";
  std::ifstream in(fname, std::ifstream::in);
  int n, t = 0, c = 0, r = 1, ca = 0;
  in >> n; // тут просто выкидываем строки с количеством узлов
  while (in.good()) {
    in >> t;
    c++;
    if (c > n) {
      r++;
      c = 1;
      cout << endl;
    }
    if (t == 1) {
      cout << r << " " << c << endl;
      ca++;
    }
  }
  cout << n << " " << ca << endl;
  in.close();
}

// interface
void showMenu() {
  cout << "to exit press 0" << endl
       << "to convert bitmap press 1" << endl
       << "for searching shortest paths press 2" << endl;
}
void runMenu() {
  int mode = -1;
  while (mode != 0) {
    showMenu();
    cin >> mode;
    switch (mode) {
    case 0:
      cout << "Bye!" << endl;
      break;
    case 1:
      act1();
      break;
    case 2:
      act2();
      break;
    default:
      break;
    }
  }
}

class TestObj {
public:
  int id = 0;
  string name = "";
  vector<pair<int, int>> &params; // id param + value
  /*error
  default constructor of 'TestObj' is implicitly deleted because field 'params'
  of reference type 'vector<pair<int, int>> &' would not be initialized
          */
};
class TestParam {
public:
  int id = 0;
  string name = "";
};

int main() {
  runMenu();
  return 0;
}

void act1() {
  string fname;
  cout << "type in bitmap file's name" << endl;
  cin >> fname;
  try {
    bitmapConverter(fname);
  } catch (...) {
    cout << "error" << endl;
  }
}
void act2() {
  string fname, s_temp;
  cout << "type in file's name" << endl;
  cin >> fname;

  //читаем
  std::ifstream in(fname, std::ifstream::in);
  int obj_count, param_count, n;
  in >> obj_count >> param_count;
  n = obj_count * param_count;

  vector<TestObj> T(obj_count); // error in instantiation of member function
                                // 'std::vector<TestObj>::vector' requested here
  for (int i = 0; i < obj_count; i++) {
    in >> s_temp;
    TestObj &t_obj = T[i];
    t_obj.id = i;
    t_obj.name = s_temp;
    t_obj.params = (vector<pair<int, int>>(param_count));
  }

  vector<TestParam> P(param_count);
  for (int i = 0; i < param_count; i++) {
    in >> s_temp;
    TestParam &t_obj = P[i];
    t_obj.id = i;
    t_obj.name = s_temp;
  }

  for (int i = 0; i < obj_count; i++) {
    for (int j = 0; j < param_count; j++) {
      int t;
      in >> t;
      pair<int, int> &op = T[i].params[j];
      op.first = j;
      op.second = t;
    }
  }
  in.close();

  //проверка
}
