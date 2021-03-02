﻿#include <iostream>
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
	if (valid_pozitie(p, n, m) && !obstacol(mat,p) && valid_nevizitat(aux, p))
	{
		return true;
	}
	else
	{
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


//Queue gaseste_cale(bool mat[][Nmax], int n, int m, pozitie_plan ps)
void gaseste_cale(bool mat[][Nmax], int n, int m, pozitie_plan ps, Queue &q)
{
	// voi pastra integritatea matricii ( mat nu va fi modificata )

	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1};

	bool visited[Nmax][Nmax] = { false };

	//cout << "MAT INITIAL:\n";
	//afis_mat<bool>(mat, n, m);
	//cout << "MAT AUXILIARA INITIAL:\n";
	cout << "MAT:\n";
	afis_mat<bool>(mat, n, m);
	cout << '\n';
	cout << "MAT AUXILIARA INAINTE de adaugare:\n";
	afis_mat<bool>(visited, n, m);
	visited[ps.i][ps.j] = true;				// marchez pozitia de start ca vizitata 
	//afis_mat<bool>(visited, n, m);

	cout << "MAT:\n";
	afis_mat<bool>(mat, n, m);
	cout << '\n';
	cout << "MAT AUXILIARA DUPA adaugare:\n";
	afis_mat<bool>(visited, n, m);

	cout << "==================================================================\n";

//	Queue q;
	q.push(ps);								// bag in coada pozitia de start

	pozitie_plan current_pos;
	int row, column;

	while (!q.isEmpty())
	// cat timp exista in coada pozitii pentru care trebuie verificati vecinii (daca vecinii sunt iesire sau nu)
	{
		cout << "MAT:\n";
		afis_mat<bool>(mat, n, m);
		cout << '\n';
		cout << "MAT AUXILIARA INAINTE de adaugare:\n";
		afis_mat<bool>(visited, n, m);
		
		cout << "---COADA INAINTE de adaugare---\n";
		q.toString();
		cout << "-----------\n";

		current_pos = q.top();
		cout << "pozitie curent interogata: " << current_pos.i << " " << current_pos.j << "(scoasa din coada)\n";

		if (solution(mat, current_pos, n, m)) return; // voi returna prima solutie gasita, care garantat va fi cea mai scurta (BFS)
		cout << "trece\n";
		q.pop();		// stocand head ul in `current_pos` pot spune ca am tratat ce aveam in head, asa cu fac pop
		cout << "are loc pop ul\n";

		for (int k = 0; k < 4; k++)
		{
			row = current_pos.i + dx[k];
			column = current_pos.j + dy[k];
			pozitie_plan vecin{ row, column };
			cout << "row=" << row << " " << "column=" << column << '\n';
			if (!valid(mat, visited, vecin, n, m))
			{
				cout << "asta de deasupra NU e bun\n";
				cout << '\n';
			}
			else
			{
				visited[row][column] = true;
				cout << "asta de deasupra e bun\n";
				cout << '\n';
				q.push(vecin);
			}
		}
		cout << "MAT:\n";
		afis_mat<bool>(mat, n, m);
		cout << '\n';
		cout << "MAT AUXILIARA DUPA adaugare:\n";
		afis_mat<bool>(visited, n, m);

		cout << "---COADA DUPA adaugare---\n";
		q.toString();
		cout << "-----------\n";
		cout << "==================================================================\n";
		// cin.get();
	}
	

	// return q;
}

int main()
{

	bool mat[Nmax][Nmax] = { false };
	int n, m;
	pozitie_plan pozitie_start;
	
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	citeste_date<bool>(input_file, mat, n, m, pozitie_start);		
	input_file.close();

	// pana aicicitesc datele de intrare
	Queue q;
//	q.push(poz)
	gaseste_cale(mat, n, m, pozitie_start, q); // presupun ca utilizatorul numara liniile & coloanele de la 1
	cout << "IESIT FUNCTIE BOSSINHO\n";
	q.toString();
	
	cout << "ajunge final\n";
	
	return 0;
}