#include "Map.h"
#include "MapIterator.h"

#include <iostream>
using std::cout; // pt mn pt debugging
using std::abs; // pentru functiile de hash
/*
void Map::afis_tabela(TElem* tabela)
{
	for (int i = 0; i < m; i++)
		cout << "(" << tabela[i].first << ", " << tabela[i].second << ") ";
	cout << '\n';
}
*/
void Map::mark_empty(TElem* tabela)
{
	for (int i = 0; i < m; i++)
		tabela[i] = NULL_TELEM;
}

Map::Map() {
	//TODO - Implementation

//	m = 23; // de dat mai mare aici? vad mai incolo... 
	m = 23; // este prim si e aproximativ la mijloc, intre 16 si 32
	/* 
	am ales `m` prim, dupa sugestia din curs; pentru Divisionsmethode se sugera un
	nr prim care sa nu fie foarte aproape de o putere a lui 2. Intrucat am vazut in teste ca se 
	adauga destul de multe numere dintr-un range relativ mare, am ales un nr prim relativ mare (in acelasi timp nu
	foarte mare, pentru a lasa algoritmul de `rehash_resize` sa intervina si el. este prim pentru ca l-am luat dintr-un
	tabel de pe net. Ini
	*/
	len = 0;

	ht1 = new TElem[m]; mark_empty(ht1);
	ht2 = new TElem[m]; mark_empty(ht2);
	/* Functiile astea tin de implementarea mea! De aceea, nu cred ca trebuie sa am pointeri
	la niste functii externe, care, eventual, sa fie initializati (pointerii la functii)
	in constructor */
}
/*
	functia de hash corespunzatoare primei tabele

	NOTE: 

2)
*/
int Map::f1(TKey k) const { /*return k % m;*/ 
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
int Map::f2(TKey k) const { /*return (k / m) % m;*/
	return(7 * abs(k) + 9) % m;
}

void Map::resize_rehash()
{
	TElem * new_ht1 = new TElem[m * 2]; mark_empty(new_ht1);
	TElem * new_ht2 = new TElem[m * 2]; mark_empty(new_ht2);

	for (int i = 0; i < m; i++)
	{	/* de facut...*/
		
	}

	// dealoc locatia de memorie precedent alocata
	delete[]ht1;
	delete[]ht2;

	// actualizez locatia de memorie catre care pointeaza pointerii ht1, ht2
	ht1 = new_ht1;
	ht2 = new_ht2;

	// actualizez capacitatea containerelor (tabelelor hash)
	m *= 2;
}


TValue Map::add(TKey c, TValue v){
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
	int poz_t1 = f1(c); // pozitie in tabela1
	if (ht1[poz_t1] == NULL_TELEM) { ht1[poz_t1] = TElem(c, v); return NULL_TVALUE; }
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
	int poz_Vizitate* = new int[2 * m + 5];
// 	int poz_precedenta =
	//TElem* tabela = &t1;
	//int poz = f1(c);
	//while( !already_visited(poz) )
	TKey current_key = c;
	do
	{
		int poz_t1 = f1(current_key);
		if (ht1[poz_t1] == NULL_TELEM) { ht1[poz_t1] = ; return NULL_TELEM; }

		current_key = 
		int poz_t2 = f2()

	} while ();

	// return NULL_TVALUE;
}

/*
bool Map::already_visited()
{

}
*/

TValue Map::search(TKey c) const{
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
	int poz1 = f1(c);
	if (ht1[poz1] != NULL_TVALUE) return ht1[poz1].second;

	int poz2 = f2(c);
	if (ht2[poz2] != NULL_TVALUE) return ht2[poz2].second;

	return NULL_TVALUE;
	/* 
	daca initializez la inceput totul cu NULL_TVALUE, al doilea if puteam sa il scriu direct:
	`` return ht2[poz2] `` sau, poate mai clar (poate nu neaparat "clar", dar pedagogic): 
	`` return ht2[poz2] != NULL_TVALUE ? ht2[poz2] : NULL_TVALUE ``
	*/
}

TValue Map::remove(TKey c){
	//TODO - Implementation
	
	TValue to_be_returned;

	int poz1 = f1(c);
	if (ht1[poz1].first == c)
	{
		to_be_returned = ht1[poz1].second;
		// ht1[poz1].second = NULL_TVALUE // daca valoarea e NULL_TVALUE, atunci elementul e NULL_TELEM !!
		ht1[poz1] = NULL_TELEM;
		len--;
		return to_be_returned;
	}

	/*
	Ce se intampla daca intra pe ambele if uri? NU va intra pe ambele if uri; in map
	nu se repeta cheile! (valorile poate da...)
	*/

	int poz2 = f2(c);
	if (ht2[poz2].first == c)
	{
		to_be_returned = ht2[poz2].second;
		ht2[poz2] = NULL_TELEM; /* as fi putut la fel de bine sa pun pe rand: 
		``ht2[poz2].first = NULL_TKEY`` , respectiv ``ht2[poz2].second = NULL_TVALUE``
		*/
		len--;
		return to_be_returned;
	}

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
	return MapIterator(*this);
}

Map::~Map() {
	//TODO - Implementation
	delete[]ht1;
	delete[]ht2;
}