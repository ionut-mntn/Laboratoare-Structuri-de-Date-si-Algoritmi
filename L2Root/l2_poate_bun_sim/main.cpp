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

void pune_carte_jos(Queue& q, Stack& s)
{
	TElem carte = q.top();
	q.pop();
	s.push(carte);
	cout << carte << '\n';
}

void hands(Queue &q1, Queue &q2)
{
	cout << "In mana:" << '\n';
	cout << "J1:"; q1.toString();
	cout << "J2:"; q2.toString();
}

/*
	Fiecare jucator isi executa miscarea, daca mai are 
*/
void joaca(Queue& q1, Queue& q2, Stack& s)
{
	hands(q1, q2);
	cout << "Jucatorul 1 pune jos:";
	//try { pune_carte_jos(q1, s); }
	//catch (exception&) { cout << "GAME OVER. PLAYER 1 WINS." << '\n'; throw;// return; 
	//}
	pune_carte_jos(q1, s);
	if (s.getTop() == 0)				// si pune jos o carte rosie, atunci: 
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
	// in sensul clasic
	
	

	cout << "Jucatorul 2 pune jos:";
	//try { pune_carte_jos(q2, s); }				// daca e randul celui de-al doilea jucator
	//catch (exception&) {
	//	cout << "GAME OVER. PLAYER 2 WINS." << '\n'; throw; //return; 
	//}
	pune_carte_jos(q2, s);
	if (s.getTop() == 0)				// si pune jos o carte rosie, atunci
	{
		cout << " Aici:Cartile de pe masa sunt:" << '\n';
		s.toString();
		ia_cartile_stiva(q1, s);			// primul jucator va lua cartile de jos si le vaplasa la finalul pachetului din mana sa
		cout << "Jucatorul 1 ia cartile de pe masa" << '\n';
		cout << '\n';
	}
	cin.get();
}

/*
template <typename T>
void my_swap(T& a, T& b)		// a = 2, b = 3
{
	a += b;						// a = 5,  = 3
	b = a - b;					// a = 5, b = 2
	a -= b;						// a = 3, b = 2
}
*/


void shuffle(int* v, int n)
{
	srand(29);									// i-am dat o valoare random seed ului
	for (int i = 0; i < n - 1; i++)				// n - 1 ca sa nu ajung la ultimul si sa fac swap cu el insusi
	{
		int random = i + (rand() % (n - i));
		//int temp = card[i]; card[i] = card[r]; card[r] = temp;
		swap(v[i], v[random]);
	}
}

void afis(int *sir, int n)
{
	for (int i = 0; i < n; i++)
		cout << sir[i] << " ";
	cout << '\n';
}


/*
	Simuleaza jocul de carti.
*/
void sim(Queue& q1, Queue& q2, Stack& s, int n)
{
	s.toString();
	imparte_carti(s, q1, q2);
	/*
	int l1 = n / 2;				// l1 va reprezenta numarul de carti primite de primul jucator
	if (2 * l1 != n)			// daca n a fost impar, inseamna ca primul a primit cu o carte in plus (impartirea cartilor a inceput de la el)
		l1++;
	int l2 = n - l1;			// oricum ar fi l1 (par/impar) l2 va primi restul de carti
	*/
	cin.get();
	// nu se precizeaza ca trebuie sa fie vreo corespondenta intre numarul de carti rosii, numarul de carti negre

	while (q1.getLen() != n && q2.getLen() != n) // in cerinta nu se precizeaza ce se intampla daca ambii jucatori primesc numai carti negre; sper ca nu intra in discutie asa un caz
	//while(true)
	//while(l1!=n && l2 !=n)
	{
		/*
		try {
			joaca(q1, q2, s);
			//joaca(q1, q2, s);
		}
		catch (exception){ 
			return;		// stiu ca nu e tocmai profi ce am facut aici, adica sa nu prea fac nimic pe catch; se putea face mult mai frumos, i know
		}
		if (q1.getLen() == n) cout << " Congrats Player1 for the win!" << '\n';
		else cout << " Congrats Player2 for the win!" << '\n';
		*/
		joaca(q1, q2, s);
	}
	// cel care ramane fara carti castiga jocul
	if (q1.getLen() == 0) cout << "GAME OVER. Congrats Player1 for the win!" << '\n';
	else cout << "GAME OVER. Congrats Player2 for the win!" << '\n';
}

/*
void defineste_pachet(int *deck, int &n)
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> deck[i];
}
*/

int main()
{
	int n; 

	Queue q1, q2; // valoarea 0 a unui nod va reprezenta o carte rosie; 1 sau orice alta valoare o carte neagra
	q1.toString();
	q2.toString();

	Stack s;
	s.toString();

	
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
	 
	
	int deck2[] = { 0,1 }; // in acest scenariu, ar trebui sa castige jucatorul1;
//	srand(time(0));
	
	/*
	cout << "initial:"; afis(deck, n);
	shuffle(deck, n); // amesteca pachetul de carti
	cout << "dupa shuffle:"; afis(deck, n);
	
	// incepe sa tratezi ca stiva pachetul
	for (int i = 0; i < n - 1; i++) 
		s.push(deck[i]);
	
	//sim(q1, q2, s);
	//cin.get();
	
//	Stack* p = &s;
//	delete p;
	//delete& s;
//	s.~Stack();
	cout << " de aici:" << '\n';
	*/
	n = 20;
	Stack s2;
	s2.toString();
	for (int i = 0; i < n; i++)
		s2.push(deck[i]);
	s2.toString();
	cin.get();
	sim(q1, q2, s2, n);
	cin.get();
	return 0;
}


























//int nr_carti[2] = { 0 }; 

	// carti[0] - nr de carti 'de culoare 0', deci rosii
	// carti[1] - nr de carti 'de culoare 1', deci negre


	//std::uniform_integer_distribution<int> unif(0, 1);
	//std::uniform_real_distribution<int> unif(0, 1);
	/*
	std::uniform_real_distribution<double> unif(0, 2);
	std::default_random_engine re;
	int x;
	int nr = 50;
	int nr0 = 0, nr1 = 0;
	cout << " intra" << '\n';
	int ap[10] = { 0 };
	while (nr)
	{
		x = unif(re);
		ap[x]++;
		cout << " x = "<< x << '\n';
		if (!x) nr0++;
		else nr1++;
		nr--;
	}
	for (int i = 0; i < 10; i++) cout << ap[i] << " ";
	cout << '\n';
	cout << "nr0:" << nr0 << '\n';
	cout << "nr1:" << nr1 << '\n';
	*/


	/*
	cout << "Jucatorul 1 pune jos:";

	try { pune_carte_jos(q1, s); }
	catch (exception&) { cout << "GAME OVER. PLAYER 2 WINS." << '\n'; return; }
	// daca e randul primului jucator
//cout << "treceBOON" << '\n';
	if (s.getTop() == 0)				// si pune jos o carte rosie, atunci:
	{
		//cout << "dar aici nu mai intra" << '\n';
		s.toString();
		ia_cartile(q2, s);			// al doilea jucator va lua cartile de jos si le va plasa la finalul pachetului din mana sa
		cout << "Jucatorul 2 ia cartile de pe masa" << '\n';
		cout << '\n';
		//return;
	}
	// de regula, in majoritatea jocurilor de carti pe care le stiu eu, daca player2 ia carile de pe masa in mana, atunci tot player 1 va fi cel care va
	// relua jocul, adica cel care va da primul cartea jos. Aici nu se precizeaza nimic, asa ca nu sunt restrans sa parasesc functia la acest pas, pentru a
	// lasa while-ul din functia 'sim' sa faca "reluarea" jocului, adica sa faca sa fie din nou randul lui player1.

	\

	cout << "Jucatorul 2 pune jos:";
	try { pune_carte_jos(q2, s); }				// daca e randul celui de-al doilea jucator
	catch (exception&) { cout << "GAME OVER. PLAYER 1 WINS." << '\n'; return; }
	if (s.getTop() == 0)				// si pune jos o carte rosie, atunci
	{
		s.toString();
		ia_cartile(q1, s);			// primul jucator va lua cartile de jos si le vaplasa la finalul pachetului din mana sa
		cout << "Jucatorul 1 ia cartile de pe masa" << '\n';
		cout << '\n';
	}

	cout << "J1: ";  q1.toString(); cout << "l1=" << q1.getLen() << '\n';
	cout << "J2: ";  q2.toString(); cout << "l2="<<q2.getLen() << '\n';
*/


/*
	shuffle_carti(deck, n);
	while (n) {
		s.push(deck[n - 1]);
		n--;
	}
	*/
