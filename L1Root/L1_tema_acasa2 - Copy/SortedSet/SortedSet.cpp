#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

// worst case: O(1)
// best case: Omega(1)
// average case: Teta(1)
// explicatie: sunt doar atribuiri; nu intervine problema complexitatii, operatiile fiind executate (relativ) instantaneu
SortedSet::SortedSet(Relation r) {
	//TODO - Implementation

	len = 0;
	cap = 105;
	elems = new TComp[cap];
	rel = r;
}

/*
NOTA: aici, am considerat ca new[] si delete[] au complexitatea O(n) ( aceasta depinde de complexitatea constructorului unui element de tip TComp )
worst case: O(n) ( nu se va gasi elementul, container ul va fi full, deci se va face realocare de memorie, iar elementul va fi inserat pe prima pozitie
in container, deci: (log n + 1)+ 1 + (n + n + n) + n  = log n + 4n + 1 = O(n) )
best case: Omega(1) ( se va gasi elementul din prima incercare, pe pozitia din mijloc a sirului )
average case: O(n)
*/
bool SortedSet::add(TComp elem) {
	//TODO - Implementation

    if(!search(elem))
    {
        if(len == cap)
        {
            cap = cap * 2 + 1;
            TComp *newElems = new TComp[cap];
            for(int i = 0; i < len; i++)
                newElems[i] = elems[i];
            delete []elems;
            elems = newElems;
        }

        len ++;
        int i = len - 1;
        while(i > 0 && (*rel)(elem, elems[i - 1]))
        {
            elems[i] = elems[i - 1];
        i --;
        }
        elems[i] = elem;
      return true;
    }
	return false;
}

/*
NOTA: aici, am considerat ca new[] si delete[] au complexitatea O(n) ( aceasta depinde de complexitatea constructorului unui element de tip TComp )
worst case: O(n) ( se va gasi elementul, container ul va fi doar 1/4 plin, deci se va face realocare de memorie, iar elementul va trebui eleminiat de pe
prima pozitie din sir, deci: (log n + 1) + 1 + (n + n + n) + n = O(n) )
best case: Omega(log n) ( nu se va gasi elementul, deci se va returna false )
average case: O()
*/
bool SortedSet::remove(TComp elem) {
	//TODO - Implementation

    if (search(elem))
    {
        if(len == cap / 4)
        {
            cap = cap / 2;
            TComp *newElems = new TComp[cap];
            for(int i = 0; i < len; i++)
                newElems[i] = elems[i];
            delete []elems;
            elems = newElems;
        }

        int i;
        for(i = 0; i < len - 1 && elems[i] != elem; i++) {;}
        for( ; i < len - 1; i++)
            elems[i] = elems[i + 1];
        len --; // actualizez lungimea set ului

        return true;
    }
	return false;
}

/*
worst case: O(log n)
best case: Omega(1) ( in cazul in care elementul cautat se afla chiar la mijlocul container ului in care se face cautarea )
average case: O(log n)
explicatie: la fiecare pas in care nu se gaseste pe pozitia 'mij' elementul cautat, se va injumatati domeniul de cautare; astfel, prin impartiri succesive
la 2, se obtine complexitatea
*/
bool SortedSet::search(TComp elem) const {
	//TODO - Implementation
    int st = 0, dr = len - 1;
    int mij;
    while(st <= dr)
    {
        mij = (st + dr) / 2;
        //if (*(elems + mij) == elem) return true;
        if (elems[mij] == elem) return true;
        //else if ( (*r)(elems[mij], elem) ) st = mij + 1;
        else if ( (*rel)(elems[mij], elem) ) st = mij + 1;
        else dr = mij -1;
    }
    return false;
	//return true;
}

/*
worst case: O(1)
best case: Omega()
average case: Teta(1)
/se va accesa valoarea de la adresa de memorie 'len' si se va returna aceasta valoare
*/
int SortedSet::size() const {
	//TODO - Implementation

	return len;

	//return 0;
}

/*
worst case: O(1)
best case: Omega(1)
average case: Teta(1)
explicatie: se va efectua o singura verificare
*/
bool SortedSet::isEmpty() const {
	//TODO - Implementation

	return (len == 0);

	//return false;
}

/*
worst case: O(1)
best case: Omega(1)
average case: Teta(1)
explicatie: se va apela constructorul SortedSetIterator, care la randul sau va apela constructorul SortedSet( despre care stim deja ca are complexitatea ca
timp: Teta(1) ), iar pe langa acesta se va mai face o atribuire
*/
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

/*
worst case: ? ( am stabilit la inceput ca elementele din elems sunt de tipul generic TComp; astfel, in cel mai rau caz, pentru fiecare dintre obiectele
din elems va trebui apelat destructorul, care are complexitatea ca timp: ? - nu cunoastem complexitatea ca timp pentru destructorul unui obiect de tip Tcomp,
pentru ca nu cunoastem implementarea clasei care defineste un obiect de tip TComp; daca am considera TComp ca fiind int, atunci am vorbi despre Teta(1) )
voi presupune ca intra in discutie cazul despre care stiu complexitatea ca timp a creeri unui obiect TComp ( Teta(1) ), deci worst case: O(n)
best case: Omega(1) ( daca elementele din elems sunt de un tip de date care nu necesita destructor )
best case: Teta(1) ( elementele din container sunt de un tip de date care nu necesita destructori: de exemplu
explicatie: se va dealoca memoria rezervata celor n variabile de tipul de date TComp ( in cel mai rau caz, dealocarea memoriei alocate fiecaruie va necesita
apelarea destructorului fiecarui obiect de tip TComp )
*/
SortedSet::~SortedSet() {
	//TODO - Implementation

	delete []elems;
}
