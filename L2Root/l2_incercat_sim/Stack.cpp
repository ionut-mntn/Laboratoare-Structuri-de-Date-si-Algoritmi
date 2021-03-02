#pragma once
#include <exception>
#include <iostream>
#include "Stack.h"

using std::cout;

Stack::Stack()
{
	top = nullptr;
}

TElem Stack::getTop()
{
	return top->data;
}

void Stack::push(TElem elem)
{
	NodeSLL *new_node = new NodeSLL;
	new_node->data = elem;
	new_node->next = top;
	top = new_node;
	//if (isEmpty()) top = new_node;
	//else { top->next = new_node; top = new_node; }
}

TElem Stack::pop() // oare o sa imi fie vizibil aici?
{
	if (isEmpty()) { std::exception each; throw each;  std::cout << "exceptie" << '\n'; }
	else
	{
		TElem top_value = top->data;
		NodeSLL* old_top = top;
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

void Stack::toString()
{
	//std::cout << " intra si aici !!" << '\n';
	//if (top == nullptr) std::cout << "DAAAAAAAAAAAAA" << '\n';
	NodeSLL* aux = top;
	if (isEmpty()) std::cout << "Stiva este goala" << '\n';
	else
	{
		//std::cout << " si pe asta " << '\n';
		do
		{
			std::cout << aux->data << '\n';
			aux = aux->next;
		//	if (aux == nullptr) cout << "Da, giani" << '\n';
		} //while (aux->next!= nullptr);
		while (aux != nullptr);
		//std::cout << aux->data << '\n';
	}
//	cout << " iese " << '\n';
}

Stack::~Stack()
{
	
	if (isEmpty()) return;
	else
	{
		while (top->next != nullptr) 
		{
			std::cout << "se elimina din stiva: " << top->data << '\n';
			pop();
		}
		pop(); // stergem ultimul element (sau puteam trece pe do-while ca sa evit scrierea de 2 ori, whatever...)
	}
	
	/*
	do
	{
		pop();
	} while (top->next != nullptr);
	*/		
}