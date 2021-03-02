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

	NodeDLL* head;
	NodeDLL* tail;

public:
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

	// destructor
	~Queue();
};
