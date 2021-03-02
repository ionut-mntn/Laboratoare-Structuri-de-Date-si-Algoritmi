#include "ThirdPriorityQueue.h"
#include <exception>
#include <iostream>
using namespace std;

ThirdPriorityQueue ::ThirdPriorityQueue(Relation r)
{
    len = 0;
    cap = 20;
    poz = 0;
    elems = new Element [cap];
    rel = r;
    p1 = p2 = make_pair(0,0);

}

void ThirdPriorityQueue ::bubble_up(int pozition)
{
    int poz = pozition;
    Element elem = elems[poz];
    int parent = poz /2;
     while (poz> 0 && rel(elem.second, elems[parent].second))
     {
         elems[poz] = elems[parent];
         poz = parent;
         parent = poz /2;
     }
     elems[poz] = elem;
}

void ThirdPriorityQueue :: bubble_down(int pozition)
{
    int poz = pozition, max_child =-1;
    Element elem = elems[poz];
    while(poz < len)
    {
        max_child = -1;
        if(poz*2 <= len) max_child=poz*2;
        
        if(poz*2 + 1 <= len && rel(elems[2*poz+1].second,elems[2*poz].second) max_child = poz*2+1;
        
        if(max_child !=-1 && rel(elems[max_child].second, elem.second))
        {
            elems[poz] = elems[max_child];
            poz = max_child;
        }else{
            elems[poz]=elem;
            poz = len + 1;
        }

    }
}

void ThirdPriorityQueue::push(TElem e, TPriority p) 
{
    //Element new_elem;
   // new_elem = make_pair(e,p);

    if(len == cap) //resize
    {
        Element* aux;
        cap = cap * 2;
        aux = new Element[cap];

        for(int i=0; i<len;i++)
            aux[i] = elems [i];

        delete elems;
        elems = aux;
        //cout << "Resize";

    }

/*    Queue[len].first = e;
    Queue[len].second = p;
    len ++;
    bubble_up(len-1);*/

    if(len==0) // daca nu mai am elemente
    {
        p1.first = e;
        p1.second = p; // aici cred ca era o greseala
        
        
        //john gabbana
        elems[len].first = e;
        elems[len].second = p;
        //john gabbana
        

        len ++;

    } else if(len == 1) // daca mai am un element
    {
        if (rel(p1.second, p)) {
            p2.first = e;
            p2.second = p;


            // jg
            elems[len].first = e;
            elems[len].second= p;
            // jg
          


            len ++;
        } else {
            p2.first = p1.first;
            p2.second = p1.second;
            p1.first = e;
            p1.first = p;
            
/*
            //
            Queue[len].first = e;
            Queue[len].second = p;
            //
*/            
            len ++;
        }

/*
        // jg
        Queue[len].first = e;
        Queue[len].second = p;
        // jg
*/  
    }
    else if(len >=2)
    {
        //cout << "unde ma intereseaza\n";
        // cin.get();
        if(rel(p, p1.second))
        {
       //     cout << "1...\n";
            //cin.get();
            elems[poz] = p2;
            p2 = p1;
            p1 = make_pair(e,p);
            len ++;
            poz++;
            bubble_up(poz-1);
        }
        else if(rel(p1.second, p) && rel(p,p2.second))
        {
     //       cout << "2...\n";
            //cin.get();
            elems[poz] = p2;
            p2 = make_pair(e,p);
            len ++;
            poz++;
            bubble_up(poz-1);
        } else if(rel(p2.second, p))
        {
 //           cout << "3...\n";
   //         cout << "pozitie_coada = " << pozitie_coada << '\n';
            //cin.get();
            elems[poz] = make_pair(e,p);
            len ++;
            poz++;
            bubble_up(poz-1);
        }
    }
}

Element ThirdPriorityQueue::top() const {
    if(atMostTwo()) // verific daca am mai putin de 3 elemente
    {
        exception ex;
        throw ex;
    }

   /* if(rel(Queue[0].second,Queue[1].second))
        return Queue[0];
    else if (rel(Queue[1].second, Queue[2].second))
        return Queue[1];
    else
        return Queue[2];*/
    return elems[0];


}

Element ThirdPriorityQueue::pop() 
{
    if(atMostTwo()) // verific daca am mai putin de 3 elemente
    {
        exception ex;
        throw ex;
    }
    Element to_delete;
    to_delete = elems[0];
    elems[0] = elems[poz-1];
    poz --;
    len --;
    bubble_down(0);

    return to_delete;

}

bool ThirdPriorityQueue ::atMostTwo() const 
{
    return len <= 2;
}

ThirdPriorityQueue::~ThirdPriorityQueue() { //destructor
    delete[]elems; // dealoc spatiul pt Queue
}

void ThirdPriorityQueue::afis()
{
    if (len == 0) 
    {  
        cout << " 0 elemente; nu se face nimic \n";  
        return;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        cout << "Queue["<< i << "].first=" << elems[i].first <<  " si " << "Queue["<< i << "].second=" << elems[i].second << '\n';
        // cin.get();
    }
    cout << "========================\n";
}

int ThirdPriorityQueue::getLen()
{
    return len;
}

int ThirdPriorityQueue::get_pozitie_coada()
{
    return poz;
}