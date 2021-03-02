#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	//TODO - Representation

	int poz;				// indexul elementului curent din container-ul `map`; 
	bool parcurs_ht1;		// variabila contor cu seminficatiile: true - iteratorul a parcurs prima tabela; false - iteratorul nu a parcurs prima tabela

	/* pozitioneaza iteratorul pe urmatorul element existent din tabela hash `ht`, adica seteaza `poz` la indexul acestuia in tabela `ht` sau la -1 daca nu s-a gasit niciun "urmator element" in tabela `ht` */
	void find_subcontainer_next(const TElem* ht);

	/* pozitioneaza iteratorul pe urmatorul element existent din ambele tabele ( daca nu mai exista elemente in `ht1` va continua cautarea in `ht2`; pozition  */
	void find_next();

	MapIterator(const Map& m);

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


