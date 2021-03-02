#pragma once
#include <utility> // pentru `pair`, I suppose
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TKEY -111111	// asta am adaugat-o eu
#define NULL_TVALUE -111111
#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111)
/*
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111) // asta era varianta initiala, dar nu mergea
sau o mai puteam scrie asa (nu-s sigur de ele, dar de probat si variantele astea si vazut):
1)#define NULL_TELEM std::pair<TKey, TValue>(NULL_TKEY, NULL_TVALUE)
	sau
2)#define TElem(NULL_TKEY, NULL_TVALUE)
*/

class MapIterator;


class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

	private:
		//TODO - Representation
		
		int m;		/* capacitatea container-ului (unde "container" = cele 2 subcontainere: prima, respectiv cea de-a doua tabela hash) */
		int len;	/* "lungimea" (nr de elemente din container) */

		TElem* ht1; // hashtable1
		TElem* ht2; // hashtable2
		
        int h1(TKey k) const;	// functia corespunzatoare primei tabele hash
        int h2(TKey k) const;	// functia corespunzatoare celei de-a doua tabele hash

		/*
			    Initializez la "valoarea nula" (`NULL_TELEM`, in cazul nostru) array-ul `tabela` cu elemente de tip `TElem`, indexat [0, ..., `dim`-1]
		*/
		void mark_empty(TElem* tabela, const int& dim);

        /*
			Modific dimensiunea container-ului (o maresc) si rearanjez (fac "rehashing" pentru) elementele din cele 2 vechi tabele hash.
			!Atentie! 
			In cazul implementarii mele, singura modificare pe care o aduc functiei in caz de "rehash" este aceea - sa o numim - "implicita", adica cea data de schimbarea valorii lui m.
		*/
        void resize_rehash();
		
		/*
			Metoda auxiliara pentru a ma ajuta cu debugging-ul "manual".
			Afiseaza containerele, dispuse vertical.
		*/
		void display() const;
public:

	/* stiu ca e un pic ciudat sa fac asta (o sa vedeti in .cpp ca eu in metoda asta pur si simplu apelez
	metoda privata `display` de mai sus, dar pe moment asta mi s-a parut singura alternativa la: a nu fi avut metoda `display` publica )*/
	void apel_display() const;


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