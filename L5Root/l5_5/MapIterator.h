#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	//TODO - Representation

	int poz;
	bool parcurs_ht1;
	void find_next(const TElem*, int &);
	MapIterator(const Map& m);
public:

	const Map & getMap();

	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


