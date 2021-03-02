#pragma once
typedef int TElem;

typedef struct stackNode
{
	TElem data;
	stackNode* next;
}Node;

class Stack
{
private:
	Node* top;
 public:
	 
	 // getter temporar (de proba) pt top
	 Node* temp_getTop();
	 
	 // constructor
	 Stack();
	 
	 // pune in varful stivei elementul TElem
	 void push(TElem);

	 // daca stiva contine elemente, elimina si returneaza elementul din varful stivei
	 // altfel, arunca eroare
	 TElem pop();

	 // returneaza true daca stiva nu contine elemente; false, altfel
	 bool isEmpty();

	 // destructor
	 ~Stack();

};