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
    if (valid()) i ++;
	else {exception e; throw e;}
}


TElem MapIterator::getCurrent(){
	//TODO - Implementation
        if( valid() ){
            /*
            TElem ret;
            ret.first = map.sir[i].first;
            ret.second = map.sir[i].second;
            return ret;
            */
//            return TElem(map.sir[i].first, map.sir[i].second);
        return map.sir[i];

        }
//    }
    else { //cout<<"ajunge si aici"<<'\n';
    exception f; throw f;}
	///return NULL_TELEM;
}


bool MapIterator::valid() const {
	//TODO - Implementation
	return (0 <= i && i < map.len );
}




