#include <iostream>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;




int main() {
	cout << "Test Reverse\n";
	testReverse();
	cout << "Short Test\n";
	testAll();
	cout << "Extended Test\n";
	testAllExtended();

	cout << "End" << endl;
	system("pause");

}
