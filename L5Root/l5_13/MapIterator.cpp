#include "Map.h"
#include "MapIterator.h"
#include <iostream>
#include <exception>
using namespace std;

/*
Depinde de complexitatea lui `first`. Astfel:
worst case = O(2m) = O(m) - elementul nu exista / se afla pe ultima pozitie din tabela2
average case = O(m)
best case = Omega(1), deci chiar Theta(1) - elementul se afla pe prima pozitie in prima tabela
*/
MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation

	first(); /* ma pozitionez pe prima pozitie - relevanta - din container ( "relevant" = pozitie care nu este un spatiu liber, ci, una care contine date - in cazul nostru spatiul liber este
			 reprezentat de  pozitii ocupate de elemente `NULL_TELEM` */
}

/*
worst case = O(m), deci Theta(m) - elementul nu se afla / este chiar pe ultima pozitie in tabela respectiva
average case = O(m)
best case = Omega(1), deci Theta(1) - elementul se afla pe pozitia invecinata
(unde m = dimensiunea unuia dintre subcontainer)
*/
void MapIterator::find_subcontainer_next(const TElem *ht)
{
	poz++;		// incep cautarea de la urmatorul element inainte ( adica inspre pozitiile de index mai mare ale subcontainer-ului )
	while (poz < map.m && ht[poz] == NULL_TELEM) poz++; // cat timp nu am iesit din tabela curenta si dau de spatii libere, incrementez pozitia
}

/*
Depinde de complexitatea lui `find_subcontainer_next`. Astfel:
worst case = O(2m) = O(m); - elementul nu exista / se afla pe ultima pozitie din tabela2
average case = O(2m) = O(m)
best case = Omega(1), deci chiar Theta(1) - elementul e pe prima pozitie din tabela1
(unde `m` = capacitatea unei tabele)
*/
void MapIterator::find_next()
{
	if (!parcurs_ht1)	// daca inca nu a fost parcurs `ht1`, atunci:
	{
		find_subcontainer_next(map.ht1);	// continua sa cauti in el
		if (valid()) return;	// daca am gasit un element, parasesc functia
								// altfel:
		parcurs_ht1 = true;		// sigur s-a parcurs prima tabela, deci marchez `parcurs_ht1` drept adevarat
		poz = -1;				// si resetez `poz`
	}
	find_subcontainer_next(map.ht2);			/* pentru a continua cautarea urmatorului element existent in tabela 2 (Atentie! cand se va reapela 
	`find_next` nu se va mai intra pe ramura de `if`, ci direct pe acest apel)  - asta daca nu se apeleaza `first` pana a se apela din nou `find_next` */
}

/*
worst case = O(2m) = O(m) - elementul nu exista / se afla pe ultima pozitie din tabela2
average case = O(m)
best case = Omega(1), deci chiar Theta(1) - elementul se afla pe prima pozitie in prima tabela
*/
void MapIterator::first() // indiferent pe ce pozitie ar fi iteratorul la pasul curent, `first` trebuie sa plaseze iteratorul pe primul element din container!
{
	//TODO - Implementation
	
	parcurs_ht1 = false; 
	poz = -1;
	/* de fiecare data cand vreau sa ajung iar pe primul element din container, trebuie sa: setez pozitia la -1 si sa marchez `parcurs_ht1` ca `false`,
		pentru ca altfel, metoda `find_next` - apelata mai jos - imi va gasi urmatorul element din container, ceea ce nu vreau sa se intample cand apelez `first` !!
		Eu vreau sa ma pozitionez cu iteratorul pe primul element existent in container! Deci, ATENTIE! `first` reseteaza iteratorul! */

	find_next();
}


/*
Depinde de complexitatea lui `find_next`. Astfel:
worst case = O(2m) = O(m); - elementul nu exista / se afla pe ultima pozitie din tabela2
average case = O(2m) = O(m)
best case = Omega(1), deci chiar Theta(1) - elementul e pe prima pozitie din tabela1
(unde `m` = capacitatea unei tabele)
*/
void MapIterator::next()
{
	//TODO - Implementation

	if (valid()) { find_next(); return; } // daca sunt pe o pozitie valida, continui sa caut elemente in container
	exception e; throw e;	// altfel, arunc exceptie
}

/* worst case = average case = best case = Theta(1). (`valid` are timp constant, iar in rest mai apare o singura verificare )*/
TElem MapIterator::getCurrent() 
{
	//TODO - Implementation

	if (valid())	// daca sunt pe o pozitie valida
	{
		if (!parcurs_ht1) return map.ht1[poz];	// daca inca nu am parcurs prima tabela, atunci inseamna ca sunt pe o pozitie valida in prima tabela
		return map.ht2[poz];	// altfel, inseamna ca sunt pe o pozitie valida in a doua tabela 
	}
	exception e; throw e; // daca nu sunt pe o pozitie valida, arunc ecxceptie

	//	return NULL_TELEM;
}

/*
worst case = average case = best case = Theta(1) - timp constant pentru ca sunt doar 2 verificari de facut 
*/
bool MapIterator::valid() const {
	//TODO - Implementation
	
	return 0 <= poz && poz < map.m;

	//	return false;
}



