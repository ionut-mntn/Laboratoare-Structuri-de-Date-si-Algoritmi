#pragma once
#include <vector>
#include <iostream>
using namespace std;
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

struct pozitie_plan
{
	int i, j;
};
bool operator==(const pozitie_plan& lhs, const pozitie_plan& rhs);

#define NULL_POZITIE_PLAN pozitie_plan{-1,-1}

struct NodeDLLA {
	pozitie_plan data;
	int prev;
	int next;
};

class Queue
{
private:
	//TODO - Representation

	int cap;

	NodeDLLA* nodes;
	
	int head;
	int tail;
	
	int firstEmpty;

public:

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

	// afiseaza atributele 'data'
	void toString () const;

	// destructor
	~Queue();
};
