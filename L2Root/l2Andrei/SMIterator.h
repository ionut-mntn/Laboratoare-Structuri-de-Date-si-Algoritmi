#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

    Node* iter; // iteratorul este un pointer la un nod din map, initial pointeaza catre null
	//TODO - Representation

public:
    /*
     * daca map nu este gol, iteratorul se muta pe nodul head
     * complexitate O(1)
     */
	void first();
	/*
	 * daca pozitia pe care se afla este valida iar pozitia urmatoare exista(nu este null), poate inainta iteratorul
	 * complexitate O(1)
	 */
	void next();
	/*
	 * daca iteratorul este valid, trece pe pozitia urmatoare
	 * complexitate O(1)
	 */
	bool valid() const;
	/*
	 * se returneaza pair-ul de key si value al nodului pe care se afla iteratorul
	 * complexitate O(1)
	 */
    TElem getCurrent() const;
    /*
     * asemanator cu functia next()
     * daca itereatorul este pe o pozitie valida, trece pe pozitia anterioara
     * complexitate O(1)
     */
    void prev();
};

