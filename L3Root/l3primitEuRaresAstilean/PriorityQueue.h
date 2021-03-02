#pragma once
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);


class PriorityQueue {
private:
	//TODO - Representation
	Element* elemente;     // Array mit Paare <TElem, TPriority>
	int* next;             // Array mit links zu den nachsten Paar
	int* prev;             // Array mit links zu den vorigen Paar
	int capacity;          // Capacity der Arrays
	int head;              // Amfang der DLLA
	int tail;              // Ende der DLLA
	int firstEmpty;        // Erste Position im next/prev array die leer ist
	int size;              // Anzahl der Elemente aus dem Priority Queue
	Relation rel;          // Von user definierte Relation

public:
	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

	//destructor
	~PriorityQueue();

	void resize();

	void print();

	void reverse();
};