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

	return len;

//	return 0;
}

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation

	return len == 0;

	//return false;
}

TComp SortedIndexedList::getElement(int i) const {
	//TODO - Implementation
	return NULL_TCOMP;
}

//NodeSL

TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation

	// as putea sa ma folosesc de un iterator sa parcurg in inordine si astfel determin indexul
	// SAU
	// poate ar fi mai inteligent sa incerc sa ma folosesc cumva de atributul unui nod care retine 
	// numarul de copii din partea stanga
	
	

	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const { // obs: am crezut ca trebuie sa fie complexitate logaritmica si m-am complicat;
// vad in curs ca as fi putut sa o implementez de complexitate O(n), deci as fi putut sa ma folosesc de o traversare in inordine 
// (deci, eventual un iterator) si un contor pe care sa il tot incrementez pentru a obtine indexul

	//TODO - Implementation

	NodeSL* currentNode = root;
	int index = currentNode->LeftChildrenCount; // ATENTIE! ( indexare de la 1 sau 0? ) indexare de la zero!!
	//int index = 0; // ATENTIE! ( indexare de la 1 sau 0? ) indexare de la zero!!
	// while(currentNode->lc != nullptr || currentNode->rc != nullptr) // daca inca ma pot deplasa in arbore (de la radacina spre frunze)
	while (currentNode != nullptr)
	{
		// NOTA: am scris codul (dar mai ales `else if` ul si `if` ul urmarind exemplul de pe slide-ul 9 din "Vorlesung 12"; (numerotat "V11" pe moodle)
		// am zis sa precizez pentru ca poate va fi mai usor de urmarit & inteles logica din spatele a ceea ce fac eu mai jos cu variabila `index` - cand, cum si de ce o incrementez
		if (e == currentNode->info) //return currentNode->list_index;
			//return index - 1;
			return index;
		//else if (rel(e, currentNode))
		//else if (rel(e, currentNode.info)) // daca decomentez asta ce e cu eroarea ciudata care imi apare ?
		else if (rel(e, currentNode->info)) // info aici!!
		{
			currentNode = currentNode->lc;
			//index = currentNode->LeftChildrenCount;
			//index += currentNode->LeftChildrenCount;
		}
		else
		{
			// e esential la acest pas intai sa "actualizez" ( cu ghilimelele de rigoare pentru ca este o actualizare temporara, nu e CHIAR indexul curent 

			/*
			int aux = currentNode->LeftChildrenCount;
			currentNode = currentNode->rc;
			index = aux + 1 + currentNode->LeftChildrenCount; // sar peste tot ce e mai mic, anume: copii din stanga ai parintelui, parintele si copii din stanga a nodului curent; !! la asta 
			*/
//			int aux = currentNode->LeftChildrenCount;
		}
	}
	return -1;

	//return 0;
}

//void SortedIndexedList::initNode(TComp e)
NodeSL* SortedIndexedList::initNode(TComp e)
{
	NodeSL* new_node = new NodeSL;
	new_node->info = e;
	new_node->lc = nullptr;
	new_node->rc = nullptr;
	return new_node;
}

NodeSL* SortedIndexedList::add_wrapper(NodeSL* current_node, TComp e)
{
	if (current_node == nullptr)
		current_node = initNode(e);
	else if (rel(current_node->info, e))
	{
		current_node->lc = add_wrapper(current_node->lc, e);
	}
	else
	{
		current_node->rc = add_wrapper(current_node->rc, e);
	}
	return current_node;
}

void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
/*
	NodeSL* prev = nullptr;
	NodeSL* currentNode = root;
*/
	//while (currentNode != nullptr && rel(e, currentNode))
	//while (currentNode-> != nullptr)

	//while (currentNode->lc != nullptr || currentNode->rc != nullptr) // daca inca ma pot deplasa in arbore (de la radacina spre frunze)
	//while (currentNode->lc != nullptr || currentNode->rc != nullptr) // daca inca ma pot deplasa in arbore (de la radacina spre frunze)
	//do
	
/*
	while(currentNode != nullptr)
	{
		// break;
		prev = currentNode;
		if (rel(e, currentNode))
		{
			currentNode = currentNode->lc;
		}
		else
		{
			currentNode = currentNode->rc;
		}
	}
*/
	//NodeSL* start_node = root;
	add_wrapper(root, e);
	len++;

//	while (currentNode->lc != nullptr || currentNode->rc != nullptr) // daca inca ma pot deplasa in arbore (de la radacina spre frunze)
	
	

}

ListIterator SortedIndexedList::iterator() {
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
}
