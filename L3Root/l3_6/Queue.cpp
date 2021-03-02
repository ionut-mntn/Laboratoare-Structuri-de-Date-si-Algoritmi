#include <iostream>
#include <fstream>
#include <exception>
#include "Queue.h"

using namespace std;

/*
worst case = O(n)
average case = O(n)
best case = Teta(1) (nu exista niciun element in coada, deci se va face doar o verificare)
*/
void Queue::toString() const 
{
	int aux = head;
	cout << "head= " << head << '\n';
	if (head != -1)
	{
		do
		{
			cout << " whaaat\n";
			// cout << "nodes[" << aux << "].prev = " << nodes[aux].prev << '\n';
			cout << "nodes[" << aux << "].data = " << nodes[aux].data.i << " " << nodes[aux].data.j << '\n';
			// cout << "nodes[" << aux << "].next = " << nodes[aux].next << '\n';
			aux = nodes[aux].next;
		} while (nodes[aux].next != -1);
		cout << '\n';
	}
}

/*
worst case = average case = best case = Teta(n) 
(la fiecare initializare a unei cozi, se vor face n pasi pentru a initializa
campul next pentru fiecare nod din `nodes`)
*/
Queue::Queue() {
	//TODO - Implementation

	cap = 105;
	//len = 0;

	head = -1;
	tail = -1;

	nodes = new NodeDLLA[cap];

	nodes[0].prev = -1;					// prima pozitie nu indica catre vreun vecin anterior
	nodes[0].next = 1;
	for (int i = 1; i < cap - 1; i++)
	{
		nodes[i].prev = i - 1;
		nodes[i].next = i + 1;
	}
	nodes[cap - 1].prev = cap - 2;
	nodes[cap - 1].next = -1;			// ultima pozitie nu indica catre vreun vecin posterior

	firstEmpty = 0; // prima pozitie pe care se poate adauga un nod in `nodes` este 0
}

/*
worst case = average case = best case = Teta(1) 
*/
/*
int Queue::getLen()
{
	return len;
}
*/

/*
worst case = O(n)
average case = O(n) - amortizat (deoarece se presupune ca realocarea memoriei nu se va face des)
best case = Teta(1)
*/
void Queue::push(pozitie_plan elem) {
	//TODO - Implementation

	if (firstEmpty == -1) // daca e full container ul
	{
		NodeDLLA* newNodes = new NodeDLLA[2 * cap];

		for (int i = 0; i < cap; i++)
		{
			//				cout << "intra";
			newNodes[i].data = nodes[i].data;
			newNodes[i].next = nodes[i].next;
			newNodes[i].prev = nodes[i].prev;
		}

		for (int i = cap; i < 2 * cap - 1; i++)
			newNodes[i].next = i + 1;		// similar initializarii de la inceput(cand se apeleaza constructorul)
		newNodes[2 * cap - 1].next = -1;

		nodes = newNodes;
		firstEmpty = cap;
		cap = cap * 2 + 1; 
		/*
		am ales sa adaug unu, in caz ca: vine cineva si trebuie sa "maintain my code", 
		doar ca din diferite considerente  are nevoie sa inceapa cu capacitatea 0; 
		dublarea m-ar fi tinut pe loc, dubland tot timpul capacitatea la zero
		*/
	}

	// adaug elementul in lista
	nodes[firstEmpty].data = elem;

	
	/* construiesc "legaturile" intre elementul tocmai introdus si ultimul
	element din container (adica legaturile dintre fosta si noua coada)
	daca ultimul element exista */ 
	if (tail == -1)			// sau head == -1 sau len == 0
	// daca am adaugat chiar primul element din coada, actualizez head ul
	{
		cout << "da, era goala\n";
		head = firstEmpty;
	}
	else
	// altfel, inseamna ca exista deja un "ultim element", deci:
	{
		/* construiesc legaturi intre fosta coada si actuala coada
		(elementul pe care tocmai l-am inserat) */
		nodes[tail].next = firstEmpty;
		nodes[firstEmpty].prev = tail;

	}

	// actualizez coada
	tail = firstEmpty;
	
	// actualizez firstEmpty
	firstEmpty = nodes[firstEmpty].next;

	/* adaugan mereu in coada, inseamna ca nu vor exista (la acest pas) vecini 
	urmatori, deci setez next ul cozii la -1 */ 
	nodes[tail].next = -1;

	//len++;
}

/*
worst case = average case = best case = Teta(1) (doar o verificare)
*/
pozitie_plan Queue::top() const {
	//TODO - Implementation

	if (isEmpty()) {
		//cout << "EXCEPTIE:::::::" << '\n';
		exception e; throw e;
	}

	return nodes[head].data;

}

/*
worst case = average case = best case = Teta(1) (doar assignment uri)
*/
pozitie_plan Queue::pop() {
	//TODO - Implementation
	
	/*
	 NOTA: 
	 In cazul resize ului de aici, din `pop` s-ar putea ca un element de care 
	 am nevoie sa fie stocat la un index dupa mai mare ca jumatate din capacitate,
	 deci se va face si o rearanjare a indecsillor
	*/

	/*
	if (len <= cap / 4)				
	{
		NodeDLLA* newNodes = new NodeDLLA[cap / 2];

		int aux = head;
		//for (int i = 0; i < cap / 2; i++)
		newNodes
		for (int i = 0; i < len; i++)
		{
			newNodes[i].data = nodes[aux].data;


			newNodes[i].next = nodes[aux].next;
			newNodes[i].prev = nodes[aux].prev;
			aux = nodes[aux].next;
		}
		for (int i = len; i < cap / 2 - 1; i++)
		{
			
			newNodes[i].next = i + 1;
		}
		newNodes[cap / 2] = -1;
		firstEmpty = cap;
		nodes = newNodes;
//		
		// firstEmpty = cap; 
		// ATENTIE! firstEmpty NU MAI TREBUIE ACTUALIZAT; ACEST INDEX ESTE DEJA UNUL DINTRE CELE LEN INDECSI POSIBILI
		cap /= 2; // am ales sa adaug unu, in caz ca: din diferite considerente cineva vine si trebuie 

	}
	*/

	if (isEmpty()) {
		exception f; throw f;
	}
	else
	{
		int aux = head;
		pozitie_plan elem = nodes[head].data;		// retin intr o variabila auxiliara ce
		// va trebui sa o returnez

		// actualizez head ul
		//if(nodes[head])
		head = nodes[head].next;
		cout << "head devine" << head << '\n';
		nodes[head].prev = -1; // head ul nu are vecini precedenti
		/*
		(observatie: De ce am modificat `nodes[head].prev`, dar nu m-am atins
		de indecsii catre vecini ai fostului head? Pentru ca atat valoarea
		de la indexul fostului head, cat si inedcsii catre vecinii sai vor
		fi modificate la un eventual `push`.
		*/

		/*creez legaturi intre firstEmpty(cel actual, urmand sa fie actualizat
		tot in aceasta functie) si fostul cap al cozii 
		(fostul head, actualizat putin mai sus)*/ 
		nodes[firstEmpty].prev = aux;
		nodes[aux].next = firstEmpty;

		// actualizez firstEmpty ul 
		firstEmpty = aux;
		nodes[firstEmpty].prev = -1; /*vecinul precedent nu exista*/
		/* OBS proprie: parcursul variabilei firstEmpty poate fi vazut ca o 
		deplasare printr-o stiva, deci firstEmpty nu avea niciodata vecin 
		in directia 'prev' reprezentand mereu varful stivei */ 
		
		
//		len--; // actualizez nr de elemente din coada
//		if (!len) { head = -1; tail = -1; }
		return elem;
	}
}

/*
worst case = average case = best case = Teta(1) ( o evaluare de expresie booleana )
*/
bool Queue::isEmpty() const {
	//TODO - Implementation

	return head == -1;
}

/*
worst case = O(n)
average case = O(n)
best case = Omega(1), deci chiar Teta(1) (niciun element in coada, deci se va face o verificare si se va parasi functia)
*/
/*
void Queue::toString()
{
	int aux = head;
	do
	{
		cout << "nodes["<<aux<<"] = "<<nodes[aux].data << '\n';
		aux = nodes[aux].next;
	}while (nodes[aux].next != -1);
	cout << '\n';
}
*/
/*
worst case = O(n), unde n - numarul de noduri
average case = O(n), chiar Teta(n), unde n - numarul de noduri ("Teta", deoarece oricare ar fi n, se vor efectua n pasi)
best case = Omega(1) (niciun nod in lista, se va face o singura verificare)
*/

Queue::~Queue() {
	//TODO - Implementation
	while (!isEmpty())			// cat timp coada nu este goala
	{
		//cout << " se elimina din coada: " << head->data << '\n';
		pop();					// sterge nodul din coada
	}
}

/*
NodeDLLA* Queue::getNodes()
{
	return nodes;
}
*/