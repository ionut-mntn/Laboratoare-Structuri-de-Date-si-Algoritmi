#include <iostream>
#include "SortedIndexedList.h"
#include "ListIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <vector>


bool relation2(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

bool ascendent(TComp c1, TComp c2) {
	if (c1 <= c2) {
		return true;
	}
	else {
		return false;
	}
}

std::vector<int> random1(int cMin, int cMax, int s, int m) {
	std::vector<int> v;
	for (int c = cMin; c <= cMax; c++) {
		if (c % s != 0) {
			v.push_back(c);
			if (c % m == 0) {
				for (int j = 0; j < c / m; j++) {
					v.push_back(c);
				}
			}
		}
	}
	int n = v.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		std::swap(v[i], v[j]);
	}
	return v;
}


int populate1(SortedIndexedList& list, int cMin, int cMax, int s, int m) {
	std::vector<int> v =random1(cMin, cMax, s, m);
	int n = v.size();
	for (int i = 0; i < n; i++) {
		std::cout << v[i] << ' ';
		list.add(v[i]);

	}
	return n;
}

int main(){
    testAll();



	
	/*SortedIndexedList list = SortedIndexedList(ascendent);
	int vMin = 10;
	int vMax = 30;
	int s = 5;
	int m = 3;
	populate1(list, vMin, vMax, s, m);
	ListIterator it = list.iterator();
	it.first();
	std::cout << "cout it"<<'\n';
	
	for (int i = 0; i < list.lungime;i++) {
		std::cout << it.getCurrent()<< ' ';
		it.next();
		std::cout << it.getCurrent() << '\n';
	
	}*/



	

	

	SortedIndexedList s = SortedIndexedList(ascendent);
	s.add(17);
	s.add(17);
	
	s.add(16);
	s.add(24);
	s.add(24);
	s.add(26);
	s.add(23);
	s.add(23);
	s.add(12);

	ListIterator it = s.iterator();

	it.first();

	for (int i = 0; i < s.lungime; i++) {
		std::cout<<it.getCurrent()<<' ';
		it.next();
	}


	
	


	//std::cout <<"get element: "<< s.getElement(0);



    // testAllExtended();



	/*
	SortedIndexedList s = SortedIndexedList(relation2);
	s.add(15);
	std::cout << "Primul nod: wert= " << s.nod->wert<<" next address= "<<s.nod->next<<std::endl;

	s.add(17);
	s.add(16);
	s.add(19);
	s.add(22);
	std::cout << s.nod->next;
	
	std::cout << "Primul nod: wert= " << s.nod->wert << " next address= " << s.nod->next<<" Next Wert: " << s.nod->next->wert<<std::endl;
	std::cout << s.size()<<std::endl;
	*/
    std::cout<<"Finished IL Tests!"<<std::endl;
	
	testAllExtended();


	system("pause");
}