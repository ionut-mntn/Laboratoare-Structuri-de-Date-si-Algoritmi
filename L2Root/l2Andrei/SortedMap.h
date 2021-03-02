#pragma once
//DO NOT INCLUDE SORTEDMAPITERATOR

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
#include <utility>
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TPAIR pair<TKey, TValue>(-11111, -11111);
class SMIterator;
typedef bool(*Relation)(TKey, TKey);

struct Node{
    TKey key;
    TValue value;
    Node* next;
    Node* prev;
    // pentru initializarea fiecarui nod
};
class SortedMap {
	friend class SMIterator;
    private:
        Node* head; // inceputul listei
        Node* tail; // finalul acesteia
        Relation r; // relatia de ordine in map
		//TODO - Representation
    public:

    // implicit constructor
    /*
     * se initializeaza head-ul si tail-ul cu pointeri la null
     * relatia de ordine din map se salveaza ca si atribut
     * complexitate O(n)
     */
    SortedMap(Relation r);

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key SMes not exist, a new pair is added and the value null is returned
	/*
	 * mai multe cazuri:
	 * 1) daca map-ul este gol, head-ul se initializeaza cu parametrii dati
	 * 2) daca este un singur nod(adica doar head-ul) se verifica daca nodul nou trebuie adaugat inainte, dupa, sau inlocuieste head-ul
	 *  ->daca trebuie adaugat dupa, tail-ul se initializeaza cu parametrii dati
	 *  ->daca trebuie adaugat inainte, tail-ul primeste atributele headului, iar headul este initializat cu parametrii dati
	 *  ->daca este egal cu head-ul, valoarea acestiua se inlocuieste cu o noua valoare
	 * 3) se parcurge map-ul pana nu se mai indeplineste conditia de relatie data
	 *  ->in cazul acesta, se creaza un nou nod care se introduce intre nodul la care s-a ajuns si prev-ul acestuia
	 *  ->in cazul in care nodul la care se oprste are key-ul egal cu parametrul dat, nodul se inlocuieste cu noile date
	 *
	 */
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	/*
	 * se parcurge map-ul dat prin initializarea unu iterator care porneste de la head si se verifica coditia de relatie pentru a inainta
	 * -> daca se gaseste un nod care are key-ul egal cu parametrul dat, se returneaza valoarea asociata acestui key
	 * -> daca se ajunge pana la tail, inseamna ca nodul nu exista in map, se returneaza NULL_TVALUE
	 * Complexitate: B:O(1) W:O(n) A:O(n)
	 */
	TValue search(TKey c) const;


	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	/*
	 * se verifica daca exista nodul cautat in lista
	 * -> daca nu, se returneazaa NULL_TVALUE
	 * -> daca da, 3 cazuri:
	 * 1) daca nodul cautat este head-ul; head-ul devine urmatorul nod
	 * 2) daca nodul cautat este tail-ul; tail-ul devine nodul anterior
	 * 3) se parcurge map-ul cu un iterator pana cand se gaseste nodul cautat; se inlocuieste prin stergerea legaturilor cu noul din fata si spatele acestuia(cele doua noduri se leaga intre ele)
	 * Complexitate: B:O(1) W:O(n) A:O(n)
	 */
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	/*
	 * daca map-ul este gol, se returneaza 0
	 * daca nu, se initializeaza un iter care parcurge map-ul de la head pana la tail, incremetandu-se un counter la fiecare pas
	 * se returneaza counter-ul
	 * Complexitate: O(n) in fiecare caz
	 */
	int size() const;

	//checks whether the map is empty or not
	/*
	 * daca atat head-ul cat si tail-ul sunt neinitializate se returneaza true
	 * daca nu false
	 * Complexitate O(1) in toate cazurile
	 */
	bool isEmpty() const;

    // return the iterator for the map
    // the iterator will return the keys following the order given by the relation
    SMIterator iterator() const;

    // destructor
    /*
     * se parcurge fiecare nod din lista si se dealoca
     * Complexitate: O(n) in fiecare caz
     */
    ~SortedMap();
};
