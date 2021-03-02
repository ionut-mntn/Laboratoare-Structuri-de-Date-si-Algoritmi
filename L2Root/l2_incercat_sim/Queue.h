#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

struct NodeDLL {
	TElem data;
	NodeDLL* prev;
	NodeDLL* next;
};

class Queue
{
private:
	//TODO - Representation

	int len;			// NOTE: acest atribut, alaturi de getterul sau l-am adaugat pentru a-mi putea usura munca in simularea jocului de carti
	NodeDLL* head;
	NodeDLL* tail;

public:

	//returns the number of elements in the queue
	int getLen();

	Queue();

	//Node* temp_getHead() { return head; }
	//Node* temp_getTail() { return tail; }
	NodeDLL* temp_getHead();
	NodeDLL* temp_getTail();

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
