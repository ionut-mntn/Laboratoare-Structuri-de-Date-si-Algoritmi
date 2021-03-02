#include "ExtendedTest.h"
#include "Map.h"
#include "MapIterator.h"

#include <assert.h>
#include <iostream>

using namespace std;

void testIteratorSteps(Map& m) {
	MapIterator mi = m.iterator();
	int count = 0;
	while (mi.valid()) {
		count++;
		mi.next();
	}
	assert(count == m.size());
}

void testCreate() {
	cout << "Test create" << endl;
	cout << "trece???"<<'\n';
	Map m;
	assert(m.size() == 0);
	cout << "TRECE1"<<'\n';
	assert(m.isEmpty() == true);
    cout << "TRECE2"<<'\n';
	for (int i = -10; i < 10; i++) {
		assert(m.search(i) == NULL_TVALUE);
	}
	cout << "TRECE3"<<'\n';
	for (int i = -10; i < 10; i++) {
		assert(m.search(i) == NULL_TVALUE);
	}
	cout << "TRECE4"<<'\n';

	MapIterator it = m.iterator();
	cout << "TRECE_CREARE_ITERATOR"<<'\n';
	assert(it.valid() == false);
	try {
		it.next();
		assert(false);
	}
	catch (exception&) {
		assert(true);
    cout << "TRECE5"<<'\n';
	}
	try {
		it.getCurrent();
		cout<<"trece pe aici"<<'\n';
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	cout << "TRECE6"<<'\n';
	cout<<"iese"<<'\n';
}


void testAdd() {
	cout << "Test add" << endl;
	Map m;
	for (int i = 0; i < 10; i++) {
		assert(m.add(i, i) == NULL_TVALUE);
	}
	cout << "TRECE7"<<'\n';
	cout << "trece8"<<'\n';
	assert(m.isEmpty() == false);
	cout << "TRECE9"<<'\n';
	assert(m.size() == 10);
	cout << "TRECE10"<<'\n';
	for (int i = -10; i < 0; i++) {
		assert(m.add(i, i) == NULL_TVALUE);
	}
	cout << "TRECE11"<<'\n';
	for (int i = 0; i < 10; i++) {
		assert(m.add(i, i) == i);
	}
	cout << "TRECE12"<<'\n';
	for (int i = 10; i < 20; i++) {
		assert(m.add(i, i) == NULL_TVALUE);
	}
	cout << "TRECE13"<<'\n';
	assert(m.isEmpty() == false);
	cout << "TRECE14"<<'\n';
	assert(m.size() == 30);
	cout << "TRECE14*"<<'\n';
	int l = m.size();
	for (int i = -100; i < 100; i++) {
		m.add(i, i);
	}
	cout << "trece15"<<'\n';
	assert(m.isEmpty() == false);
	cout << "TRECE16"<<'\n';
	assert(m.size() == 200);
	cout << "TRECE17"<<'\n';
	for (int i = -200; i < 200; i++) {
		if (i < -100) {
			assert(m.search(i) == NULL_TVALUE);
		}
		else if (i < 0) {
			assert(m.search(i) == i);
		}
		else if (i < 100) {
			assert(m.search(i) == i);
		}
		else {
			assert(m.search(i) == NULL_TVALUE);
		}
	}
	cout << "TRECE18"<<'\n';
	for (int i = 10000; i > -10000; i--) {
		m.add(i, i);
	}
	cout << "TRECE19"<<'\n';
	testIteratorSteps(m);
	cout << "TRECE20"<<'\n';
	assert(m.size() == 20000);
    cout << "TRECE21"<<'\n';
}


void testRemove() {
	cout << "Test remove" << endl;
	Map m;

	for (int i = -100; i < 100; i++) {
		assert(m.remove(i) == NULL_TVALUE);
	}
	assert(m.size() == 0);
	for (int i = -100; i < 100; i = i + 2) {
		assert(m.add(i, i) == NULL_TVALUE);
	}
	for (int i = -100; i < 100; i++) {
		if (i % 2 == 0) {
			assert(m.remove(i) == i);
		}
		else {
			assert(m.remove(i) == NULL_TVALUE);
		}
	}
	assert(m.size() == 0);

	for (int i = -100; i <= 100; i = i + 2) {
		assert(m.add(i, i) == NULL_TVALUE);
	}
	testIteratorSteps(m);
	for (int i = 100; i > -100; i--) {
		if (i % 2 == 0) {
			assert(m.remove(i) == i);
		}
		else {
			assert(m.remove(i) == NULL_TVALUE);
		}
		testIteratorSteps(m);
	}

	assert(m.size() == 1);

	m.remove(-100);
	assert(m.size() == 0);

	for (int i = -100; i < 100; i++) {
		assert(m.add(i, 0) == NULL_TVALUE);
		assert(m.add(i, 1) == 0);
		assert(m.add(i, 2) == 1);
		assert(m.add(i, 3) == 2);
		assert(m.add(i, 4) == 3);
	}
	assert(m.size() == 200);
	for (int i = -200; i < 200; i++) {
		if (i < -100 || i >= 100) {
			assert(m.remove(i) == NULL_TVALUE);
		}
		else {
			assert(m.remove(i) == 4);
			assert(m.remove(i) == NULL_TVALUE);
		}
	}
	assert(m.size() == 0);

}



void testIterator() {
	cout << "Test iterator" << endl;
	Map m;
	MapIterator it = m.iterator();
	assert(it.valid() == false);

	for (int i = 0; i < 100; i++) {
		m.add(33, 33);
	}
	MapIterator it2 = m.iterator();
	assert(it2.valid() == true);
	TElem el = it2.getCurrent();
	assert(el.first == 33);
	assert(el.second == 33);
	it2.next();
	assert(it2.valid() == false);
	try {
		it2.next();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		it2.getCurrent();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}

	it2.first();
	assert(it2.valid() == true);

	Map m2;
	for (int i = -100; i < 100; i++) {
		assert(m2.add(i, i) == NULL_TVALUE);
		assert(m2.add(i, i) == i);
		assert(m2.add(i, i) == i);
	}
	MapIterator it3 = m2.iterator();
	assert(it3.valid() == true);
	for (int i = 0; i < 200; i++) {
		it3.next();
	}
	assert(it3.valid() == false);
	it3.first();
	assert(it3.valid() == true);

	Map m3;
	for (int i = 0; i < 200; i = i + 4) {
		m3.add(i, i);
	}

	MapIterator it4 = m3.iterator();
	assert(it4.valid() == true);
	int count = 0;
	while (it4.valid()) {
		TElem e = it4.getCurrent();
		assert(e.first % 4 == 0);
		it4.next();
		count++;
	}
	assert(count == 50);

}



void testQuantity() {
	Map m;
	cout << "Test quantity" << endl;
	for (int j = 0; j < 30000; j = j + 1) {
		assert(m.add(j, j) == NULL_TVALUE);
	}
	for (int i = 10; i >= 1; i--) {
		for (int j = 0; j < 30000; j = j + i) {
			assert(m.add(j, j) == j);
		}
	}
	assert(m.size() == 30000);
	MapIterator it = m.iterator();
	assert(it.valid() == true);
	for (int i = 0; i < m.size(); i++) {
		it.next();
	}
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		assert(m.search(e.first) == e.first);
		it.next();
	}
	assert(it.valid() == false);

	for (int j = 30000 - 1; j >= 0; j--) {
		assert(m.remove(j) == j);
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 40000; j >= -4000; j--) {
			assert(m.remove(j) == NULL_TVALUE);
		}
	}
	assert(m.size() == 0);
}

void testAllExtended() {
	testCreate();
	testAdd();
	testRemove();
	testIterator();
	testQuantity();
}




