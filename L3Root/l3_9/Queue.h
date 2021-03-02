#pragma once
#include <vector>
#include <iostream>

using namespace std;
// using std::ostream;
//DO NOT CHANGE THIS PART

typedef int TElem;

#define NULL_TELEM -11111


/*
class pozitie_plan()
{

private:
	int dist;
public:
	int i, j;
}
*/


struct pozitie_plan
{

	int i, j, dist;

//	ostream& operator<<(ostream& os, const pozitie_plan& p);
//	friend ostream& operator<<(ostream& os, const pozitie_plan& p);
};
bool operator==(const pozitie_plan& lhs, const pozitie_plan& rhs);

#define NULL_POZITIE_PLAN pozitie_plan{-1,-1,-1}

/* DIN NOU O OBSERVATIE PE CARE AM MAI FACUT O, DAR FOARTE IMPORTANTA!!
operatorul asta `<<` ia ca "left-hand-operator" un stream si ca "right-hand-operator"
doar ca eu adaugandu l in clasa, o sa incerce cumva sa imi ia "this"ul ca "left-hand-operator"
which is not cool; asa ca operatorul asta nu o sa fie niciodata membru al unei clase!
SI DIN NOU, RETURNEAZA REFERINTA LA UN STREAM, PRIMESTE CA PARAMETRU REFERINTA LA UN STREAM
SI PUR SI SIMPLU "APELEAZA" STREAM UL ALA, ADICA VA CONCATENA LA STREAM CELE 2 VALORI
*/
/*
ostream& operator<<(ostream& os, const pozitie_plan &p)
{
	os << p.i << " " << p.j << " ";
	return os;
}
*/

struct NodeDLLA {
	pozitie_plan data;
	int prev;
	int next;
};


class Queue
{
private:
	//TODO - Representation

	int cap;	// am ales eu, arbitrar
//	int len;	// am tinut si un len, pentru a-mi fi mai usor
	// sa fac resize ul: voi interoga in functia de remove(si nu numai) aceasta
	// variabila pentru a vedea daca este nevoie de resize

	NodeDLLA* nodes;
	
	int head;
	int tail;
	
	int firstEmpty;

public:

	int getHead();
	int getTail();
	// returneaza numarul de elemente din coada
	// int getLen();

	Queue();

	//pushes an element to the end of the queue
	void push(pozitie_plan e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	pozitie_plan top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	pozitie_plan pop();

	//checks if the queue is empty
	bool isEmpty() const;

	// afiseaza atributele 'data' ale elementelor din coada, unul langa celalalt ('head' va pointa catre cel mai din stanga nod, 'tail' cel mai din dreapta)
	void toString () const;

	// getter atribut `nodes`
	NodeDLLA* getNodes();

	// destructor
	~Queue();
};
