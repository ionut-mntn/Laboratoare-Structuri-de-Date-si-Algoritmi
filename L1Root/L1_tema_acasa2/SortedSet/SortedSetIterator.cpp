#include <iostream>
#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m), current(0)
{
	//TODO - Implementation

    ///current = -1;

}


void SortedSetIterator::first() {
	//TODO - Implementation

    if(!multime.len) throw "eroare: set-ul nu contine niciun element";
    current = 0;
}


void SortedSetIterator::next() {
	//TODO - Implementation
    if (valid()) { current++; return ; }
    else {throw std::invalid_argument("a");}
}


TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation

    if ( valid() ) return multime.elems[current];
	else {throw std::invalid_argument("b");}
}

bool SortedSetIterator::valid() const {
	//TODO - Implementation
    ///std::cout << "aici: "<<current << '\n';
    ///std::cout << (0 < current && current < multime.len);
	return (0 <= current && current < multime.len);

//	return false;
}

