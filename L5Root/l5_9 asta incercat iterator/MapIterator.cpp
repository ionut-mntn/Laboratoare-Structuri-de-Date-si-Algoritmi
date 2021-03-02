#include "Map.h"
#include "MapIterator.h"
#include <iostream>
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation
	parcurs_ht1 = false;
	poz = -1; // nu va fi la initializare -1 pentru ca se schimba in `first` !
	//first();
}

void MapIterator::find_subcontainer_next(const TElem *ht)
{
	poz++;
	while (poz < map.m && ht[poz] == NULL_TELEM)
	{
		poz++;
//		cout << poz << '\n';
	}
}

void MapIterator::find_next()
{
//	cout << "block\n";
	if (!parcurs_ht1)	// daca inca nu a fost parcurs `ht1`, atunci:
	{
		find_subcontainer_next(map.ht1);	// continua sa cauti in el
		if (valid()) 
		{ 
			cout << "poz = " << poz << '\n'; cout << "map.ht1[" << poz << "]=" << map.ht1[poz].first << " " << map.ht1[poz].second << '\n'; 
			return; 
		}// if valid() ??? // daca nu a gasit in ht1 element
	//	cout << " nu e valid\n";
		parcurs_ht1 = true; // daca nu e valid, sigur a trecut de m, pentru ca negativ nu are cum sa fie
		// avand in vedere faptul ca eu ii dau -1 valoarea primordiala si incepe cu `poz` ++
		poz = -1;
	}
//	cout << "block\n";
	find_subcontainer_next(map.ht2);
	// if (valid()) return;
}


void MapIterator::first() 
{
	//TODO - Implementation
	find_next();
	cout << "s a facut first ul!\n";
}


void MapIterator::next() 
{
	//TODO - Implementation
	//if(valid()) find_next();
	find_next();
//	if (valid()) return;
	//exception e; throw e;
}


TElem MapIterator::getCurrent() 
{
	//TODO - Implementation
	if (valid())
	{
		if (!parcurs_ht1) return map.ht1[poz];
		return map.ht2[poz];
	}
	cout << "aruncaaa\n";
	exception e; throw e;
	//	return NULL_TELEM;
}


bool MapIterator::valid() const {
	//TODO - Implementation
	
	return 0 <= poz && poz < map.m;

		//	return false;
}


