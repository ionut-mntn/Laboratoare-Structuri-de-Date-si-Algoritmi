//#include "Queue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>

using std::cout;

typedef int TElem;
struct Node {
	TElem data;
	Node* next;
	Node* prev;
};

class Queue {
private:
	Node* head;
	Node* tail;
public:

	Queue()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
	void push()
	{
		/*
		//	Node new_node;
		//	Node.data = elem;
		//Node aux = new Node[1];
		Node new_node = new Node; // il aloc dinamic, pentru ca la iesirea din aceasta functie sa nu mi se distruga obiectul ( ..cred )
		new_node.data = elem;
		// pana aici, creez un nod
		if (isEmpty())
		{
			new_node.next = nullptr;
			new_node.prev = nullptr;
			head = &aux;
			tail = &aux;
		}
		else
		{
			last->next = &new_node
		}
		*/
	}
};


int main() {

	
	testAll();
	testAllExtended();

	cout << "Test end" << '\n';
	
	/*
	Node ob;
	//cout << ob.data << " " << ob.next << " " << ob.prev << '\n';
	//Node ob2();
	//cout << ob2.data << " " << ob2.next << " " << ob2.prev << '\n';
	*/

	return 0;
}