#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
	//Complexitate best case=worst case=avg case = O(1)
	rel = r;
	lungime = 0;
	nod = new Node();
	nod->next = nullptr;
	nod->prev = nullptr;
	nod->wert = NULL_TCOMP;




}

int SortedIndexedList::size() const {
	//TODO - Implementation
	//Complexitate best case=worst case=avg case = O(1)

	//returneaza lungimea listei

	return lungime;
}

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	//Complexitate best case=worst case=avg case = O(1)

	//daca lungimea = 0 atunci returneaza true, daca nu, returneaza false
	return !(bool)lungime;
}

TComp SortedIndexedList::getElement(int i) const {
	//TODO - Implementation
	//Complexitate
	//best case: O(1)
	//worst case: O(n)
	//avg case: O(n)

	Node* aux = nod;
	if (i < lungime && i >= 0) { //verifica daca indexul este valid
		cout << nod << ' ' << lungime << " get element pe pozitia " << i << "\n";
		
		
		int ct = 0;
		while (ct < i) {
			cout << aux << ' ';

			aux = aux->next;
			ct++;
		}
		//aux este nodu de la indexul i
		cout << "\n getElement adresa" << aux;
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
	//Complexitate
//best case: O(1)
//worst case: O(n)
//avg case: O(n)

	if (i >= 0 && i < lungime) { //verifica daca indexul este valid
		Node* aux = nod;
		TComp el;

		int ct = 0;

		if (i == 0) { //cazul in care vrem sa stergem nodul de pornire al listei
			std::cout << "a intrat pe pos 0 " << lungime << '\n';
			el = nod->wert;
			if (nod->next != nullptr)
				nod = nod->next;
			nod->prev = nullptr;
			lungime--;

			return el;
		}
		else {
			while (ct < i) {

				ct++;
				aux = aux->next;

			} //aux este nodul pe care vrem sa il stergem
			std::cout << "la pos " << i << " avem valoare " << aux->wert << std::endl;


			if (ct == lungime - 1) {//daca nodul pe care vrem sa il stergem este ultimul nod din lista
				aux->prev->next = nullptr;

			}


			el = aux->wert;
			//se creaza linkuri noi
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
	//Complexitate
//best case: O(1)
//worst case: O(n)
//avg case: O(n)

	/*
	if (!isEmpty()) {
		//TODO - Implementation
		Node* aux = nod;
		//std::cout << "Lungime= " << lungime;
		int ct = 0;
		while (ct < lungime) {
			std::cout << "pozitia: " << ct << ": " << nod << ' ' << aux << '\n';

			if (aux->wert == e) //daca valoare este gasita atunci se returneaza pozitia si functia se opreste
			{
				cout << "pos: " << ct << '\n';
				return ct;
			}
			ct++;
			aux = aux->next;

		}
	}
	*/


	Node* current = nod;
	int i = 0;
	if (nod->wert == e)
		return i;
	while (current != NULL) {
		if (current->wert == e)
			return i;
		current = current->next;
		i++;
	}


	return -1;
}

void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
	//Complexitate
	//best case: O(1)
	//worst case: O(n)
	//avg case: O(n)
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
		while (rel(aux->wert, e) && aux->next != nullptr) { //se cauta elementul dupa care vine inserata valoarea e
			//std::cout<<aux->wert;
			aux = aux->next;
		}

		//std::cout <<e <<" vine bagat dupa "<<aux->wert<<rel(aux->wert,e)<<"\n";

		if (rel(aux->wert, e) == 0) { //daca rel(aux->wert, e) = 0 inseamna ca elementul vine adaugat undeva in mijlocul liste, nu la final
			if (aux->prev == nullptr) {
				//daca trebe bagat inaintea primului nod
				//std::cout <<e<< " trebe bagat in fata lui "<<aux->wert;
				nod = temp;
				nod->prev = nullptr;
				nod->next = aux;
			}
			else {
				//daca trebe bagat undeva in mijlocul listei
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

ListIterator SortedIndexedList::iterator() {
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	/*
	//while de la primul nod pana la ultimul si le sterg
	cout << "destructor ";
	if (!isEmpty()) {
		Node* temp = nod;
		while (temp != nullptr) {
			cout << "while destrutor\n";
			Node* curr = temp->next;
			delete temp;
			temp = curr;



		}
		nod = NULL;
	}
	
	*/

}
