/*
	#include "ShortTest.h"
	#include "Queue.h"
	#include <assert.h>
	#include<iostream>
	using std::cout;
	void testAll() {
		Queue q;
		assert(q.isEmpty() == true);
		q.push(5);
		cout << q.getTail() << '\n';
		q.push(1);
		cout << q.getTail() << '\n';
		q.push(10);
		cout << q.getTail() << '\n';
		assert(q.isEmpty() == false);
		assert(q.top() == 5);
		assert(q.pop() == 5);
		cout << q.getHead() << '\n';
		assert(q.top() == 1);
		assert(q.pop() == 1);
		cout << q.getHead() << '\n';
		assert(q.top() == 10);
		assert(q.pop() == 10);
		cout << q.getHead() << '\n';
		assert(q.isEmpty() == true);
	}
*/