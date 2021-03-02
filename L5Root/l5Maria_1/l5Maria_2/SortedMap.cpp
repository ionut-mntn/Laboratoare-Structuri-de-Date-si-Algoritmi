#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

/*
SortedMap::afis()
{
    Node* aux;
    while(aux != )
    for(int i = 0; i < len; i++)
        
        cout << 
}
*/

SortedMap::SortedMap(Relation r) {
    //TODO - Implementation
    rel = r;
    len = 0;
    capacity = 100;
    elems = new Node*[capacity]; // asta e vector de pointeri?
   // array = new TKey[1000];
   head = new Node;
   head = nullptr;

    for(int i=0; i<capacity;i++) // initializez
    {
//        elems[i] = nullptr;

        cout << "intra\n";
        elems[i]->next_in_list= nullptr;
        cout << "intra\n";
        elems[i]->next_in_map = nullptr;
        elems[i]->info= NULL_TPAIR;

/*
        elems[i].next_in_list = nullptr;
        elems[i].next_in_map = nullptr;
        elems[i].info = NULL_TPAIR;
*/
        /*
        * (elems + i).next_in_list = nullptr;
        * (elems + i).next_in_map = nullptr;
        * (elems + i).info = NULL_TPAIR;
        */
    }
}

int SortedMap::hash_function(int capacity, TKey k) const{
    return (k % capacity);

}

TValue SortedMap::add(TKey k, TValue v) {
    //TODO - Implementation

   int position = hash_function(capacity, k);
   Node* new_node = new Node;
   new_node->next_in_list = nullptr;
   new_node->next_in_map = nullptr;
   new_node->info = make_pair(k,v);

   if(isEmpty()){ // daca nu mai am valori in Hashtable
       len ++;
       elems[position] = new_node;
       head = elems[position];
       return NULL_TVALUE;
   }

   if(search(k) == NULL_TVALUE) // daca mai am elemente, dar cheia k nu exista in  hashtable
   {
       if(elems[position] == nullptr) { // pozitia din elems este libera; trebuie sa schimb doar next_in_map
           len ++;
           elems[position] = new_node;

           Node * current = new Node;
           current = head;
           // verific daca noul element nu trebuie sa fie head
           if(rel(k, head->info.first))
           {
               elems[position]->next_in_map = head;
               head = elems[position];
               return NULL_TVALUE;
           }
           // parcurg nodurile ca sa fac legaturile cu noul element
           while (current->next_in_map != nullptr && !rel(current->info.first, k))
               current=current->next_in_map;
           // ies din while cand am ajuns la final  sau am gasit locul noului element
           if(current->next_in_map == nullptr) // daca am ajuns la final
               if(rel(current->info.first, k)) // elementul va fi ultimul in map
               {
                   current->next_in_map = elems[position];
                   return NULL_TVALUE;
               }
           if(rel(current->info.first, k)) // am gasit locul noului element in hashtable
           {
               Node * aux = new Node;
               aux = current->next_in_map;
               current ->next_in_map = elems[position];
               elems[position]->next_in_map = aux;
           }
           return NULL_TVALUE;
       }
       else
           //elems[position]  este o pozitie ocupata
       {
           len ++;
           Node * parcurgere = new Node;
           parcurgere = head;
           if(rel(k, head->info.first))
           {
               new_node->next_in_map = head;
               head = new_node;
           }
           // parcurg nodurile ca sa fac legaturile cu noul element
           while (parcurgere->next_in_map != nullptr && !rel(parcurgere->info.first, k))
               parcurgere = parcurgere->next_in_map;
           // ies din while cand am ajuns la final  sau am gasit locul noului element
           if(parcurgere->next_in_map == nullptr) // daca am ajuns la final
               if(rel(parcurgere->info.first, k)) // elementul va fi ultimul in map
               {
                   parcurgere->next_in_map = new_node;
               }
           if(rel(parcurgere->info.first, k)) // am gasit locul noului element in hashtable
           {
               Node * aux = new Node;
               aux = parcurgere->next_in_map;
               parcurgere ->next_in_map = new_node;
               new_node->next_in_map = aux;
           }

           Node* current = new Node;
           current = elems[position];
           while (current->next_in_list != nullptr)
               current = current->next_in_list;
           // ies din while cand current se afla pe ultima pozitie din lista inlantita
           current->next_in_list = new_node;

           return NULL_TVALUE;
       }
   }else { // daca cheia exista deja, next-ul elem in map este bun
       Node* current = new Node;
       current = elems[position];
       while (current != nullptr && current->info.first != k)
           current = current->next_in_list;
       if (current != nullptr)
       {
           TValue old_value = current->info.second;
           current->info.second = v;
           return old_value;

       }
   }
}

TValue SortedMap::search(TKey k) const {
    //TODO - Implementation
    if(isEmpty())
        return NULL_TVALUE;

    int position = hash_function(capacity, k);
    Node* current = new Node;
    current = elems[position];
    while (current != nullptr && current->info.first != k)
        current = current->next_in_list;
    if(current== nullptr)
        return NULL_TVALUE;
    if (current->info.first == k ) {
        //cout << current->info.second<<" ";
        return current->info.second;
    }

}

TValue SortedMap::remove(TKey k) {
    //TODO - Implementation
    if(isEmpty())
        return NULL_TVALUE;

    if(search(k) == NULL_TVALUE) // cheia nu exista in map
        return NULL_TVALUE;
    else{
        len --;
        int position = hash_function(capacity, k);
        Node* current = new Node;
        Node * previous = new Node;
        Node * parcurgere = new Node;
        parcurgere = head;
        current = elems[position];

        while (current != nullptr && current->info.first != k) {
            previous = current;
            current = current->next_in_list;
        } // in previous am elementul precedent
        if(current->info.first == k)
        {
            TValue old = current->info.second;
            previous->next_in_list = current->next_in_list; // refac legaturile in lista inlantuita
            // refac legaturile si in map
            if(head->info.first==k)
            {
                head = head->next_in_map;
                return old;
            }
            while(parcurgere!= nullptr && parcurgere->next_in_map->info.first!=k)
                parcurgere = parcurgere->next_in_map;
            // ies din while cand am gasit elementul precedent elementului  care trebuie sters
            if(parcurgere->info.first == k)
            {
                Node * to_delete = new Node;
                to_delete = parcurgere->next_in_map;
                parcurgere->next_in_map = to_delete->next_in_map;
                return old;
            }

        }


    }

}

int SortedMap::size() const {
    //TODO - Implementation
    return len;
}

bool SortedMap::isEmpty() const {
    //TODO - Implementation
    if(len == 0)
        return  true;
    else
        return false;
}

SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

SortedMap::~SortedMap() {
    //TODO - Implementation
}
