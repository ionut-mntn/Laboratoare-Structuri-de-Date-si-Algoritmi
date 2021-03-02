#pragma once
#include <utility>

using namespace std;

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

class SecondPriorityQueue
{
private:
	//representation of the SecondPriorityQueue
	int capacity;
	int size;

	Relation rel;
	Element* heap;

	void bubble_up(int ct);

	void bubble_down(int ct);

	// Makes heap bigger
	void resize();

	// Makes heap smaller
	void resize_smaller();

	void print();
public:
	//implicit constructor
	SecondPriorityQueue(Relation r);

	//adds an element with a priority to the queue
	void push(TElem e, TPriority p);

	 //returns the element with the second highest priority with respect to the relation
	//throws exception if the queue has less than 2 elements
	Element top() const;

	//removes and returns the element with the second highest priority
	//throws exception if the queue has less than 2 elements
	Element pop();

	//checks if the queue has at most one element
	bool atMostOne() const;

	 //destructor
	~SecondPriorityQueue();
};

