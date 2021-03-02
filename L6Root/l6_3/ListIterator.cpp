#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation

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

// parcurgere in inordine
void ListIterator::next_wrapper(NodeSL* current_node)
{
/*
	if (current_node != nullptr)
	{
		next_wrapper(current_node->lc);
		current = current_node;
		next_wrapper(current_node->rc);
	}
	else { //exception e; throw e; 
	cout << "exceptie boss\n"; }
*/

	while(current->)

}


void ListIterator::next() {
	//TODO - Implementation
/*
	//next_wrapper()
	if (valid())
	{
		//next(); // aici sigur o sa am problema; trebuie sa marchez cumva copiii vizitati ca sa
// nu ii vizitez din nou cand ma intorc pe apel recursiv si sa raman blocat(similar in
// principiu cu marcarea celulelor vizitate intr o matrice in algoritmul lui Lee si altele asemenea...
		//current =

		next_wrapper()
	}
*/
	next_wrapper(current);	// atentie! parametrul lui `next_wrapper` nu este pasat prin referinta, deci e ok!
// (am totusi o referinta la el, din interiorul metodei `next_wrapper`)
	//if (!valid()) {exception e; throw e;}
	//if (valid()) { exception e; throw e; }
	
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