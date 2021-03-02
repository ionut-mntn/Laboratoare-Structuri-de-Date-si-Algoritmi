#include "PriorityQueue.h"
#include "ShortTest.h"
#include <assert.h>

bool rel(TPriority p1, TPriority p2) {
	if (p1 <= p2) {
		return true;
	}
	else {
		return false;
	}
}




void testAll() { //call each function and see if it exists
	PriorityQueue pq(rel);
	
	assert(pq.isEmpty() == true);
	
	//adaugam 5, 3, 10, 2, 12 -> rezultat: 2, 3, 5, 10, 12
	pq.push(5, 5);
	assert(pq.top().first == 5);
	assert(pq.top().second == 5);
	pq.push(3, 3);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(10, 10);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(2, 2);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	pq.push(12, 12);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	assert(pq.isEmpty() == false);
	assert(pq.pop().second == 2);
	assert(pq.top().second == 3);
	assert(pq.pop().second == 3);
	assert(pq.top().second == 5);
	assert(pq.pop().second == 5);
	assert(pq.top().second == 10);
	assert(pq.pop().second == 10);
	assert(pq.top().second == 12);
	assert(pq.pop().second == 12);
	assert(pq.isEmpty() == true);
}


void testReverse() {
	PriorityQueue pq(rel);

	assert(pq.isEmpty() == true);

	//adaugam 5, 3, 10, 2, 12 -> rezultat: 2, 3, 5, 10, 12
	pq.push(5, 5);
	assert(pq.top().first == 5);
	assert(pq.top().second == 5);
	pq.push(3, 3);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(10, 10);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(2, 2);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	pq.push(12, 12);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	assert(pq.isEmpty() == false);
	
	// Apelam functia de reverse -> rezultat: 12, 10, 5, 3, 2
	pq.reverse();
	assert(pq.isEmpty() == false);
	// Top ar trebui sa fie 12, scoatem 12, topul ar trebui sa fie 10 dupa
	assert(pq.top().first == 12);
	assert(pq.top().second == 12);
	assert(pq.pop().second == 12);
	// Top ar trebui sa fie 10, scoatem 10, topul ar trebui sa fie 5 dupa
	assert(pq.top().first == 10);
	assert(pq.top().second == 10);
	assert(pq.pop().second == 10);

	// Top ar trebui sa fie 5, scoatem 5, topul ar trebui sa fie 3 dupa
	assert(pq.top().first == 5);
	assert(pq.top().second == 5);
	assert(pq.pop().second == 5);

	// Top ar trebui sa fie 3, scoatem 3, topul ar trebui sa fie 2 dupa
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	assert(pq.pop().second == 3);

	// Top ar trebui sa fie 2, scoatem 2, queue ar trebui sa fie empty dupa
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	assert(pq.pop().second == 2);

	assert(pq.isEmpty() == true);
}