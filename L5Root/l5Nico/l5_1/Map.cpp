#include "Map.h"
#include "MapIterator.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using std::cout;
using std::cin;

/*
 * Constructor of the class.
 */
Map::Map() {
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(n), since every element in the array must first be marked as empty.

    currentLength = 0;                                          // the current number of elemnts in the hashtabelles
    capacity = 23; // maximum number of elements for every hashtabelle
    // 193

	firstHash = new TElem[capacity];                            // 2 arrays for the cuckoo hashing
	secondHash = new TElem[capacity];                           // representing 2 hashtabelles

	for(int current = 0; current < capacity; current++) {
	    // Every element must firstly be marked as empty (by NULL_TELEM).
	    firstHash[current] = secondHash[current] = NULL_TELEM;
	}
}

/*
 * Destructor of the class.
 * Deallocates the reserved memory for the arrays.
 */
Map::~Map() {
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(n), the complexity of the delete function.

	delete[] firstHash;
	delete[] secondHash;
}

/*
 * Method to add an element to the map if it doesn't exist, or change its value otherwise.
 * @param c: the key to be added (or modified)
 * @param v: the value to be added to the key
 * @return: - NULL_TVALUE,  if the element didn't already exist and was added successfully;
 *          - value,        the former value of the key, if the element already existed.
 */

void Map::display() const
{

    cout << "========================================================================\n";
    cout << "capacity = " << capacity << '\n';
    for (int i = 0; i < currentLength; i++)
    {
        if (firstHash[i] != NULL_TELEM || secondHash[i] != NULL_TELEM)
        {
            cout << i << ". " <<
                firstHash[i].first << " " << firstHash[i].second
                << "          " <<
                secondHash[i].first << " " << secondHash[i].second << '\n';
    //        cin.get();
        }
    }
    cout << "========================================================================\n";
    cin.get();
}

void Map::apel_display() const
{
    display();
}
TValue Map::add(TKey c, TValue v){
	//TODO - Implementation
	// COMPLEXITY:
	// 1. best/average case: o(1), we calculate the position where the element should be added.
	// 2. worst case: o(n), in case we have reached the capacity or if we have an infinite cycle.

	TValue searchValue = search(c);     // search if the key exists (or not)
	if(searchValue != NULL_TVALUE) {
	    // If the key already exists, we modify its value.
	    // A key can only exist on 2 calculated positions in the two hashtabelles.
	    TValue oldValue;
	    if(firstHash[hashFunction1(c)].first == c) {
	        // If the key is in the first hashtabelle, ..
	        oldValue = firstHash[hashFunction1(c)].second;      // save former value in order to return
	        firstHash[hashFunction1(c)].second = v;             // modify former value
	    } else {
	        // If the key is in the second hashtabelle, ..
	        oldValue = secondHash[hashFunction2(c)].second;     // save former value in order to return
	        secondHash[hashFunction2(c)].second = v;            // modify former value
	    }
        return oldValue;
	}

	// If we reach this point, the value didn't already exist, so we have to add it.
	TElem element = std::make_pair(c, v);       // save the element
	currentLength++;                            // update the number of elements
	if(currentLength == capacity) {
	    // The hashtabelles are half empty, so we have to verify if the number of elements reaches the capacity,
	    // and not its doubled value.
	    // resize + rehash
//        cout << " se face resize la " << c << " " << v << '\n';
	    resize_rehash();
	}

	int positionHash1 = hashFunction1(c);       // calculate where the element should be added
	TElem removed = firstHash[positionHash1];   // save the former element, in case there was one

	firstHash[positionHash1] = element;         // put the element where we calculated

	if(removed == NULL_TELEM) {
	    // If no value was removed, ..
        return NULL_TVALUE;
    } else {
	    // If a value was removed, we have to reposition it.
	    int startPoint = positionHash1;         // saving the starting point in case of an infinite cycle
	    while(true) {
	        // I put true since there are multiple factors and conditions for the algorithm to stop.
	        // For simplicity, I verify both hashtabelles in one loop.

	        int positionHash2 = hashFunction2(removed.first);       // Calculate where the removed element should be placed
	                                                                // in the second hashtabelle.
	        std::swap(removed, secondHash[positionHash2]);   // The removed element is placed where calculated,
	                                                                // and we save the former element, in case it was removed.
	        if(removed == NULL_TELEM) {
	            // If we haven't removed any element, ..resize
                return NULL_TVALUE;
	        } else {
	            // If we have removed an element, ..
	            positionHash1 = hashFunction1(removed.first);          // Calculate where the removed element should be placed
	                                                                   // in the first hashtabelle.
	            std::swap(removed, firstHash[positionHash1]);   // The removed element is placed where calculated,
	                                                                    // and we save the former element, in case it was removed.
	            if(removed == NULL_TELEM) {
	                // If we haven't removed any element, ..
                    return NULL_TVALUE;
	            } else {
	                if(removed == element && startPoint == positionHash1) {
	                    // If we have made a complete cycle and came back from where we started,
	                    // it means we have to deal with an infinite loop, so we double the capacity and
	                    // reposition the elements.
                        //cout << " se face resize la " << c << " " << v << '\n';
	                    resize_rehash();
	                }
	            }
	        }
	    }
	}

    //cout << "dupa add:\n";
    //display();
}

/*
 * Method to search whether or not an element already exists in the map.
 * @param c: the key with which we search for the element.
 * @return: - NULL_TVALUE,  if the element doesn't exist;
 *          - value,        the value of the element, if it exists.
 */
TValue Map::search(TKey c) const{
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(1), we just calculate the possible position of situation

	if(isEmpty()) {
	    // If it's empty, ..
        return NULL_TVALUE;
	}

    // We have to calculate the possible positions where the element might be situated.
    if(firstHash[hashFunction1(c)].first == c) {
	    // If we find the key in the first hashtabelle, we return the value.
        return firstHash[hashFunction1(c)].second;
	}
	if(secondHash[hashFunction2(c)].first == c) {
	    // If we find it in the second, ..
        return secondHash[hashFunction2(c)].second;
	}

	// If we reach this point, it means that the element doesn't exist.
	return NULL_TVALUE;
}

/*
 * Method that removes an element from the map by marking its position as empty with NULL_TELEM.
 * @param c: the key with which we search for the element.
 * @return: - NULL_TVALUE,  if the element doesn't exist, we can't remove it;
 *          - value,        the value of the element, if it existed.
 */
TValue Map::remove(TKey c){
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(1), we just calculate the possible position of situation
	//                                             and then mark as empty with NULL_TELEM.

    if(isEmpty() || search(c) == NULL_TVALUE) {
        // If it's empty or it wasn't found, it means that there is no element to remove.
        return NULL_TVALUE;
    }
    int p1 = hashFunction1(c), p2=  hashFunction2(c);
    if(firstHash[p1].first == c) {
        // If we find the key in the first hashtabelle, we return the value and mark the position as empty.
        TValue oldValue = firstHash[p1].second;     // save the former value for return
        firstHash[p1] = NULL_TELEM;                 // mark the position as empty with NULL_TELEM
        currentLength--;  // update the number of elements
        
        
        //cout << "dupa remove:\n";
        //display();
        

        return oldValue;
    }
    if(secondHash[p2].first == c) {
        // If we find it in the second, we return the value and mark the position as empty.
        TValue oldValue = secondHash[p2].second;    // save the former value for return
        secondHash[p2] = NULL_TELEM;                // mark the position as empty with NULL_TELEM
        currentLength--;                            // update the number of elements

        //cout << "dupa remove:\n";
        //display();


        return oldValue;
    }

//    cout << "dupa remove(nu s a eliminat nimic)!!!!\n";
    // display();


    // If it reaches this point, it means the element wasn't removed successfully.
    return NULL_TVALUE;
}

/*
 * Method to calculate the number of elements in the map.
 * @return: an integer representing the number of elements in the map.
 */
int Map::size() const {
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(1), the number of elements was updated with every operation, so we just
	//                                              return it.

	return currentLength;
}

/*
 * Method that verifies whether or not the map is empty.
 * @return: - true,     if the map has no element;
 *          - false,    if the map has at least one element.
 */
bool Map::isEmpty() const{
	//TODO - Implementation
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(1),  the size was constantly updated, we have to verify if it is 0,
	//                                              meaning the array is empty.

	return currentLength == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}

/*
 * These two methods receive a key and calculate the position where the key should be.
 * They change depending on the capacity of the array, the complexity being o(1) in every case.
 * In case of negative number we apply the absolute value to avoid a negative rest.
 * @param key: the key of the element.
 * @return: a positive integer representing the position of the element.
 */
int Map::hashFunction1(TKey key) const {
    // return (2 * abs(key) + 3) % capacity;
//    return abs(key) % capacity;
    // return (abs(key) + 10) % capacity;
    return (3 * abs(key) + 5) % capacity;
    // return abs(key) % capacity;
}
int Map::hashFunction2(TKey key) const {
    // return 2 * abs(key) % capacity;
//    return (abs(key) / capacity) % capacity;
    //return ( (abs(key) + 10) / capacity ) % capacity;
    return (7 * abs(key) + 9)  % capacity;
    //return ( abs(key) + 5 )% capacity;
}

/*
 * Method to do the operations of resize and rehash.
 * Double the capacity and reposition every element with the new functions.
 */
void Map::resize_rehash() {
    // COMPLEXITY:
    // 1. overall (best/average/worst case): o(n), since every element must be repositioned.

    std::cout << " s a facut resize !!" << '\n';

    capacity <<= 1;                     // double the capacity

    auto aux1 = new TElem[capacity];    // allocate the doubled space for the hashtabelles
    auto aux2 = new TElem[capacity];

    for(int current = 0; current < capacity; current++) {
        // Initialized the space with NULL_TELEM to mark it as empty.
        aux1[current] = aux2[current] = NULL_TELEM;
    }

    for(int current = 0; current < capacity >> 1; current++) {
        // We take every element from the 2 arrays in order to reposition them in the new ones.
        TElem e1 = firstHash[current], e2 = secondHash[current];    // elements to be repositioned

        // Here there is no chance of infinite loops or not enough space.
        if(e1 != NULL_TELEM) {
            // If there is an element, we add it.
            int p1 = hashFunction1(e1.first);       // place in fist hashtabelle
            TElem removed = aux1[p1];
            aux1[p1] = e1;

            if(removed != NULL_TELEM) {
                while(true) {
                    // if we have removed an element, we apply the same algorithm as in the add function
                    int p2 = hashFunction2(removed.first);      // save removed element in second hash
                    std::swap(removed, aux2[p2]);
                    if(removed == NULL_TELEM) {
                        break;
                    } else {
                        // if we removed an element, ..
                        p1 = hashFunction1(removed.first);
                        std::swap(removed, aux1[p1]);   // save removed element in first hash
                        if(removed == NULL_TELEM) {
                            break;
                        }
                    }
                }
            }
        }

        // ANALOG ^
        if(e2 != NULL_TELEM) {
            // if the position wasn't empty, ..
            int p1 = hashFunction1(e2.first);
            TElem removed = aux1[p1];
            aux1[p1] = e2;

            if(removed != NULL_TELEM) {
                while(true) {
                    // if we have removed an element, we apply the same algorithm as in the add function
                    int p2 =hashFunction2(removed.first);       // save removed element in second hash
                    std::swap(removed, aux2[p2]);
                    if(removed == NULL_TELEM) {
                        break;
                    } else {
                        // if we removed an element, ..
                        p1 = hashFunction1(removed.first);      // save removed element in first hash
                        std::swap(removed, aux1[p1]);
                        if(removed == NULL_TELEM) {
                            break;
                        }
                    }
                }
            }
        }
    }

    // deallocate the former space.
    delete[] firstHash;
    delete[] secondHash;

    // update.
    firstHash = aux1;
    secondHash = aux2;
}



