#include "Map.h"
#include "MapIterator.h"
#include <exception>
#include <iostream>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation
	// cout << "merge constructorul 2222 !!!\n";
	parcurs_ht1 = false;
	// cout << "merge constructorul 3333 !!!\n";
	first(); // vrem sa ne aflam pe pozitie valida chiar de la inceput, deci
	// apelam `first` ( `poz` mi se va schimba in `first` )
	// cout << "merge constructorul 4444!!!\n";
}

//void MapIterator::find_next_container()

//void MapIterator::find_next_subcontainer(const TElem *ht, int &poz)// tabela si variabila (indexul) de incrementat
void MapIterator::find_next(const TElem *ht, int &poz)// tabela si variabila (indexul) de incrementat
{
//	while (poz < m && ht1[poz] == NULL_TELEM) poz++;

	while (poz < map.m && ht[poz] == NULL_TELEM) poz++;
	if (poz < map.m) return;
	poz = -1;
}


// atentie! Intr un map nesortat nu conteaza ordinea!
void MapIterator::first() {
	//TODO - Implementation
	
	// ma voi pozitiona pe prima pozitie din cele doua tabele (
	poz = 0;
	

//	find_next(ht1, p);
	//if()
	
	find_next(map.ht1, poz);
	if (poz != -1) return;

	// daca poz nu e diferit de -1, inseamna ca trebuie sa caut in al doilea container

	parcurs_ht1 = true;

	find_next(map.ht2, poz);
	if (poz != -1) return;

	// daca poz nu e diferit de -1, inseamna ca am parcurs tot containerul si nu am gasit element

	// exception e; throw e;  // trebuie sau nu trebuie aruncata exceptie aici ???????????

	/* e gol ( as fi putut trata la inceput, folosindu-ma de metoda `isEmpty` 
din atributul `m` de tip Map dar, privit din ansamblu: in majoritatea cazurilor nu o sa fie gol container ul, 
asa ca nu vreau sa tot fac verificarea `isEmpty` de multe ori degeaba, in detrimentul verificarilor care 
chiar au sens
	*/

/*
	if (poz < m) return;
	else { poz = 0; parcurs_ht1 = true; }

	while (poz < m && ht2[poz] == NULL_TELEM) poz++;
*/	
}

const Map & MapIterator::getMap() { return map; }

void MapIterator::next() { // nu ar fi trebuit sa arunce exceptie daca nu am niciun element? 
// Vad ca in teste nu asteapta nicaeri ceva de genul cu un try-except sau altfel, deci... daca
// asa se cere prin interfata, nu ma complic
	//TODO - Implementation
	// cout << "poz = " << poz << '\n';
	if (valid())
	{
		// cout << "intra totusi\n";
		poz++;
		// try 
		//{ 
			find_next(map.ht1, poz); 
			if (poz != -1) return;
			// cout << "poz = " << poz << '\n';
			find_next(map.ht2, poz);
			if (poz != -1) return;
			// cout << "poz = " << poz << '\n';
		
			//cout << "arunca exceptie\n!";  exception e; throw e;
		//}
		// catch (exception& e) { cout << "arunca exceptie\n!"; throw e; }
	}
	else
	{
//		cout << "De aici arunca exceptia!\n";
		exception e;
		throw e;

	}	//////////////////////////////////////////////////////////////////////////////// 
	// aici daca de ceva !!
}


TElem MapIterator::getCurrent(){
	//TODO - Implementation

	if (valid())
	{
	//	cout << "Este valid; pozitia curenta este: " << poz << '\n';
		if (!parcurs_ht1) {
		//cout << "return pe prima ramura\n";  
			return map.ht1[poz];
		}
		//cout << "return pe a doua ramura\n";
		return map.ht2[poz];
	}
	else
	{
//		cout << "NU ESTE VALID! valoare = " << poz << '\n';
	}
	//cout << "De aici arunca exceptie_222 !!!\n";
	exception e; throw e;
	// return NULL_TELEM;
}


bool MapIterator::valid() const {
	//TODO - Implementation
//	cout << "!!!! poz = " << poz << '\n';
	return poz != -1 && poz < map.m; // o sa am eu grija sa ... ? sa ce ?
	
	// return false;
}



