#pragma once
#include <utility>

using namespace std;

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);
#define NULL_ELEMENT Element(-111111, -111111)
/* nu s sigur ca e bine ce e mai jos !!
// posibil sa nu fi trebuiasca sa fie definit si asta; la urma urmei, e un int
// cred ca rezolva compiler ul treaba cumva... dar na; ca sa fiu sigur, 
// am suprascris operatorul asta
bool operator<(const TPriority &lhs, const TPriority& rhs)
{
	return lhs < rhs;
}

bool operator<(const Element& lhs, const Element& rhs) // left hand side, respectively right hand side
{
	return lhs.second < rhs.second;
}
*/

class ThirdPriorityQueue
{
private:
	//representation of the ThirdPriorityQueue

	int cap;
	int len;
	
//	std::pair<TElem, TPriority>* elems;
	Element* elems;
	Relation rel;
	/* am adaugat si un bubble-up si un bubble-down ca sa ma ajute pe mine;
		le-am adaugat aici pentru ca nu vreau ca acestea sa fie accesibile 
		din exterior
	*/

	void bubble_up(int);
	void bubble_down(int);
	void resize();

public:
	//implicit constructor
	ThirdPriorityQueue(Relation r);

	//adds an element with a priority to the queue
	void push(TElem e, TPriority p);

	 //returns the element with the third highest priority with respect to the relation
	//throws exception if the queue has less than 3 elements
	Element top()  const;	// deci am de facut cateva comparatii pe acolo...

	//removes and returns the element with the third highest priority
	//throws exception if the queue has less than 3 elements
	Element pop();

	//checks if the queue has at most two elements
	bool atMostTwo() const;

	void toString() const;

	 //destructor
	~ThirdPriorityQueue();
};

