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

    //m = 23;
    
    m = 11;

    // m = 1531;   // "capacitatea" container ului
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
    if(len == m) resize_rehash();

    int poz1 = h1(c);           // obtin hashwert-ul (pozitia) in tabela 1 al elementului de inserat
    TElem aux = ht1[poz1];      // salvez elementul precedent (in caz ca vom avea un "eviction chain")

    ht1[poz1] = element;        // inseram elementul pe pozitia lui corespunzatoare

	if(aux == NULL_TELEM) return NULL_TVALUE;       // daca elementul precedent a fost elementul nul, atunci il returnam
    else        // altfel, continuam cu "eviction chain-ul"
    {
	    
	    int poz_start = poz1;         /* retin pozitia de start ( voi avea nevoie de aceasta pentru a verifica daca ne-am lovit de un ciclu, 
        caz in care va fi nevoie de redimensionare & rehash ) */ 
	    
        while(true) /* Stiu ca nu e prea ok aici sa fac asta, dar am mai jos conditii care imi garanteaza ca nu ma voi opri intr-o bucla infinita. 
                    Erau mai multe conditii de verificat si se complica conditia pentru `while`. Am lasat while(true) */
        {

            /*
                La fiecare pas, voi face o mutare in `ht1` si una in `ht2`, daca este posibil. Daca nu, fie am terminat si s-a inserat elementul, fie va fi nevoie de `rehash_resize`.
            */

	        int poz2 = h2(aux.first);       /* Calculam pozitia pe care ar trebui inserat in tabela 2 elementul scos din tabela 1*/
            
            swap(aux, ht2[poz2]);   /* Il inseram si in acelasi timp obtinem in `aux` elementul care trebuie acum inserat in tabela 2 */

            if (aux == NULL_TELEM) return NULL_TVALUE;      // din nou: daca elementul precedent a fost elementul nul, atunci il returnam
            else    // atlfel, continuam cu "eviction chain-ul"
            {
	            poz1 = h1(aux.first);          // obtin hashwert-ul (pozitia) in tabela 1 al elementului de inserat
	            swap(aux, ht1[poz1]);   /* Il inseram si in acelasi timp obtinem in `aux` elementul care trebuie acum inserat in tabela 2 */
	                                                                    // and we save the former element, in case it was removed.
	            if(aux == NULL_TELEM) return NULL_TVALUE; // din nou: daca elementul precedent a fost elementul nul, atunci il returnam
	            else 
                { // altfel
                    if (aux == element && poz_start == poz1) /* Daca am ajuns din nou pe pozitia de la care am plecat, DAR ATENTIE!:
                                                            am ajuns: SI de la pozitia de la care am plecat SI cu acelasi element de inserat => ciclu => trebui sa facem resize & rehash
                                                            */
                        resize_rehash();
	            }
	        }
	    }
	}
//    cout << "dupa add:\n";
  //  display();
}

/*
worst case = average case = best case = Theta(1), deoarece sunt doar 2 apeluri de functii alese de noi, functii pentru care timpul de calcul este O(1), deci chiar Theta(1) (am putea spune "instantaneu")
*/
TValue Map::search(TKey c) const
{

    /*
    ATENTIE! Daca un element exista intr-unul din cele 2 tabele, atunci cu siguranta exista
    pe una dintre cele 2 pozitii posibile, date de functiile corespunzatoarei primei,
    respectiv celei de a doua tabele. 
    
    //
    (initial am crezut ca atunci cand se impinge un
    element dintr-o tabela in alta, este posibil ca acel element impins sa ajunga pe o
    pozitie diferita, 
    (de exemplu, cand un element se intoarce din tabela2 in tabela1, aces-
    ta sa fie introdus pe o pozitie diferita decat anterioara din tabela1 pe care a fost
    inserata)
    de ce returneaza f1(elem) sau f2(elem), 
    //
    
    DAR (acum cred ca) EXACT ASTA E PRINCIPIUL
    CUCKOO HASHING!)
    */
    int poz1 = h1(c);
    if (ht1[poz1].first == c) return ht1[poz1].second;

    int poz2 = h2(c);
    if (ht2[poz2].first == c) return ht2[poz2].second;

    return NULL_TVALUE;
    /*
    daca initializez la inceput totul cu NULL_TVALUE, al doilea if puteam sa il scriu direct:
    `` return ht2[poz2] `` sau, poate mai clar (poate nu neaparat "clar", dar pedagogic):
    `` return ht2[poz2] != NULL_TVALUE ? ht2[poz2] : NULL_TVALUE ``
    */
}

/*
    worst case = average case = best case = Theta(1), deoarece avem doar 
*/
TValue Map::remove(TKey c){

    TValue to_be_returned;

    int poz1 = h1(c);
    if (ht1[poz1].first == c)   // daca am gasit cheia in prima tabela
    {
        to_be_returned = ht1[poz1].second;  // retin intr-o variabila auxiliara ceea ce trebuie returnat (conform interfetei date)
        ht1[poz1] = NULL_TELEM;     // marchez pozitia drept "libera"
        len--;         // actualizez lungimea (nr de elemente ale) container-ului

        return to_be_returned;
    }

    /*
    Ce se intampla daca intra pe ambele if uri? NU va intra pe ambele if uri; in map
    nu se repeta cheile! (valorile poate da...)
    */

    int poz2 = h2(c);
    if (ht2[poz2].first == c)   // daca am gasit cheia in a doua tabela
    {
        to_be_returned = ht2[poz2].second;  // retin intr-o variabila auxiliara ceea ce trebuie returant (conform interfetei date)
        ht2[poz2] = NULL_TELEM;     // marchez pozitia drept "libera"
        /* obs: as fi putut la fel de bine sa pun pe rand:
        ``ht2[poz2].first = NULL_TKEY`` , respectiv ``ht2[poz2].second = NULL_TVALUE``
        */
        len--; // actualizez lungimea (nr de elemente ale) conatiner-ului

        return to_be_returned;
    }

    /* cout << "dupa remove(nu s a eliminat nimic)!!!!\n";
    display(); */

    /* Daca nu s-a gasit elementul, returnam elementul nul, conform interfetei date */
    return NULL_TVALUE;
}

/*
worst case = average case = best case = Theta(1)
*/
int Map::size() const 
{
	return len;
}

/*
worst case = average case = best case = Theta(1)
*/
bool Map::isEmpty() const
{
	return len == 0;
}

/*
Atentie! Complexitatea acestei metoide depinde, dupa cum se vede, de complexitatea constructorului `MapIterator`, 
care la randul sau depinde de metoda `first` din clasa MapIterator.
Astfel:
worst case = O(m) - primul element din container fie nu exista, fie este chiar pe ultima pozitie din al doilea sub-container 
average case = O(m)
best case = Omega(1), deci chiar: Theta(1) - in cel mai bun caz
*/
MapIterator Map::iterator() const 
{
	return MapIterator(*this);
}


 /* 
Observatie (mai mult pentru mine): 
1)Functiile astea tin de implementarea PROPRIE! De aceea, nu cred ca trebuie sa am pointeri
la niste functii externe care, eventual, sa fie initializati in constructor 
2) Daca as fi considerat functiile ca in curs, adica:
    a) h1(k) = k % m;
    b) h2(k) = ( k / m ) % m;
as fi avut probleme, pentru ca asa aveam prea multe coliziuni pe pozitia 0 ( mai exact m
sau chiar 2m - 1 coliziuni, incluzand si numerele negative );
concret: facand operatia " k / m " as fi obtinut pentru toate cheile din intervalul deschis (-m, m) 
valoarea zero, deci functia nu ar fi avut "even distribution" prin urmare n-ar fi fost o functie buna de hash 
*/

int Map::h1(TKey key) const { return (3 * abs(key) + 5) % m; }
int Map::h2(TKey key) const { return (7 * abs(key) + 9)  % m; }

//////////////////////////////////////////////////////////////////////////////////////////de revenit aici!!
/*
Daca e sa consideram functia noastra, drept una bine aleasa, adica una care ne ofera o probabilitate mare
ca "eviction chain-ul" nu va fi foarte lung / nu se va intampla des, atunci complexitatea amortizata este:

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
        
        // !! Mai jos voi aplica un algoritm similar cu cel din metoda `add` !!


        if(e1 != NULL_TELEM) /* daca pe pozitia `i` din `ht1` am gasit un element, intr-adevar, atunci: */
        {
            // il adaugam in noua "prima tabela" hash
            
            int poz1 = h1(e1.first);          // calculez "hashwert-ul"
            TElem removed = new_ht1[poz1];    // retin intr-o variabila auxiliara elementul curent "in aer"
            new_ht1[poz1] = e1;               // inserez elementul in locul celui existent deja

            
            if(removed != NULL_TELEM)       // daca elementul tocmai inserat a inlocuit un element deja existen si nu valoare nula, atunci:
            {   
                while(true) 
                {
                    
                    int poz2 = h2(removed.first);
                    swap(removed, new_ht2[poz2]);
                    if(removed == NULL_TELEM) 
                    {
                        poz1 = h1(removed.first);
                        swap(removed, new_ht1[poz1]);
                        if (removed == NULL_TELEM) {
                            break;
                        }

                    }
                    else 
                    {
                        break;
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

            if(removed != NULL_TELEM) 
            {
                while(true) 
                {
                    // if we have removed an element, we apply the same algorithm as in the add function
                    int poz2 =h2(removed.first);       // save removed element in second hash
                    swap(removed, new_ht2[poz2]);
                    if(removed != NULL_TELEM) 
                    {
                    
                        // if we removed an element, ..
                        poz1 = h1(removed.first);      // save removed element in first hash
                        swap(removed, new_ht1[poz1]);
                        if (removed == NULL_TELEM) 
                        {
                            break;
                        }
                    } 
                    else 
                    {
                        break;
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