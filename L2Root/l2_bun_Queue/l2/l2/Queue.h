#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

struct Node {
	TElem data;
	Node* prev;
	Node* next;
};

class Queue
{
private:
	//TODO - Representation

	Node* head;
	Node* tail;

public:
	Queue();

	//Node* temp_getHead() { return head; }
	//Node* temp_getTail() { return tail; }
	Node* temp_getHead();
	Node* temp_getTail();

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
