#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
//typedef int pozitie_plan;
#define NULL_TELEM -11111

// daca as fi scris aici:
// template<typename T>
// si imediat inainte de `class Queue`, mai jos tot:
// template<typename T>
// mi-ar fi fost recunoscute ca acelasi tip? 

/*
struct TElem
{
	int i, j;
};
*/


struct NodeDLLA {
	TElem data;
	int prev;
	int next;
};


class Queue
{
private:
	//TODO - Representation

	int cap;	// am ales eu, arbitrar
	int len;	// am tinut si un len, pentru a-mi fi mai usor
	// sa fac resize ul( voi interoga in functia de remove aceasta
	// variabila pentru a vedea daca este nevoie de resize )

	NodeDLLA* nodes;
	
	int head;
	int tail;
	
	int firstEmpty;

public:

	// returneaza numarul de elemente din coada
	// int getLen();

	Queue();

	//pushes an element to the end of the queue
	void push(TElem e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem pop();

	//checks if the queue is empty
	bool isEmpty() const;

	// afiseaza atributele 'data' ale elementelor din coada, unul langa celalalt ('head' va pointa catre cel mai din stanga nod, 'tail' cel mai din dreapta)
	void toString();

	// destructor
	~Queue();
};
