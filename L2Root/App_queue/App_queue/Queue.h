#pragma once
#include <vector>
//#include "Node.h"
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

//aici n-am mai folosit typedef...


/*
class Node
{
public:
	TElem data;
	Node* next;
};
//struct Node;
*/

/*
class Node
{
public:
	TElem data;
	Node *next;
	Node *prev;
	Node()
	{
		data = NULL_TELEM;
		next = nullptr;
		prev = nullptr;
	}
};
*/

/*
struct Node {			// nu stiu de ce, dar daca declar struct ul aici, nu e vizibil in .cpp
	TElem data;
	//Node* next;
};
*/
/*
class Node {
private:
	TElem Data;
public:
	void setData(TElem value) { Data = value; }
};
*/
/*
class Node {
public:
	TElem data = NULL_TELEM;
	int next = -1;
	int prev = -1;
};
*/






























class Queue
{
//private:
	//TODO - Representation

	//	TElem *first;
//	TElem *last;
	/*
	Node *tail;
	Node *head;
	*/
	//Node *head;
	//Node *Tail;
	/*
	struct Node {			// nu stiu de ce, dar daca declar struct ul aici, nu e vizibil in .cpp
		TElem data;
		Node* next;
	};
	*/

	struct Node {
		TElem data;
		Node* next;
	};

private:
	Node *head;
	Node *tail;

public:
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

	// destructor
	~Queue();
};
