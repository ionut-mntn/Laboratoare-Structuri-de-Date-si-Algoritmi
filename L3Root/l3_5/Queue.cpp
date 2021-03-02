#include <iostream>
#include <exception>
#include "Queue.h"
using namespace std;

void Queue::toString() const 
{
	int aux = head;
	do
	{
		/*
		cout << "nodes[" << aux << "].prev = " << nodes[aux].prev << '\n';
		cout << "nodes[" << aux << "].data = " << nodes[aux].data << '\n';
		cout << "nodes[" << aux << "].next = " << nodes[aux].next << '\n';
		*/
		cin.get();
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

	/*
	for (int i = 0; i < cap; i++)
		cout << nodes[i].prev << " " << nodes[i].next << '\n';
	*/

	firstEmpty = 0; // !! 0, nu -1 aici!!
	//cout << "Bun constructor\n";
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

	// adaug elementul in lista
	nodes[firstEmpty].data = elem;

	// TOATE INCURCATURILE ASTEA E POSIBIL SA FIE PENTRU CA NU FOLOSESTI
	// VARIABILE AUXILIARE ( CARE DE ALTFEL NU TE COSTA NIMIC!!!)


	// construiesc "legaturile" intre elementul tocmai introdus si ultimul
	// element din container (adica legaturile dintre fosta si noua coada)
	// daca ultimul element exista
	if (tail == -1)			// sau head == -1 sau len == -1
	// daca am adaugat chiar primul element din coada, actualizez head ul
	{
		// cout << "primul" << '\n';
		head = firstEmpty;
//		tail = firstEmpty;
//		firstEmpty = nodes[firstEmpty].next;
//		nodes[tail].next = -1;
	}
	else
	// altfel, inseamna ca exista deja un "ultim element", deci:
	{
		// construiesc legaturi intre fosta coada si actuala coada
		// (elementul pe care tocmai l-am inserat)
		nodes[tail].next = firstEmpty;
		nodes[firstEmpty].prev = tail;

	}

	// actualizez coada
	tail = firstEmpty;
	
	// actualizez firstEmpty
	firstEmpty = nodes[firstEmpty].next;

	// adaugan mereu in coada, inseamna ca nu vor exista (la acest pas) vecini 
	// urmatori, deci setez next ul cozii la -1
	nodes[tail].next = -1;

	len++;

	/*
	cout << "nodes[" << tail << "].prev = " << nodes[tail].prev << '\n';
	cout << "nodes[" << tail << "].data = " << nodes[tail].data << '\n';
	cout << "nodes[" << tail << "].next = " << nodes[tail].next << '\n';
	*/
}

/*
worst case = average case = best case = Teta(1)
*/
TElem Queue::top() const {
	//TODO - Implementation

	if (isEmpty()) {
		//cout << "EXCEPTIE:::::::" << '\n';
		exception e; throw e;
	}

	//toString(); // !! atentie!! functia asta
	// top este `const`! iar toString nu este const!
	// implicit nu am garantia ca toString nu va modifica 
	// starea obiectului! => trebuie sa fac si toString `const`
	
	/*
	cout << head << '\n';
	cout << "head="<<head << " " << "tail="<<tail << '\n';
	*/
	return nodes[head].data;

	//return NULL_TELEM;
}
/*
worst case = average case = best case = Teta(1) ( doar assignment uri, nimic special; nicio iteratie, nimic )
*/
TElem Queue::pop() {
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
		TElem elem = nodes[head].data;		// retin intr o variabila auxiliara ce
		// va trebui sa returnez

		// actualizez head ul
		head = nodes[head].next;
		nodes[head].prev = -1; // head ul nu are vecini precedenti
		/*
		(observatie: De ce am modificat `nodes[head].prev`, dar nu m-am atins
		de indecsii catre vecini ai fostului head? Pentru ca atat valoaread
		de la indexul fostului head, cat si inedcsii catre vecinii sai vor
		fi modificate la un eventual `push`
		*/

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