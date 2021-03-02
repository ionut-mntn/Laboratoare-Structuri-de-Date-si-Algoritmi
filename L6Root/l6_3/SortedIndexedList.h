#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

/*
bool operator==(TComp lhs, TComp rhs) // Daca e gresit ca am facut overload la operatorul asta aici, in .h va rog sa imi spuneti
{
	return int(lhs) == int(rhs); // e bun asa? pare un pic de "overhead"
}
*/

struct NodeSL {// Node Sorted List

	TComp info;

	NodeSL* lc; // address of left child
	NodeSL* rc; // address of right child

	int LeftChildrenCount; // number 

	// NodeSL * f; // address of father

	//int list_index; 

}; // AICI LIPSEA UN punct-virgula asta era problema!!!!!!!!!!!!

class SortedIndexedList {
private:
	friend class ListIterator;
private:
	//TODO - Representation

	NodeSL* root; // daca o sa am si father, tatal astuia o sa fie NULL, evident!!
	Relation rel; // ATENTIE! a fost facut un typedef (redenumire de tip) mai sus 
	int len;

	NodeSL* initNode(TComp e);

	NodeSL* add_wrapper(NodeSL* current_node, TComp e); // poate impropriu denumita asa, pentru ca nu in wrapper ul asta apelez add-ul dat deja de interfata,
	// ci fac invers: apelez metoda aceasta in interioriul metodei deja cerute de interfata data

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element to a given position
	//throws an exception if the position is not valid
	// ( vad ca in teste nu e nicaeri vreo structura de genul try-except care sa astepte
	// exceptii de la `add`)
	void add(TComp e);
	
	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

};
