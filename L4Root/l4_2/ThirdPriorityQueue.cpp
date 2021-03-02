/* Nu imi dau seama de o chestie: !!!
Eu trebuie sa im construiesc coada in asa fel incat:
1) cand fac `pop`, in varful cozii sa am deja elementul cu a treia 
cea mai mare prioritate
		===SAU===	
2) sa fie bagate in lista 

3) elementul cu a treia cea mai mare prioritate sa tot fie calculat
chiar atunci cand dau `pop` dintre primele 3 elemente ale cozii: asta 
clar nu, deci nu cred ca pot retine un vector pentru primele 3 elemente
ale cozii

*/
#include <iostream>
#include <exception>
#include "ThirdPriorityQueue.h"

using std::cout;

ThirdPriorityQueue::ThirdPriorityQueue(Relation r)
{
	// cap = 100005;
	//cap = 10005;
	cap = 1005;
	len = 0; // voi implementa in indexare de la 1( stiu ca aici scrie 0, dar e de la 1 indexarea;vezi mai jos )
	// iar daca pe parcurs imi dau seama ca trebuia de la 0, voi veni si voi pune len = -1 in loc de 0 + voi verifica
	// peste tot unde trebuie ( adica in remove ) daca len e diferit de -1 nu de 0 !! 

	elems = new Element[cap];
	rel = r;
}

// vad ca nu conteaza indexarea
void ThirdPriorityQueue::resize()
{
	Element *new_elems = new Element[cap * 2 + 1];
//	cout << "trece?";
	for (int i = 1; i <= len; i++)		// indexare de la 1 !!!
		new_elems[i] = elems[i];

// 	cout << "trece?";
	
	cap = cap * 2 + 1;
	Element* aux = elems;
	delete []elems;
	cout << "trece?";
	elems = new_elems;
}

void ThirdPriorityQueue::bubble_up(int p)
{
	int poz = p;
	Element elem = elems[p];
	int parent = p / 2;

	// aici eventual de schimbat ordinea
//	while (poz > 1 && elem > elems[parent]) // efectiv caut pozitia
	while (poz > 1 && rel(elem.second, elems[parent].second))// efectiv caut pozitia
	{
		elems[poz] = elems[parent];
		poz = parent; // ma mut pe noua pozitie where I would insert the element
		parent = poz / 2;
	}
	elems[poz] = elem;
}

void ThirdPriorityQueue::push(TElem e, TPriority p)
{
	if (len == cap - 1) // atunci e cap -1 aici; 
	{ /* chit ca am indexat de la 1, eu rezerv `cap` spatii in constructor!
		// asta inseamna ca pot merge pana la cap - 1; chit ca nu folosesc
		// casuta cu indexul 0 ea tot e rezervata !! */
		std::cout << "incearca el schemosu ceva\n";
		resize();
		std :: cout << " si iese!!!\n";
	}
	elems[len + 1] = Element(e, p);
	len = len + 1;
	bubble_up(len);
}

// la fiecare add,

bool ThirdPriorityQueue::atMostTwo() const
{
	// return true;
	// return len <= 2;
	return (len <= 2);
}

Element ThirdPriorityQueue::top () const
{
	if (atMostTwo()) { exception e; throw e; }
	// altfel: tre sa fac cumva sa am acces
	return Element(-1, -1);
}

void ThirdPriorityQueue::bubble_down(int p)
{
	int poz = p;
	Element elem = elems[p];
	while (poz < len)
	{
		int maxChild = -1;
		if (poz * 2 <= len)	// daca are cel putin un copil, il presupun pe acela drept maxChild ul
			maxChild = poz * 2;

		// aici eventual de schimbat ordinea: aranjamente de 2 luate cate 2 (permutari de 2)
		if (poz * 2 + 1 <= len && rel(elems[2 * poz + 1].second, elems[2 * poz].second)) // daca mai are un copil, actualizez 
		// ( sau nu, in functie de cum e evaluata a doua conditie din if ) maxChild ul; pe scurt, in maxChild determin care
		// e copilul mai mare
			maxChild = poz * 2 + 1;

		// eventual aici de schimbat: permutari de 3
		if (maxChild != -1 && rel(elems[maxChild].second, elem.second))
			// daca intr-adevar, am gasit un copil si este indeplinita
			// relatia dintre copil si parinte, atunci continui sa il cobor pe asta
		{
			elems[poz] = elems[maxChild];
			poz = maxChild;
			/* pe exemplu:
			1. 
			*/
		}
		else
		{
			elems[poz] = elem;
			poz = len + 1;
			// interesant! facem asta ca sa oprim while ul; 
			// DE APLICAT si in alte parti!!

		}
	}
}

Element ThirdPriorityQueue::pop()
{
	 if (len <= 2) { exception e("Empty list!"); throw e; } // nu stiu de ce, daca folosesc varianta comentata mai jos, imi da eroare de heap
	// if (atMostTwo()) { exception e("Queue has less than 3 elements!"); throw e; }
	else
	{
		Element deletedElem = elems[1]; // indexare de la 1
		elems[1] = elems[len]; // pe eexmplu: aici inlocuim radacina initiala 63 cu ultimul element din array: 14
		// de ce facem asta? tocmai pentru ca numai asa vom avea complexitate O(n) in a urca tot subarborele stang 
		// in locul radacinii eliminate si a gasi -din nou- un loc potrivit (conform relatiei) pentru 14 (adica ultimul element)
		len = len - 1;
		bubble_down(1);

		return deletedElem;
	}
}

void ThirdPriorityQueue::toString() const
{
	cout << "=======================\n";
	for (int i = 1; i <= len; i++)
		cout << elems[i].first << " " << elems[i].second << '\n';
	cout << "=======================\n";
	cin.get();
}

ThirdPriorityQueue::~ThirdPriorityQueue()
{
	delete []elems;
}