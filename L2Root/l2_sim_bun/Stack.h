#pragma once
typedef int TElem;
#define NULL_TELEM -1111
/*
typedef struct stackNode
{
	TElem data;
	stackNode* next;
}Node;
*/

struct NodeSLL {
	TElem data;
	NodeSLL* next;
};
class Stack
{
private:
	NodeSLL* top;
 public:
	 
	 // getter temporar (de proba) pt top
	 TElem getTop();
	 
	 // constructor
	 Stack();
	 
	 // pune in varful stivei elementul TElem
	 void push(TElem);

	 // daca stiva contine elemente, elimina si returneaza elementul din varful stivei
	 // altfel, arunca eroare
	 TElem pop();

	 // returneaza true daca stiva nu contine elemente; false, altfel
	 bool isEmpty();

	 // afiseaza atributele 'data' ale elementelor din stiva, unul deasupra celuilalt
	 void toString();

	 // destructor
	 ~Stack();

};