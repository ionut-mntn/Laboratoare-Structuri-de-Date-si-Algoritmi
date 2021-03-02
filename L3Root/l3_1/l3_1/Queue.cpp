#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;

/*
worst case = average case = best case = Teta(1)
*/
Queue::Queue() {
	//TODO - Implementation

	head = nullptr;
	tail = nullptr;
	len = 0;
}

/*
worst case = average case = best case = Teta(1)
*/
int Queue::getLen()
{
	return len;
}


/*
worst case = average case = best case = Teta(1)
*/
void Queue::push(pozitie_plan elem) {
	//TODO - Implementation

	NodeDLL* new_node = new NodeDLL;
	new_node->data = elem;
	if (isEmpty())
	{
		new_node->next = nullptr;
		new_node->prev = nullptr;
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		new_node->next = nullptr;
		new_node->prev = tail;
		tail = new_node;
	}
	len++;
}

/*
worst case = average case = best case = Teta(1)
*/
pozitie_plan Queue::top() const {
	//TODO - Implementation

	if (isEmpty()) {
		exception e; throw e;
	}
	return head->data;

	//return NULL_TELEM;
}
/*
worst case = average case = best case = Teta(1) ( doar assignment uri, nimic special; nicio iteratie, nimic )
*/
pozitie_plan Queue::pop() {
	//TODO - Implementation

	if (isEmpty()) {
		exception f; throw f;
	}

	pozitie_plan aux = head->data;
	NodeDLL* auxp = head;
	head = head->next;
	delete auxp;

	len--;

	return aux;
}

/*
worst case = average case = best case = Teta(1) ( o evaluare de expresie booleana )
*/
bool Queue::isEmpty() const {
	//TODO - Implementation

	return (head == nullptr);

	//return false;
}

/*
worst case = O(n)
average case = O(n)
best case = Omega(1), deci chiar Teta(1) (niciun element in coada, deci se va face o verificare si se va parasi functia)
*/
void Queue::toString()
{
	NodeDLL* aux = head;
	while (aux != nullptr)
	{
		//cout << aux->data << " ";
		cout << aux->data.i << " " << aux->data.j << '\n';
		aux = aux->next;
	}
	cout << '\n';
}

/*
worst case = O(n), unde n - numarul de noduri
average case = O(n), chiar Teta(n), unde n - numarul de noduri ("Teta", deoarece oricare ar fi n, se vor efectua n pasi)
best case = Omega(1) (niciun nod in lista, se va face o singura verificare)
*/
Queue::~Queue() {
	//TODO - Implementation
	while (!isEmpty())			// cat timp coada nu este goala
	{
		//cout << " se elimina din coada: " << head->data << '\n';
		pop();					// sterge nodul din coada
	}
}

