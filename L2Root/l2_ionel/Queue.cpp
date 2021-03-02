#include "Queue.h"
#include <iostream>
using namespace std;

string Queue::front()
{
	if (isEmpty() == true) //BC: O(1) AC O(1) WC: O(1) 
	{
		cout << "The Queue is EMPTY";
		return NULL;
	}
	return first->data;
}

void Queue::pushfront(string a)
{
	if (isEmpty() == true) //BC: O(1) AC O(1) WC: O(1) 
	{
		Nodeptr NodNou = new Node();
		NodNou->data = a;
		NodNou->next = NULL;
		NodNou->prev = NULL;

		first = NodNou;
		last = NodNou;
	}
	else
	{
		Nodeptr NewNode = new Node();
		NewNode->data = a;
		NewNode->prev = NULL;
		first->prev = NewNode;
		NewNode->next = first;
		first = NewNode;
	}
}

void Queue::popfront()
{
	if (isEmpty() == true) //BC: O(1) AC O(1) WC: O(1) 
	{
		cout << "The Queue is already EMPTY";
	}
	if (first == last) //BC: O(1) AC O(1) WC: O(1) 
	{
		Nodeptr DeletedNode = first;
		first = NULL;
		last = NULL;
		delete DeletedNode;
		return;
	}
	else //BC: O(1) AC O(1) WC: O(1) 
	{
		Nodeptr DelNode = new Node();
		DelNode = first;
		first = first->next;
		first->prev = NULL;
		delete DelNode;
	}
}

void Queue::pushback(string a)
{
	if (isEmpty()==true)	//BC: O(1) AC O(1) WC: O(1) 
	{
		Nodeptr NodNou = new Node();
		NodNou->data = a;
		NodNou->next = NULL;
		NodNou->prev = NULL;

		first = NodNou;
		last = NodNou;
	}
	else //BC: O(1) AC O(1) WC: O(1) 
	{
		Nodeptr NewNode = new Node();
		NewNode->data = a;
		NewNode->prev = last;
		last->next = NewNode;
		NewNode->next = NULL;
		last = NewNode;
	}
}

void Queue::popback()
{
	if (isEmpty() == true) //BC: O(1) AC O(1) WC: O(1) 
	{
		cout << "The Queue is already EMPTY";
		return;
	}
	if (first == last) //BC: O(1) AC O(1) WC: O(1) 
	{
		Nodeptr DeletedNode = new Node();
		DeletedNode = first;
		first = NULL;
		last = NULL;
		delete DeletedNode;
		return;
	}
	else //BC: O(1) AC O(1) WC: O(1) 
	{
		Nodeptr DelNode= new Node();
		DelNode = last;
		last = last->prev;
		last->next = NULL;
		delete DelNode;
	}
}

void Queue::afisare()
{
	if (first == NULL)
	{
		cout << "NO elements in the Linked List";
	}
	else
	{
		Nodeptr Iterator = new Node();
		Iterator = first;
		while (Iterator != NULL) //BC: O(1) AC O(n) WC: Θ(n) 
		{
			cout << Iterator->data << " ";
			Iterator = Iterator->next;
		}
	}
}

bool Queue::isEmpty() //BC: O(1) AC O(1) WC: O(1) 
{
	if (first == NULL)
	{
		return true;
	}
	return false;
}

Queue::~Queue()
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

