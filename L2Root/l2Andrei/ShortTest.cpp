#include <assert.h>
#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
#include <iostream>

using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
    std :: cout << " intra " << '\n';
	SortedMap sm(relatie1);
    cout << " trece1 " << '\n';
	assert(sm.size() == 0);
    cout << " trece2 " << '\n';
    assert(sm.isEmpty());
    cout << " trece3 " << '\n';
    sm.add(1,2);
    cout << " trece4 " << '\n';
    assert(sm.size() == 1);
    cout << " trece5 " << '\n';
    assert(!sm.isEmpty());
    cout << " trece6 " << '\n';
    assert(sm.search(1)!=NULL_TVALUE);
    cout << " trece7 " << '\n';
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    cout << " trece1 " << '\n';
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());
}

