
	#include "ShortTest.h"
	#include "Queue.h"
	#include <assert.h>
	#include<iostream>
	using std::cout;
	void testAll() {
		Queue q;
		assert(q.isEmpty() == true);
		q.push(5);
		//cout << "So far so good" << '\n';
		//NodeDLLA* aux=q.getNodes();
		//cout << aux[0].data << '\n';
		q.push(1);
		//aux = q.getNodes();
		//cout << aux[0].data << '\n';
		q.push(10);
		//aux = q.getNodes();
		//cout << aux[0].data << '\n';

		assert(q.isEmpty() == false);
		assert(q.top() == 5);
		assert(q.pop() == 5);
		assert(q.top() == 1);
		assert(q.pop() == 1);
		assert(q.top() == 10);
		assert(q.pop() == 10);
		assert(q.isEmpty() == true);
	}
