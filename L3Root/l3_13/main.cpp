#include <iostream>
#include <vector>
#include "Queue.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

#define Nmax 25

using std::cin;
using std::cout;
using std::vector;
using std::swap;

#include <fstream>
using std::ifstream;
using std::ofstream;

/* worst case = average case = best case = Teta(1)
( nu stiu sigur cum ar trebui sa calculez complexitatea pentru ceva ce tine de user aici...
cred ca nu ar trebui sa se puna problema complexitatii intr un astfel de caz, dar nu sunt sigur...)
la fel si pentru celelalte functii de mai jos care asteapta input pentru utilizator)
*/
template<typename T>
void citeste_mat(ifstream &input_stream, T mat[][Nmax], int &n, int &m)
{
	input_stream >> n >> m;	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			input_stream >> mat[i][j];
}

/* worst case = average case = best case = Teta(1)*/
void citeste_poz_start(ifstream &input_stream, U &p)
{
	input_stream >> p.i >> p.j;
	// p.dist = 0;
	p.i--; p.j--;				// utilizatorul vede in indexare de la 1, dar eu am implementat in indexare de la 0!
}

/* worst case = average case = best case = Teta(1)*/
template<typename V>
void citeste_date(ifstream &input_file, V mat[][Nmax], int &n, int &m, U &p)
{
	citeste_mat<V>(input_file, mat, n, m);
	citeste_poz_start(input_file, p);
}

/* worst case = O(n*m)
average case = O(n*m)
best case = Teta(1) ( n si m sunt zero )
*/
template<typename U>
void afis_mat(U mat[][Nmax], int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << mat[i][j] << " ";
		cout << '\n';
	}
	cout << '\n';
}

/* worst case = average case = best case = Teta(1) */
bool valid_pozitie( int i, int j, int n, int m)
{
	return 0 <= i && i < n && 0 <= j && j < m;
}

/* worst case = average case = best case = Teta(1) */
template<typename T>
bool obstacol(T mat[][Nmax], U p)
{
	return mat[p.i][p.j] == 0;
}

/* worst case = average case = best case = Teta(1) */
template<typename T>
bool valid_nevizitat(T aux[][Nmax], U p)
{
	return aux[p.i][p.j] == false;
}

/* worst case = average case = best case = Teta(1) */
template<typename T, typename U>
bool valid(T mat[][Nmax], U aux[][Nmax], U p, int n, int m)
{
	return valid_pozitie(p.i, p.j, n, m) && !obstacol<T>(mat, p) && valid_nevizitat<U>(aux, p);
}

/* worst case = average case = best case = Teta(1) */
bool pe_contur(U p, int n, int m)
{
	// return p.i == 0 || p.j == 0 || p.i == n - 1 || p.j == m - 1;
	return p.i * p.j == 0 || p.i == n-1 || p.j == m-1;
}

/* e un pic "overhead" sa am toate functiile astea de valid, stiu; dar parca imi place sa am totul cat se poate de fragmentat;
plus ca imi e mai usor sa fac debugging */


/* worst case = average case = best case = Teta(1) */
template<typename T>
bool solution(T mat[][Nmax], U p , int n, int m)
{
	return !obstacol(mat, p) && pe_contur(p, n, m);
}


/*
worst case: O(n*m) 
(scenariul worst case: toate pozitiile sunt marcate cu 0(deci se poate face deplasare in acele celule,
mai putin conturul cel mai din exterior, care este plin cu obstacole)
average case: O(n*m)
best case: Teta(1) (pozitia de start este vecina cu iesire din labirint)
NOTA: stiu ca nu e bine sa presupui in informatica, dar am presupus aici ca pozitia de start nu este chiar o 
o iesire din labirint 
*/
template<typename T>
U gaseste_cale(T mat[][Nmax], int n, int m, U ps)
{
	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1};

	bool visited[Nmax][Nmax] = { false };

	visited[ps.i][ps.j] = true;				// marchez pozitia de start ca vizitata 

	Queue q;
	q.push(ps);								// bag in coada pozitia de start

	U current_pos;
	int row, column, distance;

	while (!q.isEmpty())
	// cat timp exista in coada pozitii pentru care trebuie verificati vecinii (adica sa verific daca vecinii sunt iesire sau nu)
	{
		current_pos = q.pop();
		// stocand head ul cozii in `current_pos` pot spune ca am tratat ce aveam in head, asa cu fac pop

		if (solution<int>(mat, current_pos, n, m))		// daca am gasit o iesire din labirint, parasesc functia
		{
			return current_pos; // voi returna prima solutie gasita, care garantat va fi cea mai scurta (BFS)
		}

		// altfel: adaug toti vecinii valizi in coada
		for (int k = 0; k < 4; k++)
		{
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];
			distance = mat[current_pos.i][current_pos.j] + 1;
			
			U vecin{ row, column };
			
			if (valid<int,bool>(mat, visited, vecin, n, m))

			{
				mat[row][column] = distance;
				visited[row][column] = true;
				q.push(vecin);
			}
		}
	}

	return NULL_POZITIE_PLAN;
}

void reconstruct_path(int mat[][Nmax], int n, int m, U end, U begin, Queue& q)
{
	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1 };

	q.push(end);
	
	U current_pos = end;
	int row, column, distance;
	int len = mat[end.i][end.j];
	while(len != 1)										// cat timp nu am reconstruit intreg traseul din nou ( de data aceasta se va construi traseul in sens invers, de la iesira
	{													// din labirint spre intrare)
		for (int k = 0; k < 4; k++)
		{
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];				// construiesc coordonatele vecinului curent de interogat
			distance = mat[row][column];
			if (valid_pozitie(row, column, n, m)		// verific daca sunt valide aceste coordonate si daca pozitia respectiva are distanta de la pozitia initiala egala cu cat ma 
				&& distance == len - 1)					// intereseaza la pasul curent
			{
				U new_pos = U{ row, column };			// daca da,
				q.push(new_pos);											// adaug in coada aceasta pozitie
				current_pos = new_pos;										// si ma deplasez pe pozitia tocmai adaugata, pentru a relua procedeul
				break;
			}
		}
		len--;					// am certitudinea ca in momentul in care reconstruiesc traseul voi gasi un astfel de element("astfel"= care satisface cele 2 conditii de mai sus, din if),
								// asa ca decrementez lungimea, deoarece am ajuns cu o pozitie mai aproape de pozitia initiala din labirint
	}
	q.push(begin);				// la final, adaug si pozitia initiala in caoda
}


void reverse_queue(Queue& q, const int len)
{
	U *aux = new U[len];
	for (int i = 0; i < len; i++)
		aux[i] = q.pop();

	for (int i = 0; i < len / 2; i++)
		swap(aux[i], aux[len - 1 - i]);				// merg pana la jumatate din array si inversez elementele( functioneaza si pentru dimensiune impara; elementul din mijloc
													// va ramane nemutat )
	for (int i = 0; i <len ; i++)					// reconstruiesc o coada, in care ordinea de parcurgere a pozitiilor din matrice este: de la pozitia initiala catre iesire
		q.push(aux[i]);
}


int main()
{
	/*	NOTA: am incercat sa comprim atat testele pentru Queue cat si jocul in acelasi program, folosindu ma de templated classes/functions doar ca m-am incurcat si n-am mai reusit
	pentru a putea vedea ca testele pentru Queue sunt trecute, va trebui sa (si pe calea aceasta, va rog sa ma iertati ca va dau treaba):
	1. scoateti din comentariu: `testAll()` si `testAllExtended()` mai jos, sa comentati restul de cod in jos, pana la return 0 si sa scoateti din comentariu
	tot fisierul ShortTest.cpp si ExtendedTest.cpp
	2. sa redenumiti in Queue.h NodeDLLA la NodeDLLA_Teste
	3. sa redenumiti in Queue.h atributul tipul atributului nodes de la `TElem*` la `pozitie_plan*` si sa modificati corespunzator
	4. sa comentati in metoda `toString()` a clasei `Queue` `cout` ul lung si sa il lasati pe ala mai scurt
	5.rulati
	
	Am incercat sa fac in asa fel incat sa nu va trimit 2 proiecte.. 

*/

/*
	testAll();
	testAllExtended();
*/

	int mat[Nmax][Nmax] = { 0 };
	int n, m;
	U pozitie_start;
	
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	citeste_date<int>(input_file, mat, n, m, pozitie_start);		
	input_file.close();

	afis_mat<int>(mat, n, m);

	// pana aici citesc datele de intrare si afisez matricea pentru care se rezolva problema

	U end = gaseste_cale<int>(mat, n, m, pozitie_start);
	if (end == NULL_POZITIE_PLAN) 
	{
		cout << "NO SOLUTION FOUND!\n";
	}
	else
	{
		Queue cale;
		reconstruct_path(mat, n, m, end, pozitie_start, cale);
		reverse_queue(cale, mat[end.i][end.j] + 1);
		cout << "The shortest path to be followed (length = " << mat[end.i][end.j] << ", not including the starting position) in the given matrix (above) is:\n";
		cale.toString();
	}

	return 0;
}
