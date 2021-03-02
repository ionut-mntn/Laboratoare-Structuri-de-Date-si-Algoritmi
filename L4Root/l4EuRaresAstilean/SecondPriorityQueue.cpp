#include "SecondPriorityQueue.h"
#include <exception>
#include <iostream>

using namespace std;

SecondPriorityQueue::SecondPriorityQueue(Relation r) {
	/*
	Komplexitat: Es werden nur assignments gemacht und memory allocation
		Best Case: Theta(1)
		Worst Case: Theta(1)
		Average: Theta(1)
		Total: Theta(1)
	*/

	capacity = 5;
	size = 0;
	rel = r;
	heap = new Element[capacity];
}

//adds an element with a priority to the queue
void SecondPriorityQueue::push(TElem e, TPriority p) {
	/*
	Komplexitat:
		Best Case: Theta(1) amortisiert wenn resize gemacht werden muss und bubble_up im best case ist
		Worst Case: O(log2 n) wegen bubble up
		Average: O(log2 n)
		Total: O(log2 n)
	*/

	// Wenn kein Platz in dem heap mehr gibt -> resize mit doppelte Kapazitat
	if (size == capacity)
		resize();

	// Adding new Element at the End of the heap and then call bubble_up
	Element elem(e, p);
	heap[size] = elem;
	size++;

	// Bubble Up Funktion wie im Vorlesung
	bubble_up(size - 1);
	
}

//returns the element with the second highest priority with respect to the relation
//throws exception if the queue has less than 2 elements
Element SecondPriorityQueue::top() const {
	/*
	Komplexitat: O(n * log2 n) weil ein neues Heap gebaut wird
		Best Case: O(log 2n) wenn heap nur 1 Element verschiden von erstes enthalt, also nur 1 Element in neues Heap
		Worst Case: O(n * log2 n)
		Average: O(n * log2 n)
		Total: O(n * log2 n)
	*/

	if (this->atMostOne() == true)
		throw exception();
	else {
wy		// Neues Heap wrid gebaut, der neue Heap wird alle Elemente enthalten ausser die Elemente die die Prioritat gleich mit der Prioritat des ersten Element haben
		SecondPriorityQueue aux(rel);

		for (int i = 1;i<size;i++)
			if (heap[i].second != heap[0].second)
				aux.push(heap[i].first, heap[i].second);

		// Wruzel des neues heap ist der Element mit der zeitgrosste Prioritat aus des PQ2 heaps
		return aux.heap[0];
	}
}

//removes and returns the element with the second highest priority
//throws exception if the queue has less than 2 elements
Element SecondPriorityQueue::pop() {
	/*
	Komplexitat: O(n * log2 n + n) wegen bubble_down + top + Suchen Element von top in heap + resize_smaller()
		Best Case: O(log 2n + n) 
		Worst Case: O(n * log2 n + n)
		Average: O(n * log2 n + n)
		Total: O(n * log2 n + n)
	*/
	if(this->atMostOne() == true)
		throw exception();
	else {
		int poz=0;
		Element de_sters = top();

		// de_sters wird gesucht in PQ2 heaps, Komplexitat: O(n)
		for (int i = 0; i < size; i++)
			if (heap[i].first == de_sters.first && heap[i].second == de_sters.second) {
				poz = i;  // Von diese Position wird bubble_down aufgerufen
				break;
			}

		heap[poz] = heap[size - 1];
		size--;

		// Bubble Down Funktion wie im Vorlesung
		bubble_down(poz);

		// Wenn zu viel Platz nicht besitzt ist, dann wird Heap kleiner
		if (size == capacity / 4)
			resize_smaller();

		return de_sters;
	}		
}

//checks if the queue has at most one element
bool SecondPriorityQueue::atMostOne() const {
	/*
	Die Funktion checked ob es wenigstens zwei Elemente mit verschiede Prioritat gibt

	Komplexitat:
		Best Case: Theta(1) Wenn Zweites Element schon verschiede Prioritat hat
		Worst Case: Theta(n) Wenn alle Elemente gleich sind dann wird das ganze Heap parcurs
		Average: O(n) Element kann irgendwo sein
		Total: O(n) Wegen Worst Case
	*/

	// Wenn size < 2 dann konnen nicht zwei Elemente mit verschiedene Prioritat sein
	if (size < 2)
		return true;

	// Gehen durch Heap bis ein Elemente mit verschiedene Prioritat von ersten Element gefunden wird
	int current = 1;
	TPriority priority = heap[0].second;

	while (current < size) {
		if (heap[current].second != priority)
			return false;
		current++;
	}

	return true;
}

//destructor
SecondPriorityQueue::~SecondPriorityQueue() {
	/*
	Komplexitat:
		Best Case: Theta(1)
		Worst Case: Theta(1)
		Average: Theta(1)
		Total: Theta(1)
	*/
	
	delete[] heap;
}

void SecondPriorityQueue::print() {
	/*
	Komplexitat: Die Funktion zeigt auf dem Bildschirm nur die ersten 7 Elemente
		Best Case: Theta(1)
		Worst Case: Theta(1)
		Average: Theta(1)
		Total: Theta(1)
	*/

	cout << "\nPQ Heap: \n";
	cout << heap[0].first;
	cout << endl;
	int ct = 0;
	for (int i = 1; i < 8; i++) {
		if (ct == 2) {
			cout << endl;
			ct = 0;
		}
		ct++;
		cout << heap[i].first << " ";
	}

	cout << endl;	
}


void SecondPriorityQueue::bubble_up(int p) {
	/*
	Die Funktion ist dieselbe wie im Vorlesung, aber nur die Positionen sind verschieden, wegen erstes Arrays index 0

	Komplexitat: Der Baum besitzt logaritmische Hohe
		Best Case: Theta(1) Relation zwischen neues Knoten und Vaterknoten des neues Knoten ist falsch, dann ist der neue Knoten an die gute Position
		Worst Case: Theta(log2 n) Der neue Knoten muss der erste Knoten sein, dan werden log2 n Iterationen gemacht
		Average: O(log2 n)
		Total: O(log2 n)
	*/

	int poz = p;  // Position von welchem man den neuen Knoten hochsteigen muss
	Element elem = heap[p]; // Element der hochgestiegen werden muss
	
	int parent;  // Vaterknoten der akutellen Knoten
	if (poz - 1 >= 0)
		parent = (poz - 1) / 2;
	else
		parent = 0;

	while (poz > 0 && rel(elem.second, heap[parent].second)) {
		// Der Vaterknoten wird nach unten verschoben
		heap[poz] = heap[parent];
		poz = parent;
		parent = parent / 2;
	}

	heap[poz] = elem;  // Die Position des Elementes wurde gefunden
}


void SecondPriorityQueue::bubble_down(int p) {
	/*
	Die Funktion ist dieselbe wie im Vorlesung, aber nur die Positionen sind verschieden, wegen erstes Arrays index 0

	Komplexitat: Der Baum besitzt logaritmische Hohe
		Best Case: O(log2 n) 
		Worst Case: Theta(log2 n) Muss bis ganz unten abgesinkt werden
		Average: O(log2 n)
		Total: O(log2 n)
	*/
	
	int poz = p;  // Position von welchem man den neuen Knoten absinken muss
	Element elem = heap[p];  // Element der abgesinkt werden muss
	int RelationChild; // Der grosste/kleinste Sohn according to Relation
	
	while (poz < size) {
		RelationChild = -1;
		if (poz * 2 + 1 < size) // Wenn ja dann gibt ein linkes Kind
			RelationChild = poz * 2 + 1;
		if (poz * 2 + 2 < size && rel(heap[poz * 2 + 2].second, heap[RelationChild].second))  // Wenn ja dann gibt auch ein rechtes Kind und ist grosser
			RelationChild = poz * 2 + 2;
		if (RelationChild != -1 && rel(heap[RelationChild].second, elem.second)) {
			// Knoten wird nach unten geschoben
			heap[poz] = heap[RelationChild];
			poz = RelationChild;
		}
		else {
			// Position fur Knoten wurde gefunden und while wird gestopt
			heap[poz] = elem;
			poz = size + 1;
		}
	}
}


void SecondPriorityQueue::resize() {
	/*
	Komplexitat: Theta(n) weill jedes Mal alle Elemente kopiert werden
		Best Case: Theta(n) 
		Worst Case: Theta(n)
		Average: Theta(n)
		Total: Theta(n)
	*/
	capacity = capacity * 2;
	
	Element* temp = new Element[capacity];

	for (int p = 0; p < size; p++)
		temp[p] = heap[p];

	delete[] heap;

	heap = temp;
}


void SecondPriorityQueue::resize_smaller() {
	/*
	Komplexitat: Theta(n) weill jedes Mal alle Elemente kopiert werden
		Best Case: Theta(n)
		Worst Case: Theta(n)
		Average: Theta(n)
		Total: Theta(n)
	*/

	capacity = capacity / 2;

	Element* temp = new Element[capacity];

	for (int p = 0; p < size; p++)
		temp[p] = heap[p];

	delete[] heap;

	heap = temp;
}



    1
   / \
  2   3
 / \
4   5