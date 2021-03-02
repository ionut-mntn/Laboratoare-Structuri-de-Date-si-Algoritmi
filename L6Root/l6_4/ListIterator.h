#pragma once
#include "SortedIndexedList.h"
#include <stack>

using std::stack;

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	//TODO - Representation

	NodeSL* current;
	//bool;
	void next_wrapper(NodeSL* current_node);

	//NodeSL aux_stack[list.size()];
	
	/*
	NodeSL* aux_stack;
	int dim_stack;
	*/
	
//	NodeSL* aux_stack;

	/*
	stack<NodeSL>* aux_stack;
	bool hasNext();
	void pushToLeft(NodeSL* node);
	*/	
public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};