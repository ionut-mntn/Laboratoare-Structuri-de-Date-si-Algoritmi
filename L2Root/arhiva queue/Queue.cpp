#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
	//TODO - Implementation
	
	head = nullptr;
	tail = nullptr;

}


void Queue::push(TElem elem) {
	//TODO - Implementation
}


TElem Queue::top() const {
	//TODO - Implementation
	return NULL_TELEM;
}

TElem Queue::pop() {
	//TODO - Implementation
	return NULL_TELEM;
}

bool Queue::isEmpty() const {
	//TODO - Implementation
	
//	return this->head.next == nullptr; // ori first ori last pointeaza catre o adresa null

	return false;
}


Queue::~Queue() {
	//TODO - Implementation
}

