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


template<typename T>
void citeste_mat(ifstream &input_file, T mat[][Nmax], int &n, int &m)
{
	input_file >> n >> m;	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			input_file >> mat[i][j];
}

void citeste_poz_start(ifstream &input_file, pozitie_plan &p)
{
	input_file >> p.i >> p.j;
	p.dist = 0;
	p.i--; p.j--;				// utilizatorul vede in indexare de la 1, dar eu am implementat in indexare de la 0!
	cout << p.i << " " << p.j << '\n';
}

template<typename V>
void citeste_date(ifstream &input_file, V mat[][Nmax], int &n, int &m, pozitie_plan &p)
{
	citeste_mat<int>(input_file, mat, n, m);
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

bool valid_pozitie( int i, int j, int n, int m)
{
	return 0 <= i && i < n && 0 <= j && j < m;
}

template<typename T>
bool obstacol(T mat[][Nmax], pozitie_plan p)
{
	return mat[p.i][p.j] == 0;
}

template<typename T>
bool valid_nevizitat(T aux[][Nmax], pozitie_plan p)
{
	return aux[p.i][p.j] == false;
}

template<typename T>
bool valid(T mat[][Nmax], bool aux[][Nmax], pozitie_plan p, int n, int m)
{
	return valid_pozitie(p.i, p.j, n, m) && !obstacol<int>(mat, p) && valid_nevizitat<bool>(aux, p);
}

// e un pic "overhead" sa am toate functiile astea de valid, stiu; dar parca imi place sa am totul cat se poate de fragmentat

bool pe_contur(pozitie_plan p, int n, int m)
{
	// return p.i == 0 || p.j == 0 || p.i == n - 1 || p.j == m - 1;
	return p.i * p.j == 0 || p.i == n-1 || p.j == m-1;
}

template<typename T>
bool solution(T mat[][Nmax], pozitie_plan p , int n, int m)
{
	return !obstacol(mat, p) && pe_contur(p, n, m);
}


template<typename T>
pozitie_plan gaseste_cale(T mat[][Nmax], int n, int m, pozitie_plan ps)
{
	// voi pastra integritatea matricii ( mat nu va fi modificata )

	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1};

	bool visited[Nmax][Nmax] = { false };

	//cout << "MAT INITIAL:\n";
	//afis_mat<bool>(mat, n, m);
	//cout << "MAT AUXILIARA INITIAL:\n";
	cout << "MAT:\n";
	afis_mat<int>(mat, n, m);
	cout << '\n';
	cout << "MAT AUXILIARA INAINTE de adaugare:\n";
	afis_mat<bool>(visited, n, m);
	visited[ps.i][ps.j] = true;				// marchez pozitia de start ca vizitata 

	cout << "MAT:\n";
	afis_mat<int>(mat, n, m);
	cout << '\n';
	cout << "MAT AUXILIARA DUPA adaugare:\n";
	afis_mat<bool>(visited, n, m);

	cout << "==================================================================\n";

	Queue q;
	q.push(ps);								// bag in coada pozitia de start

	pozitie_plan current_pos;
	int row, column, distance;

	while (!q.isEmpty())
	// cat timp exista in coada pozitii pentru care trebuie verificati vecinii (daca vecinii sunt iesire sau nu)
	{
		cout << "MAT:\n";
		afis_mat<int>(mat, n, m);
		cout << '\n';
		cout << "MAT AUXILIARA INAINTE de adaugare:\n";
		afis_mat<bool>(visited, n, m);
		
		cout << "---COADA INAINTE de adaugare---\n";
		q.toString();
		cout << "-----------\n";

		current_pos = q.top();
		cout << "pozitie curent interogata: " << current_pos.i << " " << current_pos.j << "(scoasa din coada)\n";

		if (solution<int>(mat, current_pos, n, m))
		{
			cout << "!S-a gasit solutie! => "<<current_pos.i <<"(+1) "<< " " << current_pos.j << "(+1)"<<'\n';
			return current_pos; // voi returna prima solutie gasita, care garantat va fi cea mai scurta (BFS)
		}
		cout << "trece\n";
		q.pop();		// stocand head ul in `current_pos` pot spune ca am tratat ce aveam in head, asa cu fac pop
		cout << "are loc pop ul\n";

		for (int k = 0; k < 4; k++)
		{
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];
			distance = current_pos.dist + 1;
			
			pozitie_plan vecin{ row, column, distance };
			
			cout << "row=" << row << " " << "column=" << column << '\n';
			if (!valid<int>(mat, visited, vecin, n, m))
			{
				cout << "asta de deasupra NU e bun\n";
				cout << '\n';
			}
			else
			{
				mat[row][column] = distance;
				visited[row][column] = true;
				cout << "asta de deasupra e bun\n";
				cout << '\n';
				q.push(vecin);
			}
		}
		cout << "MAT:\n";
		afis_mat<int>(mat, n, m);
		cout << '\n';
		cout << "MAT AUXILIARA DUPA adaugare:\n";
		afis_mat<bool>(visited, n, m);

		cout << "---COADA DUPA adaugare---\n";
		q.toString();
		cout << "-----------\n";
		cout << "==================================================================\n";
	}

	cout << "NICIO SOLUTIE\n";

	return NULL_POZITIE_PLAN;
}

void reconstruct_path(int mat[][Nmax], int n, int m, pozitie_plan end, pozitie_plan begin, Queue& q)
{
	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1 };

	cout << begin.i << " " << begin.j << '\n';

	q.push(end);
	

	pozitie_plan current_pos = end;
	int row, column, distance;
	int len = current_pos.dist;
	// len--; 
	/* decrementez pentru ca am adaugat deja pozitia de sfarsit in coada (pe while ul de mai jos voi adauga
	pozitii de pe traseu diferite de pozitia de start si pozitia de sfarsit */
	while(len != 1)
	{
		cout << "len=" << len << '\n';
		for (int k = 0; k < 4; k++)
		{
			//cout << " iese de aici\n";
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];
			distance = mat[row][column];
			if (valid_pozitie(row, column, n, m)
				&& distance == len - 1)
			{
				cout << row << " " << column << " " << distance << '\n';
				cout << "DA; distance = " << distance << " = " << len << " - 1 = " << len - 1 << '\n';
				// imping elementul respectiv in coada
				pozitie_plan new_pos = pozitie_plan{ row, column, distance };
				q.push(new_pos);
				// actualizez elementul curent interogat 
				current_pos = new_pos;
				// si reiau instant procedeul
				break;
			}
		}
		len--;
	}
	cout << "//////////////////////////////////////////////////////////\n";
	q.toString();
	cout << "//////////////////////////////////////////////////////////\n";
	q.push(begin);
	q.toString();
	cout << "//////////////////////////////////////////////////////////\n";
}


void reverse_queue(Queue& q, const int len)
{
	pozitie_plan *aux = new pozitie_plan[len];
	cout << "len=" << len << '\n';

	pozitie_plan aux2{ q.top() };
	cout << "TOP:\n";
	cout << aux2.i << " " << aux2.j << '\n';
	cout << "TOP\n";

	for (int i = 0; i < len; i++)
		aux[i] = q.pop();

	for (int i = 0; i < len; i++)
		cout << aux[i].i << " " << aux[i].j << '\n';

	for (int i = 0; i < len / 2; i++)
		swap(aux[i], aux[len - 1 - i]);

	cout << "==============\n";

	if (q.isEmpty()) cout << " Lista e goala COco\n";

	for (int i = 0; i < len; i++)
		cout << aux[i].i << " " << aux[i].j << '\n';
	
	cout << "TOP:\n";
	for (int i = 0; i <len ; i++)
		q.push(aux[i]);
	pozitie_plan aux4{ q.top() };
	cout << "TOP\n";

	q.toString();

}


int main()
{

	int mat[Nmax][Nmax] = { false };
	int n, m;
	pozitie_plan pozitie_start;
	
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	citeste_date<int>(input_file, mat, n, m, pozitie_start);		
	input_file.close();

	// pana aicicitesc datele de intrare

	pozitie_plan end = gaseste_cale<int>(mat, n, m, pozitie_start); // presupun ca utilizatorul numara liniile & coloanele de la 1
	if (end == NULL_POZITIE_PLAN) 
	{
		cout << "nu s a gasit\n";
	}
	else
	{
		// Queue cale = reconstruct_path(mat, n, m, end);
		Queue cale;
		reconstruct_path(mat, n, m, end, pozitie_start, cale);
		cout << "uite ma ca merge\n";
		cale.toString();
		reverse_queue(cale, end.dist + 1);	
		/* +1 aici pentru ca end.dist reprezinta distanta "de la...pana la..."
		deci (similar cu problemele de la secvente, in care o secventa cu 2 elemente
		are lungimea 1
		*/
		cout << "FINAL: BOOOOON\n";

		cale.toString();
	}
	return 0;
}
