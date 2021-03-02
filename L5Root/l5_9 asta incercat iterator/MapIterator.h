#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	//TODO - Representation

	//int positionFirst, positionSecond;  //positions in the two hashtabelles

	int poz;
	bool parcurs_ht1;
	void find_subcontainer_next(const TElem*);
	void find_next();

	MapIterator(const Map& m);

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


