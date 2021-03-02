#pragma once
#include <utility>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111

////////////////////////////////////////////////////////////////////
// #define NULL_TELEM pair<TKey, TValue>(-111111, -111111) // asta era varianta lor


#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111)

//#define NULL_TELEM TElem(-111111, -111111)
////////////////////////////////////////////////////////////////////
//AICI SA NU CUMVA SA FIE PROBLEME!!

class MapIterator;

// typedef int(func)(int); // pointer la o functie

// #define Nmax 105
/*
struct CuckooHashTable
{
	int array[]


};
*/

class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

	private:
		//TODO - Representation

		int m; // initial iau tabelele de o dimensiune mica
		// int l; // am retinut si o variabila ca sa am metoda size de complexitate constanta
		//(retin nr de elemente din map in l)

		TElem* ht1; // hashtable1
		TElem* ht2; //hashtable2

		/*
		int f1(int);
		int f2(int);
		*/

		int f1(TKey k) const;
		int f2(TKey k) const;

		bool already_visited();

		void mark_empty(TElem *);

		// functie ca sa ma ajute cu debugging ul manual...
		//void afis_tabela(TElem*);
		//void afis_tabele();

		//void resize();
		//void rehash();
		//void resize_rehash();

	public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

	// destructor
	~Map();

};



