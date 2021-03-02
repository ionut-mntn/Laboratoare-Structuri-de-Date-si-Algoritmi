#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation

	root = new NodeSL; // cred ca asa, da nuj sigur dc
	//daca nu, atunci asa: ...
	root->lc = nullptr;
	root->rc = nullptr;
	root->LeftChildrenCount = 0;
	//root->list_index = 0; // indexare de la zero

	rel = r;

	len = 0;
}

int SortedIndexedList::size() const {
	//TODO - Implementation
	return 0;
}

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	
	return this->len > 0;
	
	//return false;
}

TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation
	return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation
	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	NodeSL* currentNode = root;
	int index = currentNode->LeftChildrenCount;// ATENTIE! ( indexare de la 1 sau 0? ) indexare de la zero!!
	// while(currentNode->lc != nullptr || currentNode->rc != nullptr) // daca inca ma pot deplasa in arbore (de la radacina spre frunze)
	while(currentNode != nullptr)
	{
		// NOTA: am scris codul (dar mai ales `else if` ul si `if` ul urmarind exemplul de pe slide-ul 9 din "Vorlesung 12"; (numerotat "V11" pe moodle)
		// am zis sa precizez pentru ca poate va fi mai usor de urmarit & inteles logica din spatele a ceea ce fac eu mai jos cu variabila `index` - cand, cum si de ce o incrementez
		if (e == currentNode->info) //return currentNode->list_index;
			//return index - 1;
			return index;
		else if (rel(e, currentNode))
		{
			currentNode = currentNode->lc;
			index = currentNode->LeftChildrenCount;
		}
		else
		{
			// e esential la acest pas intai sa "actualizez" ( cu ghilimelele de rigoare pentru ca este o actualizare temporara, nu e CHIAR indexul curent 
	
			int aux = currentNode->LeftChildrenCount;
			currentNode = currentNode->rc;
			index = aux + 1 + currentNode->LeftChildrenCount; // sar peste tot ce e mai mic, anume: copii din stanga ai parintelui, parintele si copii din stanga a nodului curent; !! la asta 
		}
	}
	return -1;

	//return 0;
}

void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
}
