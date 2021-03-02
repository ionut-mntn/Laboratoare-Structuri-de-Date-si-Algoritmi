#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	//TODO - Representation
    int current;

public:
    //doar de proba metoda asta
    int get_current() { return current;}
	//doar de proba metoda asta
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

