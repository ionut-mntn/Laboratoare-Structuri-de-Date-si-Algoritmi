#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	//TODO - Implementation
	//constructor
	this->len = 0;
	this->cap = 10;
    this->sir = new TElem[cap];




}

Map::~Map() {
	//TODO - Implementation
	//destructor
	delete []sir;
}

TValue Map::add(TKey c, TValue v){
	//TODO - Implementation
    TValue aux;

	for(int i=0;i<this->len;i++){
	    if(this->sir[i].first == c ){
	        aux = this->sir[i].second;
	        this->sir[i].second=v;
	        return aux;
	    }
	}

    this->sir[len].first=c;
    this->sir[len].second=v;
    this->len++;

	if(this->len == this->cap)
    {
	    this->cap = this->cap * 2 + 1;
        TElem *newElems = new TElem[cap];
        for(int i = 0; i < len; i ++)
            newElems[i] = sir[i];
        delete []sir; // aici doar se dealoca spatiul de memorie
        // alocat incepand cu adresa catre care pointeaza 'sir'
        //(alocata initial, in constructor); dar pointer ul ramane!!
        sir = newElems; // aici schimbam adresa catre care
        // pointeaza pointer ul 'sir'
    }
	return NULL_TVALUE;
}

TValue Map::search(TKey c) const{
	//TODO - Implementation
	for(int i=0;i<len;i++){
        if(sir[i].first == c){
            return sir[i].second;
        }
	}

	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	//TODO - Implementation
	int pos=-1;
    for(int i=0;i<len;i++){
        if(sir[i].first == c){
            pos=i;
            break;
        }
    }
    if(pos==-1)
        return NULL_TVALUE;
    TValue ret;
    ret=sir[pos].second;
    for(int j=pos;j<len;j++){
        sir[j]=sir[j+1];
    }
	len--;
	return ret;
}


int Map::size() const {
	//TODO - Implementation
	return len;
}

bool Map::isEmpty() const{
	//TODO - Implementation
	///return !bool(len);
	return (len==0);
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}




