#pragma once
#include <iostream>
using namespace std;
class Stack
{
	class Node {
	public:
		int data;
		Node* next; //contine adresa urmatorului nod
	};
public:
	void afisare();
	void push(int);
	void pop();
	int peek();
	bool Empty();
	~Stack();
	Stack() { // constructor
		first = NULL;
	}
	typedef class Node* Nodeptr;
private:
	Node* first;
};

