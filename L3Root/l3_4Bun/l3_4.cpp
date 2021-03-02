#include <iostream>
#include <vector>
#include "Queue.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

#define Nmax 25

using std::vector;
using std::cin;
using std::cout;

bool solution(bool mat[][Nmax], int i, int j, int n, int m)
{
	return ( (i == 0 || i == n - 1 || j == 0 || j == m - 1 ) && mat[i][j]);
	// prima si ultima linie reprezinta iesiri din labirint, respectiv prima si ultima coloana
	// (conform cerintei)
}

bool valid_pozitie(int i, int j, int n, int m)
{
	return 0 < i && i < n && 0 < j && j < m;
}

bool valid_nevizitat(bool mat[][Nmax], int i, int j)
{
	return mat[i][j] == 0;
}

bool valid(bool mat[][Nmax],int i, int j, int n, int m)
{
	return valid_pozitie(i, j, n, m) && mat[i][j] == 1 && valid_nevizitat(mat, i, j);
}

//bool gaseste_cai(bool mat[][Nmax], int i, int j, int n, int m, Queue q, vector<Queue>* queues);

/*
bool trivial_case(bool mat[][Nmax], int n, int m)	// verific din prima conturul ca sa fiu sigur ca exista macar o iesire
{
	for (int j = 0; j < n; j++) if (mat[0][j] == 0) return true;			// linia de sus
	for (int i = 0; i < n - 1; i++) if (mat[i][m - 1] == 0) return true;	// coloana din dreapta
	for (int j = 0; j < m - 1; j++) if (mat[n - 1][j] == 0) return true;	// linia de jos
	for (int i = 0; i < n; i++) if (mat[i][0] == 0) return true;			// coloana din stanga
	
}
*/


/*
// vector<Queue> gaseste_cai(bool mat[][Nmax], int i, int j, int n, int m, Queue q)	
Queue gaseste_cale(bool mat[][Nmax], int n, int m, TElem ps)
{
	// voi pastra integritatea matricii ( va fi modificata )

	const int dx[] = { -1, 0, 0, 1 };
	const int dy[] = { 0, -1, 1, 0 };

	bool visited[Nmax][Nmax] = { false };
	visited[ps.i][ps.j] = true;

	Queue q;
	q.push(ps);

	int i = ps.i, j = ps.j;
	while (!q.isEmpty())	// cat timp exista in coada pozitii pentru care trebuie sa le verific vecinii(daca vecinii sunt iesire sau nu)
		// ;evident, pozitii pe care tot eu le-am bagat in coada la un moment dat
	{
		NodeDLLA current_node = q.top();
		TElem punct = current_node.data;

		if (solution(mat ,i, j, n, m)) return queue; // voi returna prima solutie gasita, care garantat va fi cea mai scurta (BFS)

		q.pop();		// stocand head ul in `current_node` pot spune ca am tratat ce aveam in head, asa cu fac pop

		for (int k = 0; k < ; k++)
		{
			int row = current_node.i + dx[k];
			int column = current_node.j + dy[k];
			if (valid(mat, i, j, n, m))
			{
				visited[row][column] = true;
				NodeDLLA nod_vecin{ row,column };
				q.push(nod_vecin);
			}
		}

	}
}


struct punct
{
	int x; int y;
};
*/



template<typename T>
void afis_mat(T mat[][Nmax], int n, int m)
//void afis_mat(bool mat[][Nmax], int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << mat[i][j] << " ";
		cout << '\n';
	}
}

int main()
{

	
	testAll();
	//testAllExtended();
	cout << "All tests passed\n";
	
	/*
	NodeDLLA proba[10];
	cout << proba[0].data << '\n';
	cout << proba[1].data << '\n';
	cout << proba[2].prev<< '\n';
	cout << proba[3].prev<< '\n';
	cout << proba[4].next<< '\n';
	cout << proba[5].next<< '\n';
	cout << proba[6].data<< '\n';
	*/
	// testele nu mai merg, pentru ca am modificat structura
	// tipului de date `NodeDLL` Info nu mai este de tip elem, 
	// ci este de tip `pozitie_plan`, unde `pozitie_plan` este
	// un tip de date definit de mine ( are ca atribute:index linie, 
	//coloana )

	/*
	bool mat[Nmax][Nmax] = {1,2,3};
	afis_mat<bool>(mat, 10, 10);
	*/

	/*
	int nr_linii, nr_coloane;
	cin >> nr_linii >> nr_coloane;

	int linie_start, coloana_start;
	cin >> linie_start >> coloana_start;
	
	Queue cale;
	*/

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
	/*
	punct a{ 1,2 };
	punct b = a;
	cout << "brio";
	*/

	return 0;
}
