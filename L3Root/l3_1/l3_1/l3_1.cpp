// l3_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include "Queue.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

#define Nmax 25

using std::vector;
using std::cin;
using std::cout;

bool solution(int i, int j, int n, int m)
{
	return i == 0 || i == n - 1 || j == 0 || j == m - 1;
	// prima si ultima linie reprezinta iesiri din labirint, respectiv prima si ultima coloana
	// (conform cerintei)
}

bool valid(int i, int j, int n, int m)
{
	return 0 < i && i < n && 0 < j && j < m;
}

// se putea si cu 2 vectori de deplasare, dar am ales sa scriu 4 if uri
/*
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
*/
// siruri pentru deplasare in plan
// am implementat DFS(Depth Field Search), adica odata ce am gasit o pozitie valida, deplasandu-ma intr-o anumita directie,
// voi continua sa ma deplasez in aceeasi directie pana

bool gaseste_cai(bool mat[][Nmax], int i, int j, int n, int m, vector<Queue>* queues);

vector<Queue> gaseste_cai(bool mat[][Nmax], int i_start, int j_start);
/*
{
	vector<Queue>* queues = new vector<Queue>; // linia asta de cod spune: rezerva-mi spatiu pentru un obiect de tip `vector<Queue>` si returneaza-mi
	// pointer catre adresa de memorie unde ai rezervat acest spatiu; (daca se depaseste cat s-a alocat, abstract data type-ul asta `vector` va avea
	// grija sa dealoece si sa realoce memorie suficienta, pentru ca e implementat pe un dynamic array
	while (gaseste_cale())		// cat timp gasesti cai, continua sa cauti ( se va incepe mereu de la pozitia de start, dar voi avea grija
		// in functia `gaseste_cale` ca, pe parcurs, in momentul in care gasesc o cale, sa marchez cu 1 pozitia de iesire din matrice!!
	{

	}
}
*/

void afis_mat(bool mat[][Nmax], int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << mat[i][j] << '\n';
		cout << '\n';
	}
}

void gaseste_cai(bool mat[][Nmax], int i, int j, int n, int m, vector<Queue> *queues) // linia si coloana pozitiei de start din labirint
// pointer vs referinta !!

{
	if (solution(i, j, n, m))
	{
		//queues.push_back(queue);

		mat[i][j] = 1;		// 1 inseamna obstacol;

		queues->push_back(queue);
		//return true;
		return;
	}
	else
	{
		// adaug in coada pozitia curenta pe care ma aflu
		q.push(pozitie_plan{ i, j }); // era vreo diferenta daca scriam `push(pozitie_plan{i, j});` ?
		// de ce aici nu merge `q.push(pozitie_plan(i, j));` ?
		// si contorizez ca am trecu prin pozitia respectiva		

		mat[i][j] = 1; // marchez pozitia curenta ca obstacol, ca sa nu ma blochez intr-o bucla infinita, cum ar fi cazul matricii: 
		/*
		1 1 1 1
		1 0 R 1			// R(obotzelul) s-ar bloca miscandu-se de dreapta la stanga, apoi inapoi la dreapta si tot asa... asta daca nu marchez o pozitie 
		1 1 1 1			// vizitata !
		1 1 1 1
		*/

		/*
		1 1 1 1 1 1 1 1
		1 1 1 1 1 1 1 1
		1 1 1 1 R 1 1 1
		1 1 1 1 0 1 1 1
		1 1 1 0 0 0 1 1
		1 1 1 0 1 0 1 1
		1 1 1 0 1 0 1 1
		1 1 1 0 1 0 1 1


		1 1 1 1 0 1 0 1
		1 1 1 1 0 0 0 1
		1 1 1 1 1 0 1 1
		1 1 0 0 0 0 1 1
		1 1 0 1 1 1 1 1
		1 1 0 R 1 1 1 1
		1 1 1 1 1 1 1 1
		1 1 1 1 1 1 1 1		
		

		1 1 1 1 1 1 1 1
		1 1 1 1 1 1 1 1
		1 1 1 1 R 1 1 1
		1 1 1 1 0 1 1 1
		1 1 1 0 0 0 1 1
		1 1 1 0 1 0 1 1
		1 1 1 0 1 0 1 1
		1 1 1 0 1 0 1 1

		*/
		if (valid(i - 1, j, n, m))
			gaseste_cai(mat, i - 1, j, n, m, q);

		if (valid(i, j + 1, n, m))
			gaseste_cai(mat, i, j + 1, n, m, q);
		
		if (valid(i + 1, j, n, m))
			gaseste_cai(mat, i + 1, j, n, m, q);
		
		if (valid(i, j - 1, n, m))
			gaseste_cai(mat, i, j - 1, n, m, q);
	}
	return false;		// da, fiindca e o functie recursiva, se va returna de mai multe ori false "pe intoarcere"
	// dar, oricum ma intereseaza numai ce returneaza la final(adica primul apel al functie, cel din `gaseste_cai` nu unul dintre multele apeluri recursive)
}

int main()
{
/*
	testAll();
	testAllExtended();
	cout << "All tests passed\n";
*/
	// testele nu mai merg, pentru ca am modificat structura
	// tipului de date `NodeDLL` Info nu mai este de tip elem, 
	// ci este de tip `pozitie_plan`, unde `pozitie_plan` este
	// un tip de date definit de mine ( are ca atribute:index linie, 
	//coloana )

	
	bool mat[Nmax][Nmax];

	int nr_linii, nr_coloane;
	cin >> nr_linii >> nr_coloane;

	int linie_start, coloana_start;
	cin >> linie_start >> coloana_start;
	
	Queue cale;

	/*
	if (gaseste_cale(mat, linie_start, coloana_start, nr_linii, nr_coloane))
		cale.toString();
	else cout << "Nu exista cale de iesire din labirint!";
	*/

	
	/*
	Queue proba;
	// queue.push(pozitie_plan(1, 2));	// asta nu merge din cauza a ceva
	//proba.push(pozitie_plan q = pozitie_plan(1, 2));
	// pozitie_plan()
	// chestii: initialization list si copy constructor - related
	proba.push(pozitie_plan{ 1,2 });
	proba.push(pozitie_plan{ 3,4 });
	proba.push(pozitie_plan{ 5,6 });
	proba.push(pozitie_plan{ 99,87 });
	proba.toString();
	proba.pop();
	proba.pop();
	proba.toString();
	*/

	return 0;
}
