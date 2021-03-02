/*
What is the difference between :
`Node* new_node_ptr = new Node; `
and
`Node* new_node_ptr`
*/

#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
	//TODO - Implementation

	head = nullptr;
	tail = nullptr;

}

NodeDLL* Queue::temp_getHead()
{
	return head;
}

NodeDLL* Queue::temp_getTail()
{
	return tail;
}

void Queue::push(TElem elem) {
	//TODO - Implementation

	
	NodeDLL* new_node = new NodeDLL;			// il aloc dinamic, pentru ca la iesirea din aceasta functie sa nu mi se distruga obiectul ( ..cred )
	new_node->data = elem;
	new_node->next = nullptr;
	if (isEmpty())
	{
		new_node->prev = nullptr;
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;			
		// obs pt mn: chiar daca tail = new_node apare si pe ramura de if si pe ramura de else, nu o pot scoate in afara lor, deoarece astfel nu as mai avea
		// acces la tail, decat daca parcurg lista dinspre head
	}
	
}


TElem Queue::top() const {
	//TODO - Implementation

	if (isEmpty()) { exception e; throw e; }
	return head->data;

	//return NULL_TELEM;
}

TElem Queue::pop() {
	//TODO - Implementation

	if (isEmpty()) { exception f; throw f; }

	TElem aux = head->data;
	NodeDLL* auxp = head;
	head = head->next;
	delete auxp;
	return aux;
	
}

bool Queue::isEmpty() const {
	//TODO - Implementation

	return (head == nullptr);

	//return false;
}


Queue::~Queue() {
	//TODO - Implementation
	while (!isEmpty())
	{
		//TElem aux = top->data;
		//cout << " se sterge nodul cu valoarea: " << head->data << '\n';
		pop();
	}
}

