#include "ThirdPriorityQueue.h"
#include <exception>
#include <iostream>
using namespace std;

ThirdPriorityQueue ::ThirdPriorityQueue(Relation r){
    len = 0;
    cap = 20;
    Queue = new Element [cap];
    rel = r;

}

void ThirdPriorityQueue::push(TElem e, TPriority p) {
    Element new_elem;
    new_elem = make_pair(e,p);

    if(len == cap) //resize
    {
        Element* aux;
        cap = cap * 2;
        aux = new Element[cap];

        for(int i=0; i<len;i++)
            aux[i] = Queue [i];

        delete Queue;
        Queue = aux;

    }

    if(len == 0) // nu mai am elemete
    {
        Queue[0] = new_elem;
        len ++;
    } else if( len == 1) // mai am un singur element
    {
        if(rel( Queue[0].second, p)) // adaug noul element la final
        {
            Queue[len] = new_elem;
            len ++;
        } else{ // noul element trebuie adaugat inaintea primului
            Queue[1] = Queue[0];
            Queue [0] = new_elem;
            len++;
        }
    }

    else if(len == 2){
        if(rel( Queue[0].second, p))
        {
            Queue[2] = Queue[1];
            Queue[1] = new_elem;
            len ++;
        //} else if(!rel( Queue[0].second, p) && rel(Queue[1].second, p))
        } else // elementul trebuie adaugat la final
            {
                Queue[2] = new_elem;
                len ++;
            }

    }

    else
    {
        Queue[len] = new_elem; // adaug noul element la final si cresc lungimea
        len ++;

        // bubble-up
 /*
        if(poz%2 == 0) {
            int parent = (len - 1) / 2;
            while (poz > 1 && !rel(Queue[parent].second, new_elem.second)) {
                Queue[poz] = Queue[parent];
                poz = parent;
                parent = poz / 2;
            }
            Queue[poz] = new_elem;
        } else
        {
            int parent =( (len - 1) / 2)%10;
            while (poz > 1 && !rel(Queue[parent].second, new_elem.second)) {
                Queue[poz] = Queue[parent];
                poz = parent;
                parent = poz / 2;
            }
            Queue[poz] = new_elem;
        }
*/  
        int poz = len - 1;
        int parent = (len - 1) / 2;
            while (poz > 1 && !rel(Queue[parent].second, new_elem.second)) {
                Queue[poz] = Queue[parent];
                poz = parent;
                parent = poz / 2;
            }
            Queue[poz] = new_elem;

      //  Queue[poz] = new_elem;
    }


}

void ThirdPriorityQueue::afis()
{
    for (int i = len - 1; i >= 0; i--)
        cout << Queue[i].first << " " << Queue[i].second << '\n';
    cout << "============================\n";
}

Element ThirdPriorityQueue::top() const {
    if(atMostTwo()) // verific daca am mai putin de 3 elemente
    {
        exception ex;
        throw ex;
    }

    if(rel(Queue[1].second,Queue[2].second))
        return Queue[2];
    else
        return Queue[1];

   //return Queue[0];

}

Element ThirdPriorityQueue::pop() {
    if(atMostTwo()) // verific daca am mai putin de 3 elemente
    {
        exception ex;
        throw ex;
    }

}

bool ThirdPriorityQueue ::atMostTwo() const {
    if(len <= 2) // verific daca am cel mult 2 elemente
        return true;
    else
        return false;


}

ThirdPriorityQueue ::~ThirdPriorityQueue() { //destructor
    delete Queue; // dealoc spatiul pt Queue

}

Element* ThirdPriorityQueue::getQueue()
{
    return Queue;
}