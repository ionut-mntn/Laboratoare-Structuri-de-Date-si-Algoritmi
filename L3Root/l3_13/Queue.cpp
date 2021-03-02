#include <iostream>
#include <fstream>
#include <exception>
#include "Queue.h"

using namespace std;

bool operator==(const U& lhs, const U& rhs)
{
	return lhs.i == rhs.i && lhs.j == rhs.j;
}

/*
worst case = O(n)
average case = O(n)
best case = Teta(1) (nu exista niciun element in coada, deci se va face doar o verificare)
*/
void Queue::toString() const 
{
	int aux = head;
	while (aux != -1)
	{
//		cout << "(" << nodes[aux].data.i + 1 << ", " << nodes[aux].data.j + 1 << ") ";	// +1 pentru ca user ul vede in indexare de la 1
		cout << "(" << nodes[aux].data <<") ";	
		aux = nodes[aux].next;
	}
	cout << '\n';
}


/*
worst case = average case = best case = Teta(n) 
(la fiecare initializare a unei cozi, se vor face n pasi pentru a initializa
campul next pentru fiecare nod din `nodes`)
*/
Queue::Queue() {
	//TODO - Implementation

	cap = 105;

	head = -1;
	tail = -1;

	nodes = new NodeDLLA[cap];

	nodes[0].prev = -1;					// prima pozitie nu indica catre vreun vecin anterior
	nodes[0].next = 1;
	for (int i = 1; i < cap - 1; i++)
	{
		nodes[i].prev = i - 1;
		nodes[i].next = i + 1;
	}
	nodes[cap - 1].prev = cap - 2;
	nodes[cap - 1].next = -1;			// ultima pozitie nu indica catre vreun vecin posterior

	firstEmpty = 0;						// prima pozitie pe care se poate adauga un nod in `nodes` este 0
}

/*
worst case = O(n)
average case = O(n) - amortizat (deoarece se presupune ca realocarea memoriei nu se va face des)
best case = Teta(1)
*/
void Queue::push(U elem) {
	//TODO - Implementation

	if (firstEmpty == -1) // daca e full container ul
	{
		NodeDLLA* newNodes = new NodeDLLA[2 * cap];

		for (int i = 0; i < cap; i++)
		{
			newNodes[i].data = nodes[i].data;
			newNodes[i].next = nodes[i].next;
			newNodes[i].prev = nodes[i].prev;
		}

		for (int i = cap; i < 2 * cap - 1; i++)
			newNodes[i].next = i + 1;		// similar initializarii de la inceput(cand se apeleaza constructorul)
		newNodes[2 * cap - 1].next = -1;

		delete[]nodes;
		nodes = newNodes;
		firstEmpty = cap;
		cap = cap * 2 + 1; 
	}

	nodes[firstEmpty].data = elem;

	if (head == -1)			// sau head == -1 sau len == 0
	{

		head = firstEmpty;
	}
	else
	{
		nodes[tail].next = firstEmpty;
		nodes[firstEmpty].prev = tail;
		
	}
	tail = firstEmpty;
	firstEmpty = nodes[firstEmpty].next;
	nodes[tail].next = -1;

}

/*
worst case = average case = best case = Teta(1) (doar o verificare)
*/
U Queue::top() const {
	//TODO - Implementation

	if (isEmpty()) {
		exception e; throw e;
	}
	return nodes[head].data;

}

/*
worst case = average case = best case = Teta(1) (doar assignment uri)
*/
U Queue::pop() {
	//TODO - Implementation

	// resize will be implemented here, too
	
	if (isEmpty()) {
		exception f; throw f;
	}
	else
	{
		int aux = head;
		U elem = nodes[head].data;
		

		head = nodes[head].next;
		
		if(head != -1) nodes[head].prev = -1; // head ul nu are vecini precedenti
		else { tail = -1; }
		nodes[firstEmpty].prev = aux;			// parcursul lui firstEmpty e ca o stiva!! cand innoiesc firstEmpty, e ca si cum as pune in varful stivei !!
		nodes[aux].next = firstEmpty;

		firstEmpty = aux;
		nodes[firstEmpty].prev = -1; /*vecinul precedent nu exista (top ul unei stive nu are nimic deasupra) */
		
		return elem;
	}
}

/*
worst case = average case = best case = Teta(1) ( o evaluare de expresie booleana )
*/
template<typename T, typename U>
bool Queue::isEmpty() const {
	//TODO - Implementation

	return head == -1;	// sau len == 0 sau tail == -1
}


/*
worst case = O(1), deci chiar Teta(1)
average case = Teta(1)
best case = Omega(1), deci chiar Teta(1)
*/
Queue::~Queue() {
	//TODO - Implementation
	delete []nodes;		// dealoc doar ce a fost alocat dinamic
}