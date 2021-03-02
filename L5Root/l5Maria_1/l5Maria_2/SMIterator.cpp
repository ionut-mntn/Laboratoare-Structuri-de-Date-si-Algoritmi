#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    //TODO - Implementation
    current_position = 0;
//    current_node = new Node;
    current_node = nullptr;
}

void SMIterator::first(){
    //TODO - Implementation
    int i =0;
//    for(int i=0; i< map.capacity; i++)
//    {
//        if (map.elems[i] != nullptr)
//    }

//    while(map.elems[i] == nullptr)
//        i++;
//    current_position = i;
//    current_node = map.elems[i];
    while(current_position<map.capacity && map.elems[current_position] == nullptr)
        current_position++;
    if(current_position<map.capacity)
        current_node = map.elems[current_position];
    else
        current_node = nullptr;

}

void SMIterator::next(){
    //TODO - Implementation
    // complexitate: best case = Θ(1) , avg case = worst case = O(capacity)
    if(valid()) {
        if (current_node->next_in_map != nullptr)
        {
            current_node = current_node->next_in_map;
            cout << "intra aici! Ar trebui sa intre?\n";
        }
        else {
            cout << "intra aici2222222222222 ! Ar trebui sa intre?\n";
            current_position++;
            while (current_position < map.capacity && map.elems[current_position] == nullptr)
                current_position++;
            if (current_position != NULL_TVALUE)
                current_node = map.elems[current_position];
            else
                current_node = nullptr;
        }
    } else{
        // cout << "arunca exceptie!!!\n";
        exception  ex;
        throw ex;
    }
}

bool SMIterator::valid() const{
    //TODO - Implementation
    // complexitate: best case = avg case = worst case = Θ(1)
    if(current_node == nullptr)// or current_position>= map.capacity)
        return false;
    else
        return true;
}

TElem SMIterator::getCurrent() const{
    //TODO - Implementation
    // complexitate: best case = avg case = worst case = Θ(1)
    if (valid())
    {
//        cout << 
        return current_node->info;
    }
    else{
        exception ex;
        throw  ex;
    }
}


