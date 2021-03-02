#pragma once
typedef int TElem;

typedef struct stackNode
{
	TElem data;
	stackNode* next;
}NodeSLL;

class Stack
{
private:
	NodeSLL* top;
 public:
	 
	 // getter temporar (de proba) pt top
	 NodeSLL* temp_getTop();
	 
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