#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
	rel = r;
	lungime = 0;
	nod = new Node();
	nod->next = nullptr;
	nod->prev = nullptr;
	nod->wert = NULL_TCOMP;

	
}

int SortedIndexedList::size() const {
	//TODO - Implementation
	return lungime;
}

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	return !(bool)lungime;
}

TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation
	Node* aux = nod;
	if (i < lungime && i>= 0) {
		cout <<nod<<' '<< lungime <<" get element pe pozitia "<<i<<"\n";
		int ct = 0;
		while (ct<i) {
			cout << aux << ' ';

			aux = aux->next;
			ct++;
		}
		cout <<"\n getElement adresa"<< aux;
		return aux->wert;

	}
	else {
		exception e;
		throw e;
	}
	

	return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
	std::cout << "de sters pos: " << i << std::endl;
	if (i >= 0 && i < lungime) {
		Node* aux = nod;
		TComp el;

		int ct = 0;

		if (i == 0) {
			std::cout << "a intrat pe pos 0 " << lungime<<'\n';
			el = nod->wert;
			if(nod->next != nullptr)
				nod = nod->next;
			nod->prev = nullptr;
			lungime--;

			return el;
		}
		else {
			while (ct < i) {

				ct++;
				aux = aux->next;

			}
			std::cout << "la pos " << i << " avem valoare " << aux->wert << std::endl;


			if (ct == lungime - 1) {
				aux->prev->next = nullptr;
				
			}


			el = aux->wert;
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
			lungime--;
			return el;

		}
		


	}
	else {
		exception e;
		throw e;
	}
	//TODO - Implementation
	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	Node* aux = nod;
	//std::cout << "Lungime= " << lungime;
	int ct = 0;
	while (ct<lungime) {
		std::cout <<"pozitia: "<<ct<<": "<< nod << ' ' << aux << '\n';

		if (aux->wert == e)
			return ct;
		ct++;
		aux = aux->next;

	}


	return -1;
}

void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
	//std::cout << "add\n";
	Node* temp = new Node();
	temp->wert = e;
	temp->next = nullptr;

	Node* aux = nod;
	if (aux->wert == NULL_TCOMP) {
		nod = temp;
		nod->prev = nullptr;
		//std::cout << "primul nod \n";
	}
	else {
		/*
		//asta adauga la final
		while (aux->next != nullptr) {
			std::cout << "nu e primul nod \n";
			aux = aux->next;
		}
		temp->prev = aux;
		aux->next = temp;
		*/
		// asta adauga dupa relatia rel
		while (rel(aux->wert,e) && aux->next != nullptr) {
			//std::cout<<aux->wert;
			aux = aux->next;
		}
		
		//std::cout <<e <<" vine bagat dupa "<<aux->wert<<rel(aux->wert,e)<<"\n";
		if (rel(aux->wert, e) == 0) {
			if (aux->prev == nullptr) {
				//daca trebe bagat inaintea primului nod
				//std::cout <<e<< " trebe bagat in fata lui "<<aux->wert;
				nod = temp;
				nod->prev = nullptr;
				nod->next = aux;
			}
			else {
				
				temp->prev = aux->prev;
				temp->next = aux;
				aux->prev->next = temp;
				aux->prev = temp;

			}
			
		}
		else {
			//trebe bagat la final
			temp->prev = aux;
			aux->next = temp;
		}
		

	}
	
	lungime++;
	

	

	


	

}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation

	//while de la primul nod pana la ultimul si le sterg

}
