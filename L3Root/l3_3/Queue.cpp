#include <iostream>
#include <exception>
#include "Queue.h"
using namespace std;

/*
worst case = average case = best case = Teta(1)
*/
Queue::Queue() {
	//TODO - Implementation

	cap = 105;
	// len = 0;

	head = -1;
	tail = -1;

	NodeDLLA* nodes = new NodeDLLA[cap];
	
	nodes[0].prev = -1;					// prima pozitie nu indica catre vreun vecin anterior
	nodes[0].next = 1;
	for (int i = 1; i < cap - 1; i++)
	{
		nodes[i].prev = i - 1;
		nodes[i].next = i + 1;
	}
	nodes[cap - 1].prev = cap - 2;
	nodes[cap - 1].next = -1			// ultima pozitie nu indica catre vreun vecin posterior
	
	firstEmpty = 0; // !! 0, nu -1 aici!!

}

/*
worst case = average case = best case = Teta(1)

int Queue::getLen()
{
	// return len;
	return tail - head + 1; // cred
}
*/


/*
worst case = average case = best case = Teta(1)
*/
// push(TElem elem, poz = len)
void Queue::push(TElem elem) {
	//TODO - Implementation

	//if (firstEmpty == -1)			// ????????
	// pai firstEmpty ar putea fi pe ultima 
	// daca s-au tot adaugat elemente pana cand s-a ajuns pe o pozitie
	// care nu mai are vecin superior("superior" = cu index de ordine mai mare
	///CRED CA E CLAR ACUM
	if(firstEmpty==-1) // daca e full container ul
	{
		NodeDLLA *newNodes = new NodeDLLA[2 * cap];

		for (int i = 0; i < cap; i++)
		{
			newNodes[i].data = nodes[i].data;
			newNodes[i].next = nodes[i].next;
			newNodes[i].prev = nodes[i].prev;
		}

		for (int i = cap; i < 2 * cap - 1; i++)
			newNodes[i] = i + 1;		// similar initializarii de la inceput(cand se apeleaza constructorul)
		newNodes[2 * cap - 1] = -1;

		nodes = newNodes;
		firstEmpty = cap;
		cap = cap * 2 + 1; // am ales sa adaug unu, in caz ca: din diferite considerente cineva vine si trebuie 
		// sa maintain my code, doar ca are nevoie sa inceapa cu capacitatea 0; dublarea m-ar fi tinut pe loc,
		// dubland tot timpul capacitatea la zero
	}

	/*
	int newPosition = firstEmpty;

	nodes[newPosition].data = elem;
	firstEmpty = nodes.next[firstEmpty];	// cred
	//nodes[newPosition].next = head;	// adaug mereu LA COADA BOSS!!
	nodes[newPosition]


	if (head == -1) tail = newPosition;
	head = newPosition;
	*/

	// adaug noul elementul `elem` pe prima pozitie libera
	nodes[firstEmpty].data = elem;
	
	// actualizez legaturile
	nodes[tail].next = firstEmpty; // nu mai e -1, ci trebuie sa "pointeze" catre noul element, adaugat in coada(deci pe ultima pozitie)
	nodes[firstEmpty].prev = tail;
	//// nodes[firstEmpty].next = = 1;	///NU FAC ASTA AICI PENTRU CA PIERD DATE!!
//	nodes[firstEmpty].next = nodes[firstEmpty] // aici nu mai e nevoie, pentru ca este setat deja nextul:
	// ori din initializare de la inceput (din constructor)
	// ori dintr un remove (pop)

	// BA CRED CA TOTUSI TREBUIE ACTUALIZAT! (urmatoarele randuri pot fi inlocuite de am comentat mai jos cu /*...*/ ,
	// inainte de a se incheia functia
	
	
	/*
	int aux = nodes[firstEmpty].next;
	nodes[firstEmpty].next = -1;	// dar retin intr o variabila auxiliara pozitia urmatoarei pozitii empty, pentru
	// a putea actualiza mai jos (se putea si fara variabila auxiliara `aux`, dar am zis ca asa se intelege mai bine 
	// ce se intampla)

	// actualizez indexul care imi "pointeaza" catre coada (pentru ca mereu adaug la coada - principiul cozii)
	tail = firstEmpty;

	// actualizez firstEmpty !!
	firstEmpty = aux;
	

	if (head == -1) head = tail; // daca am introdus chiar primul element, trebuie actualizat si head ul

	len++;
	*/

	tail = firstEmpty;
	firstEmpty = nodes[firstEmpty].next;
	nodes[tail].next = -1;



	/*
	// asa nu ar fi mers(prima varianta):
	nodes[firstEmpty].next = -1;

	// actualizez indexul care imi "pointeaza" catre coada (pentru ca mereu adaug la coada - principiul cozii)
	tail = firstEmpty;

	// actualizez firstEmpty !!
	firstEmpty = nodes[firstEmpty].next;
	
	//NU AR FI MERS, TOCMAI PENTRU CA PIERDEAM ORICE REFERINTA LA ELEMENTUL TOCMAI INTRODUS (indexul sau),
	// adica ultima instructiune ar fi facut nextul lui firstEmpty -1 si dupa aia ...

	*/


	/*
	// asa se facea fara aux:
	
		tail = firstEmpty;			// acum practic am 2 "referinte" la pozitia care ma intereseaza, deci e clar 
		// ca pot scapa de una, fara a pierde ceva de care am nevoie (un index, in cazul meu)
		firstEmpty = nodes[firstEmpty].next;
		nodes[tail].next = -1;

	*/
}

/*
worst case = average case = best case = Teta(1)
*/
TElem Queue::top() const {
	//TODO - Implementation

	if (isEmpty()) {
		exception e; throw e;
	}
	return nodes[head].data;

	//return NULL_TELEM;
}
/*
worst case = average case = best case = Teta(1) ( doar assignment uri, nimic special; nicio iteratie, nimic )
*/
TElem Queue::pop() {
	//TODO - Implementation
	if (len <= cap / 4)
	{
		NodeDLLA* newNodes = new NodeDLLA[cap / 2];

		for (int i = 0; i < cap / 2; i++)
		{
			newNodes[i].data = nodes[i].data;
			newNodes[i].next = nodes[i].next;
			newNodes[i].prev = nodes[i].prev;
		}

		for (int i = cap; i < 2 * cap - 1; i++)
			newNodes[i] = i + 1;		// similar initializarii de la inceput(cand se apeleaza constructorul)
		newNodes[2 * cap - 1] = -1;

		nodes = newNodes;
		// firstEmpty = cap; 
		// ATENTIE! firstEmpty NU MAI TREBUIE ACTUALIZAT; ACEST INDEX ESTE DEJA UNUL DINTRE CELE LEN INDECSI POSIBILI
		cap /= 2; // am ales sa adaug unu, in caz ca: din diferite considerente cineva vine si trebuie 

	}
	
	if (isEmpty()) {
		exception f; throw f;
	}
	else
	{		// HEAD = HEAD.NEXT !!
		/*
		// TElem aux = nodes[head].data;
		head = nodes[head].next;
		//nodes[head].prev = -1; //atentie! head ul actualizat

		return nodes[nodes[head]].prev;
		// si cu first empty de facut ceva aici!
		// nu cred ca mai trebuie facut ceva cu el, pentru ca eu mereu scot din head ( de pe pozitia 0, cum ar veni )
		*/

		// stochez intr o varaibila auxiliara ce am de returnat
		TElem elem = nodes[head].data;
		
		// marchez pozitia de pe care elimin(head ul) ca o pozitie pe care se pot insera alte elemente, 
		// deci parte din "array ul firstEmpty" 
		
//		firstEmpty = head;
//		nodes[firstEmpty].next = nodes
		nodes[head].next = firstEmpty;
		nodes[head].prev = -1;		// firstEmpty e exact ce zice numele: firstEmpty!! nu are vecini inaintea sa;
		// e ca si cum as avea o stiva de firstEmpty uri; de fiecare data cand actualizez firstEmpty ul, acesta devine
		// "primul" firstEmpty si pointeaza spre urmatorul(fostul) firstEmpty
		firstEmpty = head;
		/*
		nodes[firstEmpty].next = head;
		nodes[head].prev = firstEmpty;
		firstEmpty
		*/

		// nodes[firstEmpty].next = head;
		// 
//		head = nodes[head].next;
	
		return elem;
	}

}

/*
worst case = average case = best case = Teta(1) ( o evaluare de expresie booleana )
*/
bool Queue::isEmpty() const {
	//TODO - Implementation

//	return (head == nullptr);

	return head == -1;

	//return false;
}

/*
worst case = O(n)
average case = O(n)
best case = Omega(1), deci chiar Teta(1) (niciun element in coada, deci se va face o verificare si se va parasi functia)
*/
/*
void Queue::toString()
{
	NodeDLLA* aux = head;
	while (aux != nullptr)
	{
		//cout << aux->data << " ";
		cout << aux->data.i << " " << aux->data.j << '\n';
		aux = aux->next;
	}
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

