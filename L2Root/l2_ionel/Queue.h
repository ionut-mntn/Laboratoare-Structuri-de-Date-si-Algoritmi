#pragma once
#include <iostream>
using namespace std;

class Queue
{
	class Node {
	public:
		string data;
		Node* next; //contine adresa urmatorului nod
		Node* prev; //contine adresa precedentului nod
	};
public:
	string front();
	void pushfront(string);
	void popfront();
	void pushback(string);
	void popback();
	bool isEmpty();
	void afisare();
	~Queue();
	Queue() { // constructor
		first = NULL;
		last = NULL;
	}
	typedef class Node* Nodeptr;
private:
	Node* first;
	Node* last;
};


