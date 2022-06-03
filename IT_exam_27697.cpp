//// IT_exam_27697.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//добавить слова
//сделать код обхода след итерация
#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void ShowMenu()
{
	cout << "7 - default test" << endl;
	cout << "6 - show menu" << endl;
	cout << "5 - show the tree" << endl;
	cout << "4 - next node" << endl;
	cout << "3 - delete a node" << endl;
	cout << "2 - search a node" << endl;
	cout << "1 - add a node" << endl;
	cout << "0 - exit" << endl;
}

struct Node
{
	int value = 0;
	int ind = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

void ShowTree(Node * temp)
{
	if (temp != nullptr)
	{
		if (temp->left != nullptr)
			ShowTree(temp->left);
		cout << temp->value << " ";
		if (temp->right != nullptr)
			ShowTree(temp->right);
	}
}

Node * TreeSearch(int a, Node * last, bool add = true)
{
	if (last->value == a) return last;
	else if (last->value < a && last->right != nullptr) TreeSearch(a, last->right, add);
	else if (last->value > a && last->left != nullptr) TreeSearch(a, last->left, add);
	else if (add)
	{
		Node * res = new Node;
		res->parent = last;
		if (last->value < a) last->right = res;
		if (last->value > a) last->left = res;
		return res;
	}
	else return nullptr;
}
Node * NextNode(Node * curr, Node * first = nullptr)
{
	if (first == nullptr) first = curr;

	if (curr->right == nullptr)
		return NextNode(curr->parent, first);
	else
	{
		Node * temp = curr->right;
		while (temp->left != nullptr)
			temp = temp->left;
		return temp;
	}
}
void DeleteNode(int a, Node * root = nullptr)
{
	if (root == nullptr)
	{
		cout << "There is no tree";
	}
	else
	{
		Node * curr = TreeSearch(a, root, false);
		if (curr == nullptr)
			cout << "Not found";
		else if (curr->left == nullptr && curr->right == nullptr)
		{
			if (curr->parent->left == curr) curr->parent->left = nullptr;
			else if (curr->parent->right == curr) curr->parent->right = nullptr;
			delete curr;
		}
		else if (curr->parent == nullptr)
		{
			Node * temp = NextNode(curr);

		}
	
		else
		{
			Node * temp = NextNode(curr);

			if (curr->parent->left == curr)
			{
				curr->parent->left = temp;
				temp->parent = curr->parent;
			}
			else if (curr->parent->right == curr)
			{
				curr->parent->right = temp;
				temp->parent = curr->parent;
			}
			delete curr;
		}
	}

}
Node *  AddNode(int temp, Node * root)
{
	Node * last = TreeSearch(temp, root);
	last->value = temp;
	return last;
}

int main()
{
	int mode = -1;
	vector <Node*> ar;
	Node * root = nullptr;
	ShowMenu();
	do
	{
		cin >> mode;
		switch (mode)
		{
		case 1:
		{
			int temp;
			cin >> temp;
			if (root == nullptr)
			{
				root = new Node;
				root->value = temp;
			}
			AddNode(temp, root);
			cout << "Done";
			break;
		}
		case 2:
		{
			int temp;
			cin >> temp;
			Node * last = nullptr;
			last = TreeSearch(temp, root, false);
			if (last == nullptr) cout << "Not Found";
			else cout << "Found";
			break;
		}
		case 3:
		{
			int temp;
			cin >> temp;
			DeleteNode(temp, root);
			break;
		}
		case 4:
		{
			int temp;
			cin >> temp;
			Node * curr = TreeSearch(temp, root);
			curr = NextNode(curr, root);
			if (curr == nullptr) cout << "Not Found";
			else cout << curr->value;
			break;
		}
		case 5:
		{
			if (root != nullptr)
			{
				//ShowArrow(ar);
				ShowTree(root);
			}
			else cout << "No data";
			break;
		}
		case 6:
			ShowMenu(); break;
		case 7:
		{
			vector <int> test = { 8, 3, 5, 11, 9, 1, 14, 6, 10, 12, 15, 7, 13 };
			if (root == nullptr)
			{
				root = new Node;
				root->value = test[0];
			}
			for (int i : test)
				AddNode(i, root);
			break;
		}
		default:
		{
			cout << "no command";
			break;
		}
		}
		cout << endl;
	} while (mode != 0);
	return 0;
}