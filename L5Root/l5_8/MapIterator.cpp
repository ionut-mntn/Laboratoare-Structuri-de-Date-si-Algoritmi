#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

/*
 * Constructor of the class.
 */
MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation
	// COMPLEXITY:
	// 1. complexity of the first function.

	// Set the indices of the hashtabelles on the first elements.
	// The indices determine wether or not we are in a hashtabelle or the other.
	first();
}

/*
 * Set the index of the first array to the first element (if exists), or the index of the second array.
 */
void MapIterator::first() {
	//TODO - Implementation
	// COMPLEXITY:
	// 1. best case: o(1), if the first element in the first hashtabelle is close by the position 0
	// 2. average/worst case: o(n), if the first array is empty or its first element is close to the end

	positionSecond = -1;    // we are not on the second array yet
    positionFirst = 0;      // we are in the first array
    while (map.ht1[positionFirst] == NULL_TELEM && positionFirst < map.m) {
        // if we haven't reached the end of the first array or haven't encountered the first element, ..
        positionFirst++;
    }
    if(map.m == positionFirst) {
        // if we don't have a first element in the fisrt hashtabelle, we search in the second
        positionSecond = 0;
        while(map.ht2[positionSecond] == NULL_TELEM) {
            // until we encounter an element in the second hashtabelle.
            positionSecond++;
        }
    }
}

/*
 * Method to move the iterator to the next position.
 */
void MapIterator::next() {
	//TODO - Implementation
	// COMPLEXITY:
	// 1. best case: o(1), if the position is invalid or the verified elements are close to each other.
	// 2. average/worst case: o(n), if we have to go through the first array and some of the second in order to find
	//                              the next element.
	// An element is marked by a value different from NULL_TELEM.

	if(!valid()) {
	    // If the position isn't valid, ..
	    throw std::exception();
	}

	// If the position is valid,
	positionFirst++;
    while(positionFirst < map.m && map.ht1[positionFirst] == NULL_TELEM) {
        // move in the first array
        positionFirst++;
    }
    if(positionFirst < map.m) {
        // if we are within the first array, ..
        return;
    }
    positionSecond++;
    while(positionSecond < map.m && map.ht2[positionSecond] == NULL_TELEM) {
        // move in second array
        positionSecond++;
    }
}

/*
 * Method that returns the element at the current position.
 * @return: the element on the current position.
 */
TElem MapIterator::getCurrent(){
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(1), we just calculate the exact position or throw an exception.
	if(!valid()) {
	    // If the position is invalid, ..
	    throw std::exception();
	}
	if(positionFirst > -1 && positionFirst < map.m) {
	    // If we are within the first hashtabelle, ..
        return map.ht1[positionFirst];
	}
	if(positionSecond > -1 && positionSecond < map.m) {
	    // If we are within the second hashtabelle, ..
        return map.ht2[positionSecond];
	}

	// Doesn't reach the end since at least one of the positions is valid.
}

/*
 * Method that verifies if the iterator is valid.
 * @return: - true,     if the iterator is valid;
 *          - false,    if the map is empty or we have reached the end.
 */
bool MapIterator::valid() const {
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(1), we just verify a condition.

	// If the map is empty or we have reached its end, ..
    return !(map.isEmpty() || positionSecond >= map.m);
    // return !(positionSecond >= map.capacity);

}



