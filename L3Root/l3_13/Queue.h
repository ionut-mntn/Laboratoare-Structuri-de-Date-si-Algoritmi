#pragma once
#include <vector>
#include <iostream>

using namespace std;
// using std::ostream;

//DO NOT CHANGE THIS PART

typedef int TElem;

#define NULL_TELEM -11111


struct U
{

	int i, j;

};
bool operator==(const U& lhs, const U& rhs);
ostream& operator<<(ostream& os, const U& p);
#define NULL_POZITIE_PLAN U{-1,-1}


template<typename U>
struct NodeDLLA
{
	U data;
	int prev; 
	int next;
};

template<typename T, typename U>
class Queue
{
private:
	//TODO - Representation

	int cap;

	T* nodes;
	
	int head;
	int tail;
	
	int firstEmpty;

public:

	Queue();

	//pushes an element to the end of the queue
	void push(U e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	U top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	U pop();

	//checks if the queue is empty
	bool isEmpty() const;

	// afiseaza atributele 'data'
	void toString () const;

	// destructor
	~Queue();
};
