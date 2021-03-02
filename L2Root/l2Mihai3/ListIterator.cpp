#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
	//Complexitate best case = worst case = avg case = O(1)
	i = 0;
}

void ListIterator::first() {
	//TODO - Implementation
		//Complexitate best case = worst case = avg case = O(1)

	i = 0;
}

void ListIterator::next() {
	//TODO - Implementation
		//Complexitate best case = worst case = avg case = O(1)

	if (valid()) {
		//cout << " a incrementat ";
		i++;
	}

	else {
		std::cout << "exceptie";
		exception e;
		throw e;
	}
}

bool ListIterator::valid() const {
	//TODO - Implementation
		//Complexitate best case = worst case = avg case = O(1)


	return (0 <= i && i < list.lungime);
}

TComp ListIterator::getCurrent() const {
	//TODO - Implementation
		//Complexitate
	//best case: O(1)
	//worst case: O(n)
	//avg case: O(n)
	if (valid()) {
		SortedIndexedList l = list;
		//cout << l.nod;
		
		int ct = 0;
		while (ct < i) {
			//cout << l.nod << ' ' << l.nod->next<<std::endl;
			l.nod = l.nod->next;
			ct++;

		}
		return l.nod->wert;
	}



	return NULL_TCOMP;
}


