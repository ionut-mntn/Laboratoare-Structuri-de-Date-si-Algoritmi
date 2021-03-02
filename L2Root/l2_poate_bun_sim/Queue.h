#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

/*
typedef struct queueNode {
	TElem data;
	NodeDLL* prev;
	NodeDLL* next;
}NodeDLL;
*/

struct NodeDLL {
	TElem data;
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
