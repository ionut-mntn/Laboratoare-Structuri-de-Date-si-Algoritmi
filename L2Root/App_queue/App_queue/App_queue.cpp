#include "Queue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>

using namespace std;

/*
struct A {
	int x, y;
};

struct B {
	int x, y;
}ob2,ob3;
*/

typedef struct C {
	int x, y;
}nume_tip;

int main() {
	int a = 2;
	int* p = &a;
	cout << p;
	//	testAll();
//	testAllExtended();

	cout << "Test end" << endl;
	/*
	A obiect;
	obiect.x = 1;
	obiect.y = 2;

	ob2.x = 2;
	ob2.x = 3;
	ob3.x = 2;
	ob3.x = 3;

	C ob4;
	nume_tip ob5;
	ob4.x = 1;
	ob4.y = 2;
	ob5.x = 1;
	ob5.y = 1;
	*/
	return 0;
}