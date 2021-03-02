#include <iostream>
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
	//TODO - Implementation
	
	/*
	Komplexitat: Jedes Mal mussen die Elemente initialisiert werden und alle Positionen aus dem Arrays mit links als frei markieren, 
				 also werden wenigsten "capacitat" assignments gemacht
		Best Case: Theta(n)
		Worst Case: Theta(n)
		Average: Theta(n)
		Total: Theta(n)
	*/

	// Alle Daten werden initalisiert
	this->size = 0;
	this->capacity = 5; 
	this->head = -1;
	this->tail = -1;
	this->elemente = new Element[capacity];
	this->next = new int[capacity];
	this->prev = new int[capacity];
	this->rel = r;
	this->firstEmpty = 0;
	
	// Die next/prev array haben die Links zu die nachste/vorige leere Position, also am Anfang alle Positionen sind leer
	for (int i = 0; i < capacity - 1; i++) {
		next[i] = i + 1;
		prev[i] = i + 1;
	}
	next[capacity - 1] = -1;
	prev[capacity - 1] = -1;
}


void PriorityQueue::push(TElem e, TPriority p) {
	//TODO - Implementation

	/*
	Komplexitat:
		Best Case: Theta(1), wenn Queue leer ist, oder das neue Elemente am "Amfang"  oder am "Ende" einfugen kann
		Worst Case: Theta(n), wenn die Relation zwischen alle Elemente checken muss, um die richtige Reihefolge und Links zu bestimmen
					oder wenn die resize Funktion angerufen wird
		Average: O(n)
		Total: O(n)
	*/

	// Wenn kein Platz mehr in den Arrays gibt, dan wird die resize function geruft
	if (size == capacity)   
		resize();
	
	int new_firstEmpty = next[firstEmpty];    // Im new_firstEmpty wird die nachste leere Position gespeichert

	// Paar <element,priority> wird auf die erste leere Position eingefugt
	elemente[firstEmpty].first = e;          
	elemente[firstEmpty].second = p;

	// Wenn Queue leer ist
	if (head == -1) {			     
		next[firstEmpty] = -1;       // Erste Element wurde jetzt eingefugt, also es gibt kein nachste
		prev[firstEmpty] = -1;       // und kein vorigen Element
		head = 0;
		tail = 0;
	}
	// Wenn Queue nicht empty ist
	else {							 
		// Es wird gechecked, ob Element am Anfang eingefugt werden kann
		if (rel(elemente[head].second, p) == false) {        
			next[firstEmpty] = head;
			prev[firstEmpty] = -1;
			prev[head] = firstEmpty;
			head = firstEmpty;
		}
		// Es wird gechecked, ob Element am Ende eingefugt werden kann
		else if (rel(elemente[tail].second, p) == true) {   
			next[firstEmpty] = -1;
			prev[firstEmpty] = tail;
			next[tail] = firstEmpty;
			tail = firstEmpty;
		}
		// Element kann weder am Anfang noch am Ende eingefugt werden kann, also muss zwischen zwei Elemente eingefugt werden
		else {  
			// Es wird die korekte Position gesucht
			int current = head;
			while (rel(elemente[next[current]].second, p) == true)
				current = next[current];

			// Es werden die neue links gemacht zwischen die Elemente
			next[firstEmpty] = next[current];
			prev[firstEmpty] = current;

			// Links zu die erste leere Position werden geandert, weil diese nicht mehr eine leere Position ist
			next[current] = firstEmpty;
			prev[next[current]] = firstEmpty;
		}
	}

	size++;

	// Wenn size ist gleich mit capacity, dann new_firstEmpty ware -1 sein, aber -1 ist nicht eine valide Position 
	if (size == capacity)
		firstEmpty = size;  // Am nachsten Aufruf von push, capacitat wird vergrossert, also firstEmpty=size wird keine Error geben
	else
		firstEmpty = new_firstEmpty;
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	//TODO - Implementation

	/*
	Komplexitat:
		Best Case: Theta(1)
		Worst Case: Theta(1)
		Average: Theta(1)
		Total: Theta(1)
	*/

	if (this->isEmpty() == false)
		return this->elemente[head];
	else
		throw exception();
}

Element PriorityQueue::pop() {
	//TODO - Implementation

	/*
	Komplexitat: Kompelexitat ist uberall Theta(1), weil nur die Links und die Werte werden verandert.
				 Man kann den Element, der zu loschen ist, direkt angreifen, weil dieses Element jedes Mal der head ist
		Best Case: Theta(1)
		Worst Case: Theta(1)
		Average: Theta(1)
		Total: Theta(1)
	*/

	// Wenn das Queue leer ist
	if (this->isEmpty() == true)
		throw exception();
	// Wenn Queue nur ein einziges Element enthalt
	if (head == tail) {
		Element to_delete = elemente[head];
		elemente[head] = NULL_TELEM;
		head = tail = -1;

		size--;
		firstEmpty = 0;

		return to_delete;
	}
	// Wenn Queue mindestens 2 Elemente hat
	else {
		Element to_delete = elemente[head];
		elemente[head] = NULL_TELEM;
		int old_head = head;

		// Head muss geloscht werden, also nachstes Element wird das neue head sein
		head = next[head];
		prev[head] = -1;

		// Hier werden die alten links "geloscht", eigentlich werden zu den firstEmpty gebunden, um eine neue freie Position zu markieren
		next[old_head] = firstEmpty;
		firstEmpty = old_head;

		size--;

		return to_delete;
	}

}

bool PriorityQueue::isEmpty() const {
	//TODO - Implementation

	/*
	Komplexitat:
		Best Case: Theta(1)
		Worst Case: Theta(1)
		Average: Theta(1)
		Total: Theta(1)
	*/

	if (this->head == -1)
		return true;
	return false;
}


PriorityQueue::~PriorityQueue() {
	//TODO - Implementation

	/*
	Komplexitat:
		Best Case: Theta(1)
		Worst Case: Theta(1)
		Average: Theta(1)
		Total: Theta(1)
	*/

	// In Destruktor mussen nur die arrays geloscht werden
	delete[] elemente;
	delete[] next;
	delete[] prev;
};



/*
Von mich definierte print Funktion, um das Konzept am Anfang zu verstehen, benutzt meisten fur die Shorttests
void PriorityQueue::print() {
	for (int i = 0; i < size; i++)
		cout << "(" << elemente[i].first << ", " << elemente[i].second << ")  " << next[i] << " " << prev[i] << endl;
	cout << "head=" << head << "  tail=" << tail << "  first=" << firstEmpty;
	cout << endl << endl << endl;
	
}
*/


void PriorityQueue::resize() {
	
	/*
	Komplexitat: Jedes Mal mussen die Elemente kopiert werden und die neue Position als frei markieren, 
				 also werden wenigsten "capacitat" assignments gemacht
		Best Case: Theta(n)
		Worst Case: Theta(n)
		Average: Theta(n)
		Total: Theta(n)
	*/
	
	capacity = capacity * 2;

	// Temporary arrays umd die Elemente zu speichern
	Element* new_elemente;
	int* new_next;
	int* new_prev;
	new_elemente = new Element[capacity];
	new_next = new int[capacity];
	new_prev = new int[capacity];

	// Die Elemente werden in die Kopierungsarrays kopiert
	for (int i = 0; i < size; i++) {
		new_elemente[i] = elemente[i];
		new_next[i] = next[i];
		new_prev[i] = prev[i];
	}

	// Die neue freue Position werden als frei markiert
	for (int i = size; i < capacity - 1; i++) {
		new_next[i] = i + 1;
		new_prev[i] = i + 1;
	}
	new_next[capacity - 1] = -1;
	new_prev[capacity - 1] = -1;

	// Alte arrays werden geloscht, werden nicht mehr gebraucht
	delete[] this->elemente;
	delete[] this->next;
	delete[] this->prev;

	elemente = new Element[capacity];
	next = new int[capacity];
	prev = new int[capacity];

	// Member class arrays bekommen die Adressen der temporary arrays
	elemente = new_elemente;
	next = new_next;
	prev = new_prev;

}


void PriorityQueue::reverse() {
	/*
	Pentru a inversa ordinea elementelor, doar trebuie interschimbate elementul next[i] cu prev[i] + head si tail.

	Komplexitat: Es mussen alle Werte der next und prev Arrays geandert, also man muss durch Arrays gehen jedes Mal, alle Cases sind gleich.
		Best Case: Theta(n)
		Worst Case: Theta(n)
		Average: Theta(n)
		Total: Theta(n)
	*/
	int new_head = tail;
	int new_tail = head;
	for (int i = 0; i < size; i++) {
		int aux = next[i];
		next[i] = prev[i];
		prev[i] = aux;
	}

	head = new_head;
	tail = new_tail;
}