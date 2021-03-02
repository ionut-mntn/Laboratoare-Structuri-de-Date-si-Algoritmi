#pragma once
#include <exception>
#include <iostream>
#include "Stack.h"
Stack::Stack()
{
	top = nullptr;
}

Node* Stack::temp_getTop()
{
	return top;
}

void Stack::push(TElem elem)
{
	Node *new_node = new Node;
	new_node->data = elem;
	new_node->next = top;
	top = new_node;
	//if (isEmpty()) top = new_node;
	//else { top->next = new_node; top = new_node; }
}

TElem Stack::pop() // oare o sa imi fie vizibil aici?
{
	if (isEmpty()) { exception each; throw each;  std::cout << "exceptie" << '\n'; }
	else
	{
		TElem top_value = top->data;
		Node* old_top = top;
		//top = auxp->next;
		top = top->next;
		delete old_top;
		return top_value;
	}
}

bool Stack::isEmpty()
{
	return top == nullptr;
}

Stack::~Stack()
{
	
	if (isEmpty()) return;
	else
	{
		while (top->next != nullptr) pop();
		pop();
	}
	
	/*
	do
	{
		pop();
	} while (top->next != nullptr);
	*/		
}