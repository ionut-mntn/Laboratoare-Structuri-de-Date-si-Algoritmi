#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r) {
    head = tail = nullptr;
    this->r = r;
	//TODO - Implementation
}

TValue SortedMap::add(TKey k, TValue v) {
    if(isEmpty() 
    {
        Node* newNode = new Node;
        newNode->key = k;
        newNode->value = v;
        head = newNode;
        tail = newNode; 
        return NULL_TVALUE;
    }
    else if(size() == 1){
        TValue x = head->value;
        head->value = v;
        return x;
    }
    if(tail == nullptr){
        if(r(head->key,k)){
            Node* newNode = new Node;
            newNode->key = k;
            newNode->value = v;
            tail = newNode;
            tail->prev = head;
            head->next = tail;
            return NULL_TVALUE;
        }
        else
        {
            tail = head;
            head->value = v;
            head->key = k;
            head->next = tail;
            tail->prev = head;
            return NULL_TVALUE;
        }
    }
    Node* iter = head;
    while(r(iter->key,k))
    {
        iter = iter->next;
    }
    if(iter->key == k)
    {
        TKey x = iter->key;
        iter->key = k;
        iter->value = v;
        return x;
    }
    else{
        Node* x = iter;
        x->value = v;
        x->key = k;
        iter->prev->next = x;
        iter->prev = x;
        x->next = iter;
        return NULL_TVALUE;
    }
    //TODO - Implementation

}

TValue SortedMap::search(TKey k) const {
	//TODO - Implementation
	Node* i = head;
	while(i!=tail) {
        if (i->key == k)
            return i->value;
        if (r(i->key, k))
            i = i->next;
    }
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    if(search(k)){
        if(head->key == k)
        {
            TValue x = head->value;
            Node * n = new Node;
            n = head->next;
            head = n;
            return x;
        }
        if(tail->key == k)
        {
            tail->prev->next = nullptr;
            int v = tail->value;
            tail = tail->prev;
            return v;
        }
        Node* iter = head;
        while(iter!= nullptr){
            if(iter->key == k)
            {
                TValue x = iter->value;
                iter->next->prev = iter->prev;
                iter->prev->next = iter->next;
                delete iter;
                return x;
            }
            iter = iter->next;
        }
    }
	//TODO - Implementation
	return NULL_TVALUE;
}

int SortedMap::size() const {
	//TODO - Implementation
    if (isEmpty())
        return 0;
    else
    {
        int counter = 0;
        Node* iter = head;
        while (iter != nullptr) {
            counter++;
            iter = iter->next;
            if (head->next == nullptr) cout << "Da" << '\n';
            else cout << " Nu" << '\n';
        }
        cout << "ajunge 2" << '\n';
        return counter;
    }
}

bool SortedMap::isEmpty() const {
	//TODO - Implementation
	if(head== nullptr && tail == nullptr)
        return true;
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	    Node* iter = head;
	    while(iter->next){
	        iter = iter->next;
	        delete iter->prev;
	    }
	    delete tail;
	}
	//TODO - Implementation
