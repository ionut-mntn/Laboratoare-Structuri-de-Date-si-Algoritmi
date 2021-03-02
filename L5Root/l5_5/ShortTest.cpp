#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"

#include <iostream>
using std::cout;
using std::cin;

void testAll() { //call each function to see if it is implemented
	Map m;
	// cout << "intra\n";
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
//	m.apel_display();
	assert(m.size() == 5);
	assert(m.search(10) == 10);
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);
	// m.apel_display();
	// cout << "intra2\n";

	TElem e;
	MapIterator id = m.iterator();
	id.first();
	// cout << "intra3\n";
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		// cout << "intra 4\n";
		
//		cin.get();
		//id.getMap().apel_display();
//		cin.get();
		
		e = id.getCurrent();
		//cout << "curent = " << e.first << " " << e.second << '\n';
		s1 += e.first;
		s2 += e.second;
		id.next();
	//	cout << "intra 5\n";
	}
//	cout << "iese\n";
	cout << s1 << '\n';
	assert(s1 == 19);
	assert(s2 == 19);
	// cout << "intra6\n";
}


