#include "Map.h"
#include "MapIterator.h"
//#include <cmath>
//#include <algorithm>
#include <iostream>

using std::cout;
using std::cin;
using std::swap;

/*
worst case = average case = best case = Theta(dim)
Se justifica prin faptul ca se executa o operatie de complexitate O(1) (deci chiar Theta(1)) de `dim` ori
*/
void Map::mark_empty(TElem* tabela, const int& dim)
{
    for (int i = 0; i < dim; i++)
        tabela[i] = NULL_TELEM;
}

/*
worst case = average case = best case = Theta(m)
Se justifica prin faptul ca trebuie mereu sa initializam la "valoarea nula" (in cazul nostru `NULL_TELEM`) container-ul (cele doua sub-containere).
*/
Map::Map() {
	//TODO - Implementation

    /*	
    Am ales `m` prim, dupa sugestia din curs; pentru Divisionsmethode se sugera un
    nr prim care sa nu fie foarte aproape de o putere a lui 2, asa ca l-am ales relativ "la mijloc" intre puteri ale lui 2. 
    Intrucat am vazut in teste ca se adauga destul de multe numere dintr-un range relativ mare, am ales un nr prim relativ mare 
    (dar in acelasi timp nu exagerat, pentru a lasa algoritmul de `rehash_resize` sa intervina si el). `m`-ul ales este garantat 
    prim pentru ca l-am luat dintr-un tabel gasit pe Internet. ("first 1000 prime numbers" pe Wikipedia)
    Cu toate acestea, nu sunt sigur daca am facut bine ca l-am lasat asa de mare; dar, oricum, am tot probat cu diferite valori ale lui `m`, 
    cum ar fi cele comentate mai jos. 
    */

    /*
    m = 23; // de dat mai mare aici? vad mai incolo... 
    m = 23; // este prim si e aproximativ la mijloc, intre 16 si 32
    m = 193; // este prim si e aproximativ la mijloc, intre 124 si 256
    m = 1531; // este prim si e aproximativ la mijloc, intre 1024 si 2048
    m = 6131; // este prim si e aproximativ la mijloc, intre 4096 si 8192
    */

    //m = 1531;   // "capacitatea" container ului
    m = 23;
    len = 0;    // nr de elemente din container

    ht1 = new TElem[m]; mark_empty(ht1, m);
    ht2 = new TElem[m]; mark_empty(ht2, m);

}

// de revenit la comentariul astaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
/*
worst case = O(3m): se vor verifica toate cele 2*m, insa toate elementele existente se afla, deci no short circuit evaluation ( ce vreau sa spun cu asta este ca
a doua conditie din `if` nu va fi omisa vreodata; este evaluata la fiecare pas in cel mai rau caz si chiar despre asta vorbim: cel mai rau caz)
average case = 
best case = Theta(3m) = Theta(m)
Se justifica prin faptul ca: fie ca se afiseaza , fie ca nu, pentru fiecare intreg din intervalul se vor face 2 sau 3 verificari 
*/
void Map::display() const
{

    cout << "========================================================================\n";
    cout << "m = " << m << '\n';
    for (int i = 0; i < m; i++)
    {
        if (ht1[i] != NULL_TELEM || ht2[i] != NULL_TELEM)
        {
            cout << i << ". " <<
                ht1[i].first << " " << ht1[i].second
                << "          " <<
                ht2[i].first << " " << ht2[i].second << '\n';
    //        cin.get();
        }
    }
    cout << "========================================================================\n";
    cin.get(); // ca sa se vada rezultatul pe ecran; apoi, dupa apasarea unei taste oarecare sa se continue executia
}

void Map::apel_display() const
{
    display();
}
///////////////////////////////////////////////////////////////////////////////////////
/*

*/
TValue Map::add(TKey c, TValue v){
	
    TValue rez = search(c);
	if(rez != NULL_TVALUE)      // daca, intr-adevar, exista cheia in container, atunci
    {
        /*
        aceasta este:
        1) fie in prima tabela hash pe pozitia data de functia `h1(c)`
        2) fie in a doua tabela hash pe pozitia data de functia `h2(c)`
        */


        TValue prev; // valoarea precedenta, "previous"
	 
        if(ht1[h1(c)].first == c)       // daca am gasit cheia in prima tabela
        { 
            prev = ht1[h1(c)].second;   // retin intr-o variabila auxiliara valoarea precedenta asociata cheii gasite
            ht1[h1(c)].second = v;      // si modific valoarea asociata cheii gasite
	    } 
        else                            // daca am gasit cheia in a doua tabela
        {
            prev = ht2[h2(c)].second;   // retin intr-o variabila auxiliara valoarea precedenta asociata cheii gasite
            ht2[h2(c)].second = v;      // si modifica valoarea asociata cheii gasite
	    }
        return prev;            // la final, voi returna valoarea precedenta asociata cheii gasite in container, conform specificatiei din interfata data
	}

    // daca nu exista deja cheia in container, vom adauga un nou element in container
    TElem element(c, v);
    
    len++; // in acest caz, actualizam si numarul de elemente!

    /* dc nu merge aici cu varianta asta ?
    // if (len == 2 * (m - 1))     /* in curs se spune ca: fiecare tabela are mai mult de jumatate din pozitii neocupate, deci fiecare tabela
   are maxim ((m - 1) / 2) pozitii ocupate; deci, in total, trebuie sa fie maxim: 2 * ( m - 1 ) pozitii ocupate, cumulat, in cele 2 sub-containere */
//   if(len >= 2 *(m - 1))
    // if(len == 2 * m)    
    if(len == m)    
        resize_rehash();

    int poz1 = h1(c);          // obtin hashwert-ul (pozitia) in tabela 1 al elementului de inserat
	TElem aux = ht1[poz1];   // salvez elementul precedent (in caz ca vom avea un "eviction chain")

    ht1[poz1] = element;        // inseram elementul pe pozitia lui corespunzatoare

	if(aux == NULL_TELEM) return NULL_TVALUE;       // daca elementul precedent a fost elementul nul, atunci il returnam
    else        // altfel, continuam "eviction chain-ul"
    {
	    
	    int poz_start = poz1;         /* retin pozitia de start ( voi avea nevoie de aceasta pentru a verifica daca ne-am lovit de un ciclu, 
        caz in care va fi nevoie de redimensionare & rehash ) */ 
	    
        while(true) /* Stiu ca nu e prea ok aici sa fac asta, dar am mai jos conditii care imi garanteaza ca nu ma voi opri intr-o bucla infinita. 
                    Erau mai multe conditii de verificat si se complica conditia pentru `while`. Am lasat while(true) */
        {

            /*
                La fiecare pas, voi face o mutare in `ht1` si una in `ht2`, daca este posibil. Daca nu, fie am terminat si s-a inserat elementul, fie va fi nevoie de rehash_resize.
            */

	        int poz2 = h2(aux.first);       /* Calculam pozitia pe care ar trebui inserat in tabela 2 elementul scos din tabela 1*/
            
            swap(aux, ht2[poz2]);   /* Il inseram si in acelasi timp obtinem in `aux` un element care acum trebuie inserat in tabela 2*/
	                                                                // and we save the former element, in case it was removed.
            if (aux == NULL_TELEM) return NULL_TVALUE;      // din nou, daca nu am eliminat
            else 
            {
	            // If we have removed an element, ..
	            poz1 = h1(aux.first);          // Calculate where the removed element should be placed
	                                                                   // in the first hashtabelle.
	            swap(aux, ht1[poz1]);   // The removed element is placed where calculated,
	                                                                    // and we save the former element, in case it was removed.
	            if(aux == NULL_TELEM) {
	                // If we haven't removed any element, ..
                    return NULL_TVALUE;
	            } else {
	                if(aux == element && poz_start == poz1) {
	                    // If we have made a complete cycle and came back from where we started,
	                    // it means we have to deal with an infinite loop, so we double the capacity and
	                    // reposition the elements.
    //                    cout << " se face resize la " << c << " " << v << '\n';
	                    resize_rehash();
	                }
	            }
	        }
	    }
	}
//    cout << "dupa add:\n";
  //  display();
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
    if(ht1[h1(c)].first == c) {
	    // If we find the key in the first hashtabelle, we return the value.
        return ht1[h1(c)].second;
	}
	if(ht2[h2(c)].first == c) {
	    // If we find it in the second, ..
        return ht2[h2(c)].second;
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
    int p1 = h1(c), p2=  h2(c);
    if(ht1[p1].first == c) {
        // If we find the key in the first hashtabelle, we return the value and mark the position as empty.
        TValue oldValue = ht1[p1].second;     // save the former value for return
        ht1[p1] = NULL_TELEM;                 // mark the position as empty with NULL_TELEM
        len--;  // update the number of elements
        
        
        // cout << "dupa remove:\n";
        // display();
        

        return oldValue;
    }
    if(ht2[p2].first == c) {
        // If we find it in the second, we return the value and mark the position as empty.
        TValue oldValue = ht2[p2].second;    // save the former value for return
        ht2[p2] = NULL_TELEM;                // mark the position as empty with NULL_TELEM
        len--;                            // update the number of elements

        // cout << "dupa remove:\n";
        // display();


        return oldValue;
    }

    // cout << "dupa remove(nu s a eliminat nimic)!!!!\n";
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

	return len;
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

	return len == 0;
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

 /* 
Observatie: 
1)Functiile astea tin de implementarea PROPRIE! De aceea, nu cred ca trebuie sa am pointeri
la niste functii externe care, eventual, sa fie initializati in constructor 
2) Daca as fi considerat functiile "la fel de triviale", ca in curs (adica cele cu Divisionsmethode dar foarte banale, de genul celei comentate mai jos)
as fi avut probleme pentru ca asa aveam prea multe coliziuni pe pozitia 0 ( mai exact m
sau chiar 2m - 1 coliziuni, incluzand si numerele negative);
concret: facand operatia " k / m " as fi obtinut pentru toate cheile din intervalul deschis (-m, m) 
valoarea zero, deci functia nu ar fi avut distributie aproximativ la fel( cred ca in engleza suna mai bine: 
"even distribution")

 */

int Map::h1(TKey key) const {
    // return (2 * abs(key) + 3) % capacity;
//    return abs(key) % capacity;
    // return (abs(key) + 10) % capacity;
    return (3 * abs(key) + 5) % m;
    // return abs(key) % capacity;
}
int Map::h2(TKey key) const {
    // return 2 * abs(key) % capacity;
//    return (abs(key) / capacity) % capacity;
    //return ( (abs(key) + 10) / capacity ) % capacity;
    return (7 * abs(key) + 9)  % m;
    //return ( abs(key) + 5 )% capacity;
}

/*
Daca e sa consideram functia noastra, drept una bine aleasa, adica una care ne ofera o probabilitate mare
ca "eviction chain ul" nu va fi foarte lung / nu se va intampla des, atunci complexitatea amortizata este:
worst case = average case = best case = Theta(m), deoarece avem `m` operatii de complexitate O(1)
*/
void Map::resize_rehash() {

    std::cout << " s a facut resize !!" << '\n';


    /* ATENTIE! Spre deosebire de alte situatii similare discutate cand a fost vorba de alte ADT uri, aici nu putem actualiza valorea lui `m` 
    la finalul metodei, tocmai pentru ca functiile responsabile de "rehash" depind de `m`, dar !! ATENTIE !! ne trebuie `m`-ul actualizat, evident!
    De aceea, intai actualizam `m`-ul, apoi continuam cu rearanjarea vechilor elemente in noile tabele!
   */

    m *= 2;

    TElem * new_ht1 = new TElem[m]; mark_empty(new_ht1, m);
    TElem * new_ht2 = new TElem[m]; mark_empty(new_ht2, m);

    /* aranjam vechile elemente in noile tabele */
    int lim = m / 2;
    for(int i = 0; i < lim; i++)
    {
        /* stocam elementele pentru care trebuie sa facem "rehashing" in variabile auxiliare */
        TElem e1 = ht1[i];
        TElem e2 = ht2[i];
        
        // Here there is no chance of infinite loops or not enough space.
        if(e1 != NULL_TELEM) /* daca pe pozitia `i` din `ht1` am gasit un element, intr-adevar, atunci: */
        {
            // il adaugam in noua "prima tabela" hash
            
            int poz1 = h1(e1.first);          // calculez "hashwert-ul"
            TElem removed = new_ht1[poz1];    // retin intr-o variabila auxiliara elementul curent "in aer"
            new_ht1[poz1] = e1;               // inserez elementul in locul celui existent deja

            
            if(removed != NULL_TELEM)       // daca elementul tocmai inserat a inlocuit un 
            {
                while(true) 
                {
                    // if we have removed an element, we apply the same algorithm as in the add function
                    int poz2 = h2(removed.first);      // save removed element in second hash
                    swap(removed, new_ht2[poz2]);
                    if(removed != NULL_TELEM) 
                    {
                        break;
                    } else {
                        // if we removed an element, ..
                        poz1 = h1(removed.first);
                        swap(removed, new_ht1[poz1]);   // save removed element in first hash
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
            int poz1 = h1(e2.first);
            TElem removed = new_ht1[poz1];
            new_ht1[poz1] = e2;

            if(removed != NULL_TELEM) {
                while(true) {
                    // if we have removed an element, we apply the same algorithm as in the add function
                    int poz2 =h2(removed.first);       // save removed element in second hash
                    swap(removed, new_ht2[poz2]);
                    if(removed == NULL_TELEM) {
                        break;
                    } else {
                        // if we removed an element, ..
                        poz1 = h1(removed.first);      // save removed element in first hash
                        swap(removed, new_ht1[poz1]);
                        if(removed == NULL_TELEM) {
                            break;
                        }
                    }
                }
            }
        }
    }

    // dealoc spatiul initial alocat pentru cele 2 sub-containere precedente
    delete[] ht1;
    delete[] ht2;

    // actualizez pointerii catre cele 2 sub-containere.
    ht1 = new_ht1;
    ht2 = new_ht2;

}

Map::~Map() {
    //TODO - Implementation

    delete[] ht1;
    delete[] ht2;
}