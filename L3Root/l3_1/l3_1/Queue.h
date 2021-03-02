#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
//typedef int TElem;
//typedef int pozitie_plan;
#define NULL_TELEM -11111

// daca as fi scris aici:
// template<typename T>
// si imediat inainte de `class Queue`, mai jos tot:
// template<typename T>
// mi-ar fi fost recunoscute ca acelasi tip? 
struct pozitie_plan
{
	int i, j;
};

struct NodeDLL {
	pozitie_plan data;
	NodeDLL* prev;
	NodeDLL* next;
};

class Queue
{
private:
	//TODO - Representation

	NodeDLL* head;
	NodeDLL* tail;
	int len;			// acest atribut l-am adaugat pentru a ma ajuta in a simula jocul de carti

public:

	// returneaza numarul de elemente din coada
	int getLen();

	Queue();

	//pushes an element to the end of the queue
	void push(pozitie_plan e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	pozitie_plan top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	pozitie_plan pop();

	//checks if the queue is empty
	bool isEmpty() const;

	// afiseaza atributele 'data' ale elementelor din coada, unul langa celalalt ('head' va pointa catre cel mai din stanga nod, 'tail' cel mai din dreapta)
	void toString();

	// destructor
	~Queue();
};
