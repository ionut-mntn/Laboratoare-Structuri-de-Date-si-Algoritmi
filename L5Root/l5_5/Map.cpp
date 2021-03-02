#include "Map.h"
#include "MapIterator.h"

#include <iostream>
using std::cout; // pt mn pt debugging
using std::cin; // pt mn pt debugging
using std::abs; // pentru functiile de hash
/*
void Map::afis_tabela(TElem* tabela)
{
	for (int i = 0; i < m; i++)
		cout << "(" << tabela[i].first << ", " << tabela[i].second << ") ";
	cout << '\n';
}
*/


void Map::mark_empty(TElem* tabela, const int &dim)
{
	for (int i = 0; i < dim; i++)
		tabela[i] = NULL_TELEM;
}


Map::Map() {
	//TODO - Implementation

//	m = 23; // de dat mai mare aici? vad mai incolo... 
	// m = 23; // este prim si e aproximativ la mijloc, intre 16 si 32
	// m = 1531; // este prim si e aproximativ la mijloc, intre 16 si 32
	// m = 6131; // este prim si e aproximativ la mijloc, intre 16 si 32
	
	// m = 6133; // este prim si e aproximativ la mijloc, intre 16 si 32
	
	
	m = 31; // este prim si e aproximativ la mijloc, intre ... si ... !!
	// m = 13;
			
	/* 
	am ales `m` prim, dupa sugestia din curs; pentru Divisionsmethode se sugera un
	nr prim care sa nu fie foarte aproape de o putere a lui 2. Intrucat am vazut in teste ca se 
	adauga destul de multe numere dintr-un range relativ mare, am ales un nr prim relativ mare (in acelasi timp nu
	foarte mare, pentru a lasa algoritmul de `rehash_resize` sa intervina si el. este prim pentru ca l-am luat dintr-un
	tabel de pe net. Ini
	*/
	len = 0;

	ht1 = new TElem[m]; mark_empty(ht1, m);
	ht2 = new TElem[m]; mark_empty(ht2, m);
	/* Functiile astea tin de implementarea mea! De aceea, nu cred ca trebuie sa am pointeri
	la niste functii externe, care, eventual, sa fie initializati (pointerii la functii)
	in constructor */
}
/*
	functia de hash corespunzatoare primei tabele

	NOTE: 

2)
*/
int Map::h1(TKey k) const { /*return k % m;*/ 
	// return abs(k) % m;
	return (3 * abs(k) + 5) % m; // presupun ca nu intra in discutie cazuri precum: o sa vina altcineva care sa trebuiasca sa duca mai departe codul si sa se apuce sa dea lui m valoarea 1 sau 0 sau chestii de genul
} // ! sa nu te nedumereasca: TKey e doar un int!

/*
	Nota:
daca as fi considerat si a doua functie "la fel de triviala", ca in curs (de genul celei comentate mai jos)
as fi avut probleme pentru ca asa aveam prea multe coliziuni pe pozitia 0 ( mai exact m
sau chiar 2m - 1 , incluzand si numerele negative);
concret: facand operatia " k / m " as fi obtinut pentru toate cheile din intervalul deschis (-m, m) 
valoarea zero, deci functia nu ar fi avut distributie aproximativ la fel( cred ca in engleza suna mai bine: 
"even distribution")

*/
int Map::h2(TKey k) const { /*return (k / m) % m;*/
	//return (abs(k) + 5) % m;
	return(7 * abs(k) + 9) % m;
}

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
			// cin.get();
		}
	}
	cout << "========================================================================\n";
	cin.get();
}

void Map::apel_display() const
{
	display();
}

void Map::resize_rehash() {
	// COMPLEXITY:
	// 1. overall (best/average/worst case): o(n), since every element must be repositioned.

	std::cout << " s a facut resize !!" << '\n';

	m <<= 1;                     // double the capacity

	auto aux1 = new TElem[m];    // allocate the doubled space for the hashtabelles
	auto aux2 = new TElem[m];

	for (int current = 0; current < m; current++) {
		// Initialized the space with NULL_TELEM to mark it as empty.
		aux1[current] = aux2[current] = NULL_TELEM;
	}

	for (int current = 0; current < m >> 1; current++) {
		// We take every element from the 2 arrays in order to reposition them in the new ones.
		TElem e1 = ht1[current], e2 = ht2[current];    // elements to be repositioned

		// Here there is no chance of infinite loops or not enough space.
		if (e1 != NULL_TELEM) {
			// If there is an element, we add it.
			int p1 = h1(e1.first);       // place in fist hashtabelle
			TElem removed = aux1[p1];
			aux1[p1] = e1;

			if (removed != NULL_TELEM) {
				while (true) {
					// if we have removed an element, we apply the same algorithm as in the add function
					int p2 = h2(removed.first);      // save removed element in second hash
					std::swap(removed, aux2[p2]);
					if (removed == NULL_TELEM) {
						break;
					}
					else {
						// if we removed an element, ..
						p1 = h1(removed.first);
						std::swap(removed, aux1[p1]);   // save removed element in first hash
						if (removed == NULL_TELEM) {
							break;
						}
					}
				}
			}
		}

		// ANALOG ^
		if (e2 != NULL_TELEM) {
			// if the position wasn't empty, ..
			int p1 = h1(e2.first);
			TElem removed = aux1[p1];
			aux1[p1] = e2;

			if (removed != NULL_TELEM) {
				while (true) {
					// if we have removed an element, we apply the same algorithm as in the add function
					int p2 = h2(removed.first);       // save removed element in second hash
					std::swap(removed, aux2[p2]);
					if (removed == NULL_TELEM) {
						break;
					}
					else {
						// if we removed an element, ..
						p1 = h1(removed.first);      // save removed element in first hash
						std::swap(removed, aux1[p1]);
						if (removed == NULL_TELEM) {
							break;
						}
					}
				}
			}
		}
	}

	// deallocate the former space.
	delete[] ht1;
	delete[] ht2;

	// update.
	ht1 = aux1;
	ht2 = aux2;
}


TValue Map::add(TKey k, TValue v){
	//TODO - Implementation

	/* 
	if(l == ) // cred ca aici fac resize & rehash
	doar daca am ciclu infinit (nuj daca sa mai tin variabila ai `l`)
	momentan o las deoparte 
	*/


	/*
		Cum ramane complexitatea log n aici, daca, in cel mai rau caz:
		facem o cautare prin toate cele m pozitii? ( avem 2 * m pozitii, dar s-a zis
		in curs ca cele 2 tabele hash au mai mult de [m/2] pozitii libere)
		
		Raspuns: Dupa cum scrie in curs, 
		
		faptul ca avem un factor de ocupare de maxim
		0.5 si doua functii bine alese ( sper ca le-am ales bine, pentru ca le-am 
		luat triviale, ca in curs ) ne asigura ca: 
		1) e putin probabil ca mai mult de O(log n) elemente sa fie mutate
		2) probabilitatea de a intalni un ciclu infinit este mica
	*/

	TValue searchValue = search(k);     // search if the key exists (or not)
	if (searchValue != NULL_TVALUE) {
		// If the key already exists, we modify its value.
		// A key can only exist on 2 calculated positions in the two hashtabelles.
		TValue oldValue;
		if (ht1[h1(k)].first == k) {
			// If the key is in the first hashtabelle, ..
			oldValue = ht1[h1(k)].second;      // save former value in order to return
			ht1[h1(k)].second = v;             // modify former value
		}
		else {
			// If the key is in the second hashtabelle, ..
			oldValue = ht2[h2(k)].second;     // save former value in order to return
			ht2[h2(k)].second = v;            // modify former value
		}
		return oldValue;
	}

	// If we reach this point, the value didn't already exist, so we have to add it.
	TElem element = std::make_pair(k, v);       // save the element
	len++;                            // update the number of elements
	if (len == m) {
		// The hashtabelles are half empty, so we have to verify if the number of elements reaches the capacity,
		// and not its doubled value.
		// resize + rehash
//		cout << " se face resize la " << k << " " << v << '\n';
		resize_rehash();
	}

	int poz1 = h1(k);       // calculate where the element should be added
	TElem removed = ht1[poz1];   // save the former element, in case there was one

	ht1[poz1] = element;         // put the element where we calculated

	if (removed == NULL_TELEM) {
		// If no value was removed, ..
		return NULL_TVALUE;
	}
	else {
		// If a value was removed, we have to reposition it.
		int startPoint = poz1;         // saving the starting point in case of an infinite cycle
		while (true) {
			// I put true since there are multiple factors and conditions for the algorithm to stop.
			// For simplicity, I verify both hashtabelles in one loop.

			int poz2 = h2(removed.first);       // Calculate where the removed element should be placed
																	// in the second hashtabelle.
			std::swap(removed, ht2[poz2]);   // The removed element is placed where calculated,
																	// and we save the former element, in case it was removed.
			if (removed == NULL_TELEM) {
				// If we haven't removed any element, ..
				return NULL_TVALUE;
			}
			else {
				// If we have removed an element, ..
				poz1 = h1(removed.first);          // Calculate where the removed element should be placed
																	   // in the first hashtabelle.
				std::swap(removed, ht1[poz1]);   // The removed element is placed where calculated,
																		// and we save the former element, in case it was removed.
				if (removed == NULL_TELEM) {
					// If we haven't removed any element, ..
					return NULL_TVALUE;
				}
				else {
					if (removed == element && startPoint == poz1) {
						// If we have made a complete cycle and came back from where we started,
						// it means we have to deal with an infinite loop, so we double the capacity and
						// reposition the elements.
						// cout << " se face resize la " << k << " " << v << '\n';
						resize_rehash();
					}
				}
			}
		}
	}

	////int poz_t1 = f1(c); // pozitie in tabela1
	///if (ht1[poz_t1] == NULL_TELEM) { ht1[poz_t1] = TElem(c, v); return NULL_TVALUE; }
	/*
	else
	{
*/
/*
		int poz_initiala2 = f2[c];
		if (ht2[poz_initiala2] == NULL_TELEM) ht2[poz_initiala2] = TElem(c, v);
		else
		{
			int poz_vizitate[m + 10]; /* in curs scrie ca cele doua tabele hash au maxim:
			[m/2] elemente -aici era un comentariu inchis-//
			poz_vizitate[0] = poz_initiala1;
			poz_vizitate[1] = poz_initiala2;
			int poz = 
			while()

		}
*/
	/*
		int poz_t2 = f2(c);
		if (ht2[poz_t2] == NULL_TELEM) ht2[poz_t2] = TElem(c, v);
	

	}
*/
	/*
	int poz_vizitate[m + 10] = {}; // declar un array si pun pe prima 
	int poz = f2(c);
	while(poz != )
	*/


//	int poz_vizitate[2 * m + 5] = {}; // initializez un array de zerouri (nuj daca e "declar" sau "initializez" )
	
//int poz_Vizitate* = new int[2 * m + 5];

// 	int poz_precedenta =
	//TElem* tabela = &t1;
	//int poz = f1(c);
	//while( !already_visited(poz) )
/*
	TKey current_key = c;
	do
	{
		int poz_t1 = f1(current_key);
		if (ht1[poz_t1] == NULL_TELEM) { ht1[poz_t1] = ; return NULL_TELEM; }

		current_key = 
		int poz_t2 = f2()

	} while ();
*/
	// return NULL_TVALUE;

//	cout << "Dupa add:\n";
	// display();
}

/*
bool Map::already_visited()
{

}
*/

TValue Map::search(TKey k) const{
	//TODO - Implementation

	/*
	ATENTIE! Daca un element exista intr-unul din cele 2 tabele, atunci cu siguranta exista
	pe una dintre cele 2 pozitii posibile, date de functiile corespunzatoarei primei,
	respectiv celei de a doua tabele. (initial am crezut ca atunci cand se impinge un
	element dintr-o tabela in alta, este posibil ca acel element impins sa ajunga pe o
	pozitie diferita 
	
	(de exemplu, cand un element se intoarce din tabela2 in tabela1, aces-
	ta sa fie introdus pe o pozitie diferita decat anterioara din tabela1 pe care a fost 
	inserata)
	
	de ce returneaza f1(elem) sau f2(elem), DAR (acum cred ca) EXACT ASTA E PRINCIPIUL 
	CUCKOO HASHING!)
	*/
	int poz1 = h1(k);
	if (ht1[poz1].first == k) return ht1[poz1].second;

	int poz2 = h2(k);
	if (ht2[poz2].first == k) return ht2[poz2].second;

	return NULL_TVALUE;
	/* 
	daca initializez la inceput totul cu NULL_TVALUE, al doilea if puteam sa il scriu direct:
	`` return ht2[poz2] `` sau, poate mai clar (poate nu neaparat "clar", dar pedagogic): 
	`` return ht2[poz2] != NULL_TVALUE ? ht2[poz2] : NULL_TVALUE ``
	*/
}

TValue Map::remove(TKey c){
	//TODO - Implementation
	
	// !! elementul cu cheia `c` poate fi gasit doar in una din cele 2 pozitii (daca exista) !!

	TValue to_be_returned;

	int poz1 = h1(c);
	if (ht1[poz1].first == c)
	{
		to_be_returned = ht1[poz1].second;
		// ht1[poz1].second = NULL_TVALUE // daca valoarea e NULL_TVALUE, atunci elementul e NULL_TELEM !!
		ht1[poz1] = NULL_TELEM;
		len--;

//		cout << "Dupa add:\n";
	//	display();

		return to_be_returned;
	}

	/*
	Ce se intampla daca intra pe ambele if uri? NU va intra pe ambele if uri; in map
	nu se repeta cheile! (valorile poate da...)
	*/

	int poz2 = h2(c);
	if (ht2[poz2].first == c)
	{
		to_be_returned = ht2[poz2].second;
		ht2[poz2] = NULL_TELEM; /* as fi putut la fel de bine sa pun pe rand: 
		``ht2[poz2].first = NULL_TKEY`` , respectiv ``ht2[poz2].second = NULL_TVALUE``
		*/
		len--;

//		cout << "Dupa add:\n";
	//	display();

		return to_be_returned;
	}

//	cout << "Dupa add( nu s-a eliminat nimic)!!!\n";
//	display();


	return NULL_TVALUE;
}


int Map::size() const {
	//TODO - Implementation

	return len;

	//	return 0;
}

bool Map::isEmpty() const{
	//TODO - Implementation
	
	return len == 0;
	
	// return false;
}

MapIterator Map::iterator() const {
//	cout << "merge constructoru!!!!\n";
	return MapIterator(*this);
}

Map::~Map() {
	//TODO - Implementation
	delete[]ht1;
	delete[]ht2;
}