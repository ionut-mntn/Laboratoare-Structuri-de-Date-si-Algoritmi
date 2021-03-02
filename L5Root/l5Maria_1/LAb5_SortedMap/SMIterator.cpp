#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    //TODO - Implementation
    current_position = 0;
    current_node = new Node;
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
    while(current_position<map.capacity and map.elems[current_position] == nullptr)
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
            current_node = current_node->next_in_map;
        else {
            current_position++;
            while (current_position < map.capacity && map.elems[current_position] == nullptr)
                current_position++;
            if (current_position != NULL_TVALUE)
                current_node = map.elems[current_position];
            else
                current_node = nullptr;
        }
    } else{
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
    if(valid())
        return current_node->info;
    else{
        exception ex;
        throw  ex;
    }
}


