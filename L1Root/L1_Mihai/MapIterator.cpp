#include "Map.h"
#include "MapIterator.h"
#include <exception>
#include <iostream>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation
	if(!d.isEmpty()){
	    i=0;
	}

}


void MapIterator::first() {
	//TODO - Implementation
	i=0;


}


void MapIterator::next() {
	//TODO - Implementation

	i=i+1;
}


TElem MapIterator::getCurrent(){
	//TODO - Implementation
	if(i<map.size()){
        TElem ret;
        ret.first = map.sir[i].first;
        ret.second = map.sir[i].second;
        return ret;
    }

	return NULL_TELEM;
}


bool MapIterator::valid() const {
	//TODO - Implementation
	return i<map.size();
}



