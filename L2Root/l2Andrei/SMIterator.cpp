#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    iter = map.head;
	//TODO - Implementation
}

void SMIterator::first(){
    iter = map.head;
	//TODO - Implementation
}

void SMIterator::next(){
    if(valid())
        iter = iter->next;
	//TODO - Implementation
}

void SMIterator::prev(){
    if(valid())
        iter = iter->prev;
}

bool SMIterator::valid() const{
    if(iter == nullptr) return false;
	return true;
	//TODO - Implementation
}

TElem SMIterator::getCurrent() const{
	//TODO - Implementation
	if(valid())
        return TElem(iter->key,iter->value);
	return NULL_TPAIR;
}


