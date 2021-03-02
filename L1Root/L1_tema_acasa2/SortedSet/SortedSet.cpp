#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
	len = 0;
	cap = 105;
	elems = new TComp[cap];
	//rel = &r;
	rel = r;
}


bool SortedSet::add(TComp elem) {
	//TODO - Implementation

    if(!search(elem))
    {
        if(len == cap)
        {
            ///std::cout<<"s-a marit armata"<<'\n';
            ///std :: cin.get();

            cap = cap * 2 + 1; // aici de avut grija;
            // poate vine cineva si imi modifica implementarea
            // si: in loc de capacitatea initiala 0 ii da 1

            std :: cout << cap <<'\n';
            std :: cin.get();

            TComp *newElems = new TComp[cap];
            for(int i = 0; i < len; i++) // nu conteaza ca am dat tot i aici, il suprascrie temporar pe stiva
                newElems[i] = elems[i];
            delete []elems; // daca da eroare aici, voi face
            // cum am explicat mai jos
            elems = newElems;

            // ca sa dealoc spatiul la care pointa initial elems,
            // as putea sa: iau un pointer la elems, dealoc la ce pointeaza
            // elems si schimb valoarea la care pointeaza elems; cum fac asta ultima ?
            //dereferentiez pointer ul spre elems ( astfel accesand valoarea spre care
            // pointeaza elems si o suprascriu )
        }

        len ++;
//        int i = len - 1; // daca nu am fi alterat lungimea set ului mai sus, pozitia de start ar fi fost i - 1. astfel, vom incepe sa cautam unde trebuie inserat
        // elementul elem de la len - 2
//        for( ; i > 0 && (*rel)(elems[i - 1], elem); i--)
//            elems[i] =
        ///int i = len - 2; // nu mai face prostii de astea cu -2
        // pe cazuri de baza -triviale= ( primul element adaugat
        // in lista ) poate nu merg
        int i = len - 1;
        while(i > 0 && (*rel)(elem, elems[i - 1]))
        {       ///! MARE GRESEALA DE LOGICA AICI; DIN BUCLA REPE-
            ///TITIVA TREBUIE SA IES CAND ORI CAND AM DAT DE O NECON-
            ///CORDANTA IN MONOTONIA SIRULUI ( CONSIDERAT FIIND SI ELEM
            ///AICI, PE POZITIA CURENTA )
            ////////std::cout<<"la zece intra"<<'\n';
            //if( (*rel)(elem, elems[i - 1]) )
            ///if( !(*rel)(elems[i], elem) ) // ori negam relatia ( pentru ca mergem de la coada la cap ), ori inversam argumentele pasate functiei la care
                // pointeaza rel
               /// {
                    elems[i] = elems[i - 1];
                //////    std::cout << " s a mutat "<< elems[i - 1] << " pe pozitia " << i <<'\n';
                ///}
        i --;
        }
        elems[i] = elem;
        /*
        std::cout << " s a adaugat " << elem << " pe pozitia " << i <<'\n';
        for(int i = 0; i < len ;i++) std::cout << elems[i] << " ";
        std::cout <<'\n';
        */
        /*
        for(i = 0; i < len && (*rel)(elems[i], elem); i++) {;}
        // la acest pas voi fi cu 'i' pe pozitia pe care trebuie adaugat
        for( ; i < len - 1; i++)
            elems[i] = elems[i + 1];
        */

      return true;
    }
	return false;
}


bool SortedSet::remove(TComp elem) {
	//TODO - Implementation

    if (search(elem))
    {
        int i;
        for(i = 0; i < len - 1 && elems[i] != elem; i++) {;}
        // la acest pas voi fi cu 'i' pe pozitia care trebuie suprascrisa
        for( ; i < len - 1; i++)
            elems[i] = elems[i + 1];                                                        ///de corectat aici!!!
        len --; // actualizez lungimea set ului

//        if (len <= cap / 4) cap /=2 ; // nu incerc eficientizari, fac
// cum scrie in curs
/*
        if(len == cap / 2)
        {
            cap = cap / 2 + 1; // am pus +1 ca sa nu se ajunga
            //la un container de capacitate zero( analog la
            // rationamentul de mai sus, din functia de ad )
            TComp *newElems = new TComp[cap];
            for(int i = 0; i < len; i++)
                newElems[i] = elems[i];
                // o sa se suprascrie i pe stiva temporar
            delete []elems;
            elems = newElems;
        }
*/
        return true;
    }
	return false;
}


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


int SortedSet::size() const {
	//TODO - Implementation

	return len;

	//return 0;
}



bool SortedSet::isEmpty() const {
	//TODO - Implementation

	return (len == 0);

	//return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	//TODO - Implementation

	delete []elems;
}
