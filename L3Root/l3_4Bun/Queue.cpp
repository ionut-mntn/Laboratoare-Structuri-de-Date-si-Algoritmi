#include <iostream>
#include <exception>
#include "Queue.h"
using namespace std;

void Queue::toString() const 
{
	int aux = head;
	do
	{
		cin.get();
		cout << "nodes[" << aux << "] = " << nodes[aux].data << '\n';
		aux = nodes[aux].next;
	} while (nodes[aux].next != -1);
	cout << '\n';
}

/*
worst case = average case = best case = Teta(1)
*/
Queue::Queue() {
	//TODO - Implementation

	cap = 105;
	len = 0;

	head = -1;
	tail = -1;

	nodes = new NodeDLLA[cap];
	//NodeDLLA* nodes = new NodeDLLA[cap];
	/*
	cout << nodes[0].data << '\n';
	cout << nodes[1].data << '\n';
	cout << nodes[2].data << '\n';
	cout << nodes[3].data << '\n';
	*/

	nodes[0].prev = -1;					// prima pozitie nu indica catre vreun vecin anterior
	nodes[0].next = 1;
	for (int i = 1; i < cap - 1; i++)
	{
		nodes[i].prev = i - 1;
		nodes[i].next = i + 1;
	}
	nodes[cap - 1].prev = cap - 2;
	nodes[cap - 1].next = -1;			// ultima pozitie nu indica catre vreun vecin posterior

	for (int i = 0; i < cap; i++)
		cout << nodes[i].prev << " " << nodes[i].next << '\n';

	firstEmpty = 0; // !! 0, nu -1 aici!!
	cout << "Bun constructor\n";
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
			cap = cap * 2 + 1; // am ales sa adaug unu, in caz ca: din diferite considerente cineva vine si trebuie 
			// sa maintain my code, doar ca are nevoie sa inceapa cu capacitatea 0; dublarea m-ar fi tinut pe loc,
			// dubland tot timpul capacitatea la zero
		}

		/*
		// adaug noul elementul `elem` pe prima pozitie libera
		nodes[firstEmpty].data = elem;

		// construiesc legaturile dintre noul element adaugat si fosta coada
		// (fostul ultim element)
		nodes[tail].next = firstEmpty; // nu mai e -1, ci trebuie sa "pointeze" catre noul element, adaugat in coada(deci pe ultima pozitie)
		nodes[firstEmpty].prev = tail;

		// actualizez coada si indexul ce indica prima pozitie libera unde se
		// poate adauga un element nou(adica firstEmpty ul)
		tail = firstEmpty;
		firstEmpty = nodes[firstEmpty].next;
		nodes[tail].next = -1;
		*/
		cout << "1.fE= " << firstEmpty << '\n';

		nodes[firstEmpty].prev = tail;
		nodes[firstEmpty].data = elem;
		nodes[firstEmpty].next = -1;		// mereu adaug la coada, deci niciun urmator element

		if (tail == -1) // sau: `head == -1`  sau: `len == -1`
		{
			cout << "da s a bagat un element in coaja asta\n";
			tail = firstEmpty;
			head = firstEmpty;
			//firstEmpty = firstEmpty
		}
		else
		{
			nodes[tail].next = firstEmpty; // aici tail sigur nu va fi 01
			tail = firstEmpty;
			cout << "2.fE= " << firstEmpty << '\n';
			//firstEmpty = nodes[firstEmpty].next;
			//nodes[tail].next = -1; // nu mai e nevoie, s a facut mai sus
			
			//		cout << "FE:" << firstEmpty << '\n';
	

		}
		cout << "nodes[" << firstEmpty << "].next=" << nodes[firstEmpty].next << '\n';
		firstEmpty = nodes[firstEmpty].next;
		cout << "fE dupa add:" << firstEmpty << '\n';
		/////NU-I BUN:tail = firstEmpty; // daca il pun aici, nu va fi mereu
		// la valoarea la care ma astept sa fie

		/*
		firstEmpty = nodes[firstEmpty].next;

			nodes[tail].next = firstEmpty;
			firstEmpty = nodes[firstEmpty].next;
	//		cout << "FE:" << firstEmpty << '\n';
			tail = firstEmpty;
		*/

		len++;
	//	if (len == 1) head = tail;
	}

/*
worst case = average case = best case = Teta(1)
*/
TElem Queue::top() const {
	//TODO - Implementation

	if (isEmpty()) {
		cout << "EXCEPTIE:::::::" << '\n';
		exception e; throw e;
	}

	toString(); // !! atentie!! functia asta
	// top este `const`! iar toString nu este const!
	// implicit nu am garantia ca toString nu va modifica 
	// starea obiectului! => trebuie sa fac si toString `const`
	
	cout << head << '\n';
	cout << "head="<<head << " " << "tail="<<tail << '\n';
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
			newNodes[i].next = i + 1;		// similar initializarii de la inceput(cand se apeleaza constructorul)
		newNodes[2 * cap - 1].next = -1;

		nodes = newNodes;
		// firstEmpty = cap; 
		// ATENTIE! firstEmpty NU MAI TREBUIE ACTUALIZAT; ACEST INDEX ESTE DEJA UNUL DINTRE CELE LEN INDECSI POSIBILI
		cap /= 2; // am ales sa adaug unu, in caz ca: din diferite considerente cineva vine si trebuie 

	}
	
	if (isEmpty()) {
		exception f; throw f;
	}
	else
	{
		int aux = head;
		TElem elem = nodes[head].data;

		// actualizez head ul
		head = nodes[head].next;
		nodes[head].prev = -1; // head ul nu are vecini precedenti

		// creez legaturi intre firstEmpty(cel actual, urmand sa fie actualizat
		// tot in aceasta functie) si fostul cap al cozii 
		// (fostul head, actualizat putin mai sus)
		nodes[firstEmpty].prev = aux;
		nodes[aux].next = firstEmpty;

		// actualizez firstEmpty ul 
		firstEmpty = aux;
		nodes[firstEmpty].prev = -1; //vecinul precedent nu exista
		// ( parcursul variabilei firstEmpty se poate vedea ca o deplasare 
		// printr-o stiva, deci firstEmpty nu avea niciodata vecin 
		// in directia 'prev' reprezentand mereu varful stivei) 

		len--;
		if (!len) { head = -1; tail = -1; }
		return elem;

	}

}

/*
worst case = average case = best case = Teta(1) ( o evaluare de expresie booleana )
*/
bool Queue::isEmpty() const {
	//TODO - Implementation

	return head == -1;	// sau len == 0
	//return len == 0;
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

NodeDLLA* Queue::getNodes()
{
	return nodes;
}