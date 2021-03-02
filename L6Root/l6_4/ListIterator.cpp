#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation

	//aux_stack = new NodeSL[list.size()];
	//dim_stack = 0;

	//aux_stack = new stack<NodeSL*>();
	
	// aux_stack = new stack<NodeSL>();

	first();
}

void ListIterator::first(){
	//TODO - Implementation
//	NodeSL* previous_node = nullptr;
/*	NodeSL* current_node = list.root;
	while (current_node->lc != nullptr)
		current_node = current_node->lc;
*/
//	cout << "intra acilea\n";
	current = list.root;
	while (current->lc != nullptr)
	{
		current = current->lc;
	//	cout << " nu mai iese \n";
	}
//	cout << "iese\n";
}		

/*
bool ListIterator::hasNext()
{
//	return aux_stack.empty(); // daca e zero face conversie implicit
	if (aux_stack->empty()) return false;
	return true;
}
*/

// parcurgere in inordine
void ListIterator::next_wrapper(NodeSL* current_node)
// void ListIterator::next_wrapper(NodeSL* root, NodeSL* current_node)
{

	if (current_node != nullptr)
	{
		next_wrapper(current_node->lc);
		current = current_node;
		next_wrapper(current_node->rc);
	}
	else 
	{ 
		//exception e("exceptie"); throw e; 
		//exception e;  throw e;
		cerr << "exceptie\n"; 
	}


//	while(current->)

//	if (root = nullptr) return;
////////////////////////////////////////////////////////////////////////////////////////////
/*
	//TComp stack[list.size()]; // stiva de dimensiune n 9 cu siguranta e suficient spatiu)
	NodeSL stack[list.size()]; // stiva de dimensiune n 9 cu siguranta e suficient spatiu)
	int dim_stack = 0; // dimensiune stiva
	
	NodeSL* currentNode = list.root;
	while (currentNode != nullptr)
	{
		stack[dim++] = currentNode;// facem push;
		currentNode = currentNode->lc;
	}

	while (dim)
	{
		currentNode = stack[dim - 1];
		dim--;

		// @visit currentNode

		currentNode = currentNode->rc;
		while (currentNode != nullptr)
		{
			stack[dim++] = currentNode;
			currentNode = currentNode->lc;
		}
	}
*/
//////////////////////////////////////////////////////////////////////////////////////

	/*
	if (current == nullptr) { exception e; throw e; }
	else
	{
		stack[dim++] = currentNode;// facem push;
		currentNode = currentNode->lc;
	}

	next_wrapper()
	*/	
}

/*
void ListIterator::pushToLeft(NodeSL node)
{
	if (node != nullptr)
	{
		aux_stack->push(node);
		pushToLeft(node->lc);
	}
}
*/

void ListIterator::next() {
	//TODO - Implementation

	//next_wrapper()
	if (valid())
	{
		//next(); // aici sigur o sa am problema; trebuie sa marchez cumva copiii vizitati ca sa
// nu ii vizitez din nou cand ma intorc pe apel recursiv si sa raman blocat(similar in
// principiu cu marcarea celulelor vizitate intr o matrice in algoritmul lui Lee si altele asemenea...
		//current =

		next_wrapper(current);
	}
	else
	{
		exception e; 
		throw e;
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//next_wrapper(current);	// atentie! parametrul lui `next_wrapper` nu este pasat prin referinta, deci e ok!
// (am totusi o referinta la el, din interiorul metodei `next_wrapper`)
	//if (!valid()) {exception e; throw e;}
	//if (valid()) { exception e; throw e; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	NodeSL node = aux_stack->pop();
	pushToLeft(node.rc);
	*/
	//return node->info;
}

bool ListIterator::valid() const{
	//TODO - Implementation
	// cout << "iese\n";
	return current != nullptr;
	
//	return false;
}

TComp ListIterator::getCurrent() const{
	//TODO - Implementation
	
	// obs: uitandu-ma la teste, vad ca vrea sa arunc eroare daca nu gasesc elementul (in extendedTest sunt pe acolo niste asserturi)
	if (valid()) return current->info;
	exception e; throw e;
	
//	return NULL_TCOMP;
}