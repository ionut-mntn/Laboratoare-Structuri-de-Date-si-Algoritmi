#pragma once
#include <utility>

using namespace std;

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

class ThirdPriorityQueue
{
private:
    //representation of the ThirdPriorityQueue
    int cap; 
    int len;
    int poz;
    Element* elems;
    Relation rel;
    Element  p1, p2;

public:
    int get_pozitie_coada();

    void afis();

    int getLen();

    //implicit constructor
    ThirdPriorityQueue(Relation r);

    void bubble_up(int pozition); // functie ajutatoare pentru push

    void bubble_down(int pozition);

    //adds an element with a priority to the queue
    void push(TElem e, TPriority p);

    //returns the element with the third highest priority with respect to the relation
    //throws exception if the queue has less than 3 elements
    Element top()  const;

    //removes and returns the element with the third highest priority
    //throws exception if the queue has less than 3 elements
    Element pop();

    //checks if the queue has at most two elements
    bool atMostTwo() const;

    //destructor
    ~ThirdPriorityQueue();
};

