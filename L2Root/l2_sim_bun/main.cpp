/*
Un alt motiv ar fi intrucat jucatorii adauga la finalul pachetului de carti din maan si extrag prima carte din el => queue pentru teancul de carti din mana.
Mormanul de carti ce se aduna pe masa va reprezenta singura stiva, intrucat se tot pun cartile deasupra, iar cand unul dintre jucatorii ia cartile in mana,
le va adauga in coada teancului din mana, asa cum le ia de jos (deci LIFO => stiva pentru cartile care se aduna pe masa)
*/
#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include <random>
#include <ctime>

using std::cin;
using std::cout;
using std::swap;

/*
	Afiseaza un vector de intregi.
*/
void afis(int sir[], int n)
{
	for (int i = 0; i < n; i++)
		cout << sir[i] << " ";
	cout << '\n';
}

void ia_carte_stiva(Queue& q, Stack& s)
{
	TElem carte = s.pop();			// ia din stiva
	q.push(carte);					// si adauga in coada

}

void ia_cartile_stiva(Queue& q, Stack& s)
{
	while (!s.isEmpty())				// cat timp nu s-au luat toate cartile de pe masa, ia-le:
		ia_carte_stiva(q, s);
}

void imparte_carti(Stack& s, Queue& q1, Queue& q2)
{
	if (s.isEmpty()) return;
	ia_carte_stiva(q1, s);
	if (s.isEmpty()) return;
	ia_carte_stiva(q2, s);
	imparte_carti(s, q1, q2);
}

/*
	Scoate un element dintr-o coada si il adauga intr o stiva.
*/
void pune_carte_jos(Queue& q, Stack& s)
{
	TElem carte = q.top();
	q.pop();
	s.push(carte);
	cout << carte << '\n';
}

/*
	Afiseaza cartile din mainile fiecarui jucator.
*/
void hands(Queue &q1, Queue &q2)
{
	cout << "In mana:" << '\n';
	cout << "J1:"; q1.toString();
	cout << "J2:"; q2.toString();
}


/*
void joaca(Queue& q1, Queue& q2, Stack& s)
{
	if (s.getTop() == 0) {ia_cartile_stiva(q1, s); return;}
	while(s.getTop() != 0 )
	
}
*/


/*
	Simuleaza "the turns of the game" (jucator1 pune carte; daca e rosie, jucator2 o ia; alfel, jucator2 pune carte; daca erosie, jucator1 o ia)
*/
void joaca(Queue& q1, Queue& q2, Stack& s)
{
	
	if (q1.getLen() == 0 && q2.getLen() != 0)
	{
		cout << "intra1" << '\n';
		while (q2.getLen() != 0 && s.getTop() != 0) pune_carte_jos(q2, s);
		return;
	}
	else if (q1.getLen() != 0 && q2.getLen() == 0)
	{
		cout << "intra2" << '\n';
		while (q1.getLen() != 0 && s.getTop() != 0) pune_carte_jos(q1, s);
		return;
	}
	else if (q1.getLen() == 0 && q2.getLen() == 0) return;
	else
	{
	
		hands(q1, q2);
		cout << "Jucatorul 1 pune jos:";
		pune_carte_jos(q1, s);
		if (s.getTop() == 0)							// daca player1 pune jos o carte rosie, atunci: 
		{
			cout << "Cartile de pe masa sunt:" << '\n';
			s.toString();
			ia_cartile_stiva(q2, s);			// al doilea jucator va lua cartile de jos si le va plasa la finalul pachetului din mana sa
			cout << "Jucatorul 2 ia cartile de pe masa" << '\n';
			cout << '\n';
			return;
		}
		// de regula, in majoritatea jocurilor de carti pe care le stiu eu, daca player2 ia cartile de pe masa in mana, atunci tot player1 va fi cel care va
		// relua jocul, adica cel care va da primul cartea jos. Aici nu se precizeaza nimic, asa ca nu sunt restrans sa parasesc functia la acest pas, pentru a
		// lasa while-ul din functia 'sim' sa faca "reluarea" jocului, adica sa faca sa fie din nou randul lui player1. Cu toate ca nu sunt restrans, voi continua
		// in sensul clasic.



		cout << "Jucatorul 2 pune jos:";
		pune_carte_jos(q2, s);
		if (s.getTop() == 0)							// daca player2 pune jos o carte rosie, atunci
		{
			cout << "Cartile de pe masa sunt:" << '\n';
			s.toString();
			ia_cartile_stiva(q1, s);					// primul jucator va lua cartile de jos si le va plasa la finalul pachetului din mana sa
			cout << "Jucatorul 1 ia cartile de pe masa" << '\n';
			cout << '\n';
		}
		cout << '\n';
	}
}

/*
	Simuleaza jocul de carti.
*/
void sim(Queue& q1, Queue& q2, Stack& s, int n)
{
	s.toString();
	imparte_carti(s, q1, q2);
	cout << "Apasa enter pentru urmatoarele mutari";
	cin.get();

	
	// in cerinta nu se precizeaza ce se intampla daca ambii jucatori primesc numai carti negre; sper ca nu intra in discutie asa un caz
	//while (q1.getLen() != n && q2.getLen() != n)
	while (q1.getLen() != 0 && q2.getLen() != 0)
	{
		joaca(q1, q2, s);
	}
	cout << "GAME OVER" << '\n';
	hands(q1, q2);
	if (q1.getLen() == 0) cout << "Congrats Player1 for the win!" << '\n';
	else cout << "Congrats Player2 for the win!" << '\n';
}

/*
void defineste_pachet(int *deck, int &n)
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> deck[i];
}
*/

/*
	Interschimba (pseudo-)random valorile unui vector de intregi.
*/
void shuffle(int* v, const int n)
{
	srand(13);									// i-am dat o valoare random seed ului
	for (int i = 0; i < n - 1; i++)				// n - 1 ca sa nu ajung la ultimul si sa fac swap cu el insusi
	{
		int random = rand() % n;
		swap(v[i], v[random]);
	}
}

/*
	Aranjeaza pachetul intr o stiva.
*/
void treat_as_stack(const int* v, const int& n, Stack& s)
{
	for (int i = 0; i < n; i++)
		s.push(v[i]);
}

/*
	Amesteca pachetul si il aranjeaza intr o stiva.
*/
void pregateste_carti(int* deck, const int &n, Stack &s)
{
	cout << " Pachetul de carti la inceput este: "; afis(deck, n);
	shuffle(deck, n);
	cout << " Pachetul de carti dupa amestecare este: ";  afis(deck, n); cout << "Deci pachetul arata astfel:" << '\n';
	treat_as_stack(deck, n, s);
}


int main()
{
	int n; 
	Queue q1, q2; // valoarea 0 a unui nod va reprezenta o carte rosie; 1 sau orice alta valoare o carte neagra
	Stack s;
	
	/*
	// se vor introduce valorile direct aici sau se vor citi de la tastatura, folosind functia comentata mai sus "defineste_pachet"
	introdu_carti(deck,n); // copiata dupa definirea sirului deck, evident
	*/
	// poate nu e un pachet de carti de 52 de carti... n-am de ce sa fixez deck la 52
	// aici, am dat eu deja n ul si sirul
	n = 20;
	int deck[] = { 0,8,1,0,2,0,0,0,3,0,0,0,5,1,6,2,7,3,0,0 };	// daca as fi implementat Queue si Stack ca templated classes, mi-ar fi fost foarte folositor 
																// acum, pentru ca as fi putut considera deck de tip: bool, string sau chiar o clasa definita
																// de mine ( de exemplu, clasa "Card" )
	 
	
	// int deck2[2] = { 1,0 }; // in acest scenariu, ar trebui sa castige jucatorul2;
	int deck3[] = { 0, 0 };
	int deck3[] = { 1, 0, 1 };
	int deck4[] = { 1,1,1,1,0 };

	n = 3;
	pregateste_carti(deck3, n, s);
	sim(q1, q2, s, n);
	
	/*
	n = 2;
	afis(deck2, n);
	shuffle(deck2, n);
	afis(deck2, n);
	treat_as_stack(deck2, n, s);									// pun in stiva elementele din sirul dat / citit de la tastatura
	cin.get();
	sim(q1, q2, s, n);
	cin.get();
	*/
	return 0;
}
