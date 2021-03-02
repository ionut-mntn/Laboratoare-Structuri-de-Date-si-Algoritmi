#include <iostream>
#include "SortedSetIterator.h"
#include <exception>

using namespace std;

/*
worst case: O(1)
best case: Omega(1)
average case: Teta(1)
*/
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m), current(0)
{
	//TODO - Implementation

    // current = -1
    //current = 0 // n am mai facut aici, am facut in lista de initializare
}

/*
worst case: O(1)
best case: Omega(1)
average case: Teta(1)
*/
void SortedSetIterator::first() {
	//TODO - Implementation

    if(!multime.len) throw "eroare: set-ul nu contine niciun element";
    current = 0;
}

/*
worst case: O(1)
best case: Omega(1)
average case: Teta(1)
*/
void SortedSetIterator::next() {
	//TODO - Implementation
    if (valid()) { current++; return ; }
    else {exception e; throw e;}
}

/*
worst case: O(1)
best case: Omega(1)
average case: Teta(1)
*/
TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation

    if ( valid() ) return multime.elems[current];
	else {exception f; throw f;}
}

/*
worst case: O(1)
best case: Omega(1)
average case: Teta(1)
*/
bool SortedSetIterator::valid() const {
	//TODO - Implementation
	if (0 <= current && current < multime.len)
        return true;
	return false;
}
