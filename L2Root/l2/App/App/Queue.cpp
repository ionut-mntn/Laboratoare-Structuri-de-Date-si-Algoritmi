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

Node* Queue::temp_getHead()
{
	return head;
}

Node* Queue::temp_getTail()
{
	return tail;
}

void Queue::push(TElem elem) {
	//TODO - Implementation
	
	//Node new_node;
	//Node.data = elem;
	

	//Node aux = new Node[1];
	
	
	/////Node *new_node = new Node;			// il aloc dinamic, pentru ca la iesirea din aceasta functie sa nu mi se distruga obiectul ( ..cred )
	/////new_node->data = elem;
	/*
	//new_node->prev = last;
	//new_node->next = nullptr;
	//last = new_node;
	
	//tail->next = new_node;
	new_node->prev = tail;				// pentru nodul nou, fac legatura "in spate" ( spre head )
	new_node->prev->next = new_node;	// pentru nodul vechi ( new_node->prev ), fac legatura "in fata" ( spre tail )
	//tail->next = new_node;b
	//tail = new_node;

	new_node->next = nullptr;
	tail = new_node;

	if (isEmpty())
	{
		head = new_node;
	}
	*/
	
	// pana aici, creez un nod
	
	Node* new_node = new Node;			// il aloc dinamic, pentru ca la iesirea din aceasta functie sa nu mi se distruga obiectul ( ..cred )
	new_node->data = elem;
	if (isEmpty())
	{
		new_node->next = nullptr;
		new_node->prev = nullptr;
		head = new_node;
		tail = new_node;
		//cout << " 1.s a adaugat nodul cu valoarea " << int(elem) << '\n';
		//cin.get();
	}
	else
	{
		tail->next = new_node;
		new_node->next = nullptr;
		//new_node->next = tail; //wtf john
		new_node->prev = tail; 
		tail = new_node;
		//cout << " *. s a adaugat nodul cu valoarea " << int(elem) << '\n';
		//cin.get();
	}
	

	/*
	Node* new_node = new Node;
	new_node->data = elem;
	//tail->next = new_node;
	new_node->prev = tail;
	new_node->next = nullptr;
	if (isEmpty()) head = new_node; //tail->next = new_node;
	else { tail->next = new_node; tail = new_node; }
	*/
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
	Node* auxp = head;
	head = head->next;
	delete auxp;
	return aux;
	/*
	delete head; // sterg obiectul de la adresa pointed to by head
	head // il fac pe head sa indice 
	Node* aux = head->data;
	*/
//	return 
	//	return NULL_TELEM;
}

bool Queue::isEmpty() const {
	//TODO - Implementation

	//if (head == nullptr) { std::cout << " e nula coada"; return true; }
	//else {std::cout << " nu e nula coada "; return false;}
	
	return (head == nullptr);

	//return false;
}


Queue::~Queue() {
	//TODO - Implementation
}

