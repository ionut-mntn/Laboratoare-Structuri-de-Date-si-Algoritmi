#pragma once
#include <exception>
#include <iostream>
#include "Stack.h"

using std::cout;

/*
worst case = average case = best case = Teta(1) (doar atribuiri)
*/
Stack::Stack()
{
	top = nullptr;
	
}

/*
worst case = average case = best case = Teta(1) (doar atribuiri)
*/
TElem Stack::getTop()
{
	if (top == nullptr) return NULL_TELEM;
	return top->data;
}

/*
worst case = average case = best case = Teta(1) (doar atribuiri)
*/
void Stack::push(TElem elem)
{
	NodeSLL *new_node = new NodeSLL;
	new_node->data = elem;
	new_node->next = top;
	top = new_node;
}

/*
worst case = average case = best case = Teta(1) ( o singura verificare si niste atribuiri)
*/
TElem Stack::pop() // oare o sa imi fie vizibil aici?
{
	if (isEmpty()) { std::exception each; throw each;  std::cout << "exceptie" << '\n'; }
	else
	{
		TElem top_value = top->data;
		NodeSLL* old_top = top;
		top = top->next;
		delete old_top;
		return top_value;
	}
}

/*
worst case = average case = best case = Teta(1) ( doar assignment uri, nimic special; nicio iteratie, nimic )
*/
bool Stack::isEmpty()
{
	return top == nullptr;
}

/*
worst case: O(n)  
average case: O(n)
best case = Teta(1) ( doar assignment uri, nimic special; nicio iteratie, nimic )
*/
void Stack::toString()
{
	NodeSLL* aux = top;
	if (isEmpty()) std::cout << "Stiva este goala" << '\n';
	else
	{
		do
		{
			std::cout << aux->data << '\n';
			aux = aux->next;
		}while (aux != nullptr);
	}
}

Stack::~Stack()
{
	
	if (isEmpty()) return;
	else
	{
		do  
		{
			//std::cout << "se elimina din stiva: " << top->data << '\n';
			pop();
		} while (top != nullptr);
	}
	
}