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
void citeste_poz_start(ifstream &input_stream, pozitie_plan &p)
{
	input_stream >> p.i >> p.j;
	// p.dist = 0;
	p.i--; p.j--;				// utilizatorul vede in indexare de la 1, dar eu am implementat in indexare de la 0!
}

/* worst case = average case = best case = Teta(1)*/
template<typename V>
void citeste_date(ifstream &input_file, V mat[][Nmax], int &n, int &m, pozitie_plan &p)
{
	citeste_mat<V>(input_file, mat, n, m);
	citeste_poz_start(input_file, p);
}

/* worst case = O(n*m)
average case = O(n*m)
best case = Teta(1) ( n si m sunt zero )
*/
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

/* worst case = average case = best case = Teta(1) */
bool valid_pozitie( int i, int j, int n, int m)
{
	return 0 <= i && i < n && 0 <= j && j < m;
}

/* worst case = average case = best case = Teta(1) */
template<typename T>
bool obstacol(T mat[][Nmax], pozitie_plan p)
{
	return mat[p.i][p.j] == 0;
}

/* worst case = average case = best case = Teta(1) */
template<typename T>
bool valid_nevizitat(T aux[][Nmax], pozitie_plan p)
{
	return aux[p.i][p.j] == false;
}

/* worst case = average case = best case = Teta(1) */
template<typename T, typename U>
bool valid(T mat[][Nmax], U aux[][Nmax], pozitie_plan p, int n, int m)
{
	return valid_pozitie(p.i, p.j, n, m) && !obstacol<T>(mat, p) && valid_nevizitat<U>(aux, p);
}

/* worst case = average case = best case = Teta(1) */
bool pe_contur(pozitie_plan p, int n, int m)
{
	// return p.i == 0 || p.j == 0 || p.i == n - 1 || p.j == m - 1;
	return p.i * p.j == 0 || p.i == n-1 || p.j == m-1;
}

/* e un pic "overhead" sa am toate functiile astea de valid, stiu; dar parca imi place sa am totul cat se poate de fragmentat;
imi e mai usor sa fac debugging */


/* worst case = average case = best case = Teta(1) */
template<typename T>
bool solution(T mat[][Nmax], pozitie_plan p , int n, int m)
{
	return !obstacol(mat, p) && pe_contur(p, n, m);
}


/*
worst case: O(n*m) 
(scenariul worst case: toate pozitiile sunt marcate cu 0(deci se poate face deplasare in acele celule,
mai putin conturul cel mai din exterior, care este plin cu obstacole)
average case: O(n*m)
best case: Teta(1) (pozitia de start este vecina cu iesire din labirint)
NOTA: stiu ca nu e bine sa presupui in informatica, dar am presupus aici ca pozitia de start nu este o 
o iesire din labirint 
*/
template<typename T>
pozitie_plan gaseste_cale(T mat[][Nmax], int n, int m, pozitie_plan ps)
{
	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1};

	bool visited[Nmax][Nmax] = { false };

	visited[ps.i][ps.j] = true;				// marchez pozitia de start ca vizitata 

	Queue q;
	q.push(ps);								// bag in coada pozitia de start

	pozitie_plan current_pos;
	int row, column, distance;

	while (!q.isEmpty())
	// cat timp exista in coada pozitii pentru care trebuie verificati vecinii (daca vecinii sunt iesire sau nu)
	{
		current_pos = q.pop();
		// stocand head ul cozii in `current_pos` pot spune ca am tratat ce aveam in head, asa cu fac pop

		if (solution<int>(mat, current_pos, n, m))
		{
			return current_pos; // voi returna prima solutie gasita, care garantat va fi cea mai scurta (BFS)
		}

		for (int k = 0; k < 4; k++)
		{
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];
			//distance = current_pos.dist + 1;
			distance = mat[current_pos.i][current_pos.j] + 1;
			
			//pozitie_plan vecin{ row, column, distance };
			pozitie_plan vecin{ row, column };
			
			if (valid<int,bool>(mat, visited, vecin, n, m))

			{
				mat[row][column] = distance;		// 
				visited[row][column] = true;
				q.push(vecin);
			}
		}
	}

	return NULL_POZITIE_PLAN;
}

void reconstruct_path(int mat[][Nmax], int n, int m, pozitie_plan end, pozitie_plan begin, Queue& q)
{
	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1 };

	q.push(end);
	
	pozitie_plan current_pos = end;
	int row, column, distance;
	int len = mat[end.i][end.j];
	while(len != 1)
	{
		for (int k = 0; k < 4; k++)
		{
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];
			distance = mat[row][column];
			if (valid_pozitie(row, column, n, m)
				&& distance == len - 1)
			{
				pozitie_plan new_pos = pozitie_plan{ row, column };
				q.push(new_pos);
				current_pos = new_pos;
				break;
			}
		}
		len--;
	}
	q.push(begin);
}


void reverse_queue(Queue& q, const int len)
{
	pozitie_plan *aux = new pozitie_plan[len];
	for (int i = 0; i < len; i++)
		aux[i] = q.pop();

	for (int i = 0; i < len / 2; i++)
		swap(aux[i], aux[len - 1 - i]);

	for (int i = 0; i <len ; i++)
		q.push(aux[i]);
}


int main()
{

	int mat[Nmax][Nmax] = { 0 };
	int n, m;
	pozitie_plan pozitie_start;
	
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	citeste_date<int>(input_file, mat, n, m, pozitie_start);		
	input_file.close();

	afis_mat<int>(mat, n, m);

	// pana aici citesc datele de intrare

	pozitie_plan end = gaseste_cale<int>(mat, n, m, pozitie_start); // presupun ca utilizatorul numara liniile & coloanele de la 1
	if (end == NULL_POZITIE_PLAN) 
	{
		cout << "NO SOLUTION FOUND!\n";
	}
	else
	{
		// Queue cale = reconstruct_path(mat, n, m, end);
		Queue cale;
		reconstruct_path(mat, n, m, end, pozitie_start, cale);
		//reverse_queue(cale, end.dist + 1);	
		//cout << "The shortest path (length = " << end.dist << " not including the starting position) to be followed in the given matrix (above) is:\n";
		reverse_queue(cale, mat[end.i][end.j] + 1);
		cout << "The shortest path (length = " << mat[end.i][end.j] << " not including the starting position) to be followed in the given matrix (above) is:\n";
		cale.toString();
	}
	return 0;
}
