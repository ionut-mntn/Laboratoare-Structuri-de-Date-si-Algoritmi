#include "ShortTest.h"
#include "Queue.h"
#include <assert.h>
#include <iostream>

void testAll() {
	Queue q;
	assert(q.isEmpty() == true);
	//cout << "trece" << '\n';
	q.push(5);
	//cout << "trece la rece" << '\n';
	q.push(1);
	q.push(10);
	/*
	std::cout << "proba eu:" << '\n';
	//Node* aux = q.temp_getHead; // atentie la pus parantezele
	// daca nu, o sa iti interpreteze ca metoda!!
	Node* aux = q.temp_getHead();
	cout << aux->data << '\n';
	//cin.get();
	do
	{
		//std::cout << aux->prev << '\n';
		//std::cout << aux->data << "              " << aux << '\n';
		//std::cout << aux->next << '\n';
		//cin>>
		cin.get();
	aux = aux->next;
	} while (aux->next != nullptr);
//	std::cout << aux->data<<'\n';
	std::cout << " pana aici eu." << '\n';

	std::cout << q.top() << '\n';

	Node* aux2 = q.temp_getTail();
	std::cout << aux2->data << '\n';
	*/
	assert(q.isEmpty() == false);
	assert(q.top() == 5);
	assert(q.pop() == 5);
	assert(q.top() == 1);
	assert(q.pop() == 1);
	assert(q.top() == 10);
	assert(q.pop() == 10);
	assert(q.isEmpty() == true);
//	std::cout << " s a gatat " << '\n';
}