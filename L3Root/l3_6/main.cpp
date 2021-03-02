#include <iostream>
#include <vector>
#include "Queue.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

#define Nmax 25

using std::cin;
using std::cout;
using std::vector;

#include <fstream>
using std::ifstream;
using std::ofstream;

/*
ifstream(fin, "date.in");	// sper ca nu e nicio problema daca deschid aici, "global" fisierul
ofstream(fout, "date.out");
*/

template<typename T>
void citeste_mat(ifstream &input_file, T mat[][Nmax], int &n, int &m)
{
	input_file >> n >> m;	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			//cin >> mat[i][j];
			input_file >> mat[i][j];
		}
	}
}

void citeste_poz_start(ifstream &input_file, pozitie_plan &p)
{
	input_file >> p.i >> p.j;
	p.i--; p.j--;				// utilizatorul vede in indexare de la 1, dar eu am implementat in indexare de la 0!
}

template<typename V>
void citeste_date(ifstream &input_file, V mat[][Nmax], int &n, int &m, pozitie_plan &p)
{
	citeste_mat(input_file, mat, n, m);
	citeste_poz_start(input_file, p);
}

template<typename U> // ar fi fost problema daca puneam aici tot "T" in loc de "U" ?
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

bool valid_pozitie(pozitie_plan p, int n, int m)
{
	return 0 < p.i && p.i < n && 0 < p.j && p.j < m;
}

bool obstacol(bool mat[][Nmax], pozitie_plan p)
{
	return mat[p.i][p.j] == 0;
}

bool valid_nevizitat(bool aux[][Nmax], pozitie_plan p)
{
	return aux[p.i][p.j] == 0;
}

bool valid(bool mat[][Nmax], bool aux[][Nmax], pozitie_plan p, int n, int m)
{

	if (valid_pozitie(p, n, m) && !obstacol(mat,p))
	{
		cout << "A\n";
		return true;
	}
	else
	{
		cout << "B\n";
		return false;
	}
}

bool pe_contur(pozitie_plan p, int n, int m)
{
	return (p.i == 0 || p.i == n - 1 || p.j == 0 || p.j == m - 1);
}
bool solution(bool mat[][Nmax], pozitie_plan p , int n, int m)
{
	return !obstacol(mat, p) && pe_contur(p, n, m);
}


Queue gaseste_cale(bool mat[][Nmax], int n, int m, pozitie_plan ps)
{
	// voi pastra integritatea matricii ( mat nu va fi modificata )

	// cout << " l start = " << ps.i << "; c start = " << ps.j << '\n';

	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1};

	bool visited[Nmax][Nmax] = { false };

	cout << "MAT AUXILIARA:\n";
	afis_mat<bool>(visited, n, m);
	
	visited[ps.i][ps.j] = true;				// marchez pozitia de start ca vizitata 

	Queue q;
	q.push(ps);								// bag in coada pozitia de start

	pozitie_plan current_pos;
	int row, column;
	while (!q.isEmpty())
	// cat timp exista in coada pozitii pentru care trebuie verificati vecinii (daca vecinii sunt iesire sau nu)
	{
//		q.toString();

		cout << "intra\n";
		current_pos = q.top();

		if (solution(mat, current_pos, n, m)) return q; // voi returna prima solutie gasita, care garantat va fi cea mai scurta (BFS)
		cout << "trece\n";
		q.pop();		// stocand head ul in `current_pos` pot spune ca am tratat ce aveam in head, asa cu fac pop

		for (int k = 0; k < 4; k++)
		{
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];
			cout << "row=" << row << " " << "column=" << column << '\n';
			if (valid(mat, visited, current_pos, n, m))
			{
				visited[row][column] = true;
				pozitie_plan nod_vecin{ row,column };
				q.push(nod_vecin);
			}
		}
		cout << "MAT AUXILIARA:\n";
		afis_mat<bool>(visited, n, m);
		q.toString();
	}
	

	return q;
}

int main()
{

	// testAll();
	// testAllExtended();
	cout << "All `Queue` tests passed\n";

	bool mat[Nmax][Nmax] = { false };
	int n, m;
	pozitie_plan pozitie_start;
	
	
	ifstream input_file;
	input_file.open("input.txt", ios::in);
/*
	if (input_file) cout << "s a deschis cu SUCCES!\n";
	else cout << " Nu s a putut deschide fisierul\n";
*/

	citeste_date<bool>(input_file, mat, n, m, pozitie_start);		//ERA PROBLEMA LA CITIRE PENTRU CA AM LASAT
	// CARACTERUL 'R' IN MATRICE !!!
	cout << n << " " << m << '\n';
	cout << pozitie_start.i << " " << pozitie_start.j << '\n';
	input_file.close();
	
	afis_mat<bool>(mat, n, m);

	Queue q = gaseste_cale(mat, n, m, pozitie_start ); // presupun ca utilizatorul numara liniile&coloanele de la 1

	/*
	pozitie_plan aux;
	cout << aux.i << " " << aux.j << '\n';
	*/
	q.toString();









	/*
	// testAll();
	// testAllExtended();
	cout << "All `Queue` tests passed\n";

	bool mat[Nmax][Nmax] = { false };
	// afis_mat<bool>(mat, 10, 10);

	int n = 5, m = 5;
	//citeste_mat<bool>(mat, n, m);
	// afis_mat<bool>(mat, 10, 10);

	int index_start_linie = 2, index_start_coloana = 3;
	cout << "Introduceti linia de start: ";   cin >> index_start_linie;
	cout << "Introduceti coloana de start: ";   cin >> index_start_coloana;

	Queue q = gaseste_cale(mat, n, m, pozitie_plan{ index_start_linie - 1, index_start_coloana - 1}); // presupun ca utilizatorul numara liniile&coloanele de la 1
	pozitie_plan aux;
	cout << aux.i << " " << aux.j << '\n';
	q.toString();

	/*
	pozitie_plan aux{ 2,3 };
	cout << aux;
	
	*/
	
	
	return 0;
}
