#include "Stack.h"
#include <iostream>
using namespace std;

void Stack::afisare()
{
	if (Empty()==true)
	{
		cout << "NO elements Stack";
	}
	else
	{
		Nodeptr Iterator = new Node();
		Iterator = first;
		while (Iterator != NULL) //BC: O(1) AC Θ(n) WC: Θ(n) 
		{
			cout << Iterator->data << " ";
			Iterator = Iterator->next;
		}
	}
}

void Stack::push(int a)
{
	Nodeptr NodNou = new Node(); //creem un nou nod
	NodNou->data = a;
	NodNou->next = NULL;

	if (Empty()==true)
	{
		first = NodNou;
	}
	else
	{
		Nodeptr current = new Node();
		current = first;
		while (current->next != NULL) //BC: O(1) AC Θ(n) WC: Θ(n) 
		{
			current = current->next;
		}
		current->next = NodNou;
	}
}

void Stack::pop()
{
	if (Empty() == true)
	{
		cout << "The stack is already empty";
		return;
	}
	if (first->next == NULL)
	{
		first = NULL;
		return;
	}
	else
	{
		Nodeptr Iterator = new Node();
		Iterator = first;
		while (Iterator->next->next != NULL) //merg pana la penultimu BC: O(1) AC O(n) WC: Θ(n) 
		{
			Iterator = Iterator->next;
		}
		delete Iterator->next; //sterg ultimul
		Iterator->next = NULL; //penultimul pointeaza spre NULL
	}
}

int Stack::peek()
{
	Nodeptr Iterator = new Node();
	Iterator = first;
	while (Iterator->next!=NULL) //BC: O(1) AC: Θ(n) WC: Θ(n) 
	{
		Iterator = Iterator->next;
	}
	return Iterator->data;
}

bool Stack::Empty()
{
	if (first == NULL) //BC: O(1) AC O(1) WC: Θ(1) 
	{
		return true;
	}
	return false;
}
Stack::~Stack()
{
	Nodeptr aux = new Node();
	aux = first;
	while (aux != NULL) //BC: O(1) AC Θ(n) WC: Θ(n) 
	{
		Nodeptr deleteME = new Node();
		deleteME = aux;
		aux = aux->next;
		delete deleteME;
	}
}
