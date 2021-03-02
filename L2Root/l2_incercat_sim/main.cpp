/*
	In ipoteza, chiar daca se spune ca ca cei doi jucatori au cate o "Stapel" in mana, acelea sunt de fapt cozi, deoarece se mai precizeaza faptul ca
atunci unul dintre ei treubie sa ia mormanul adunat pe masa, acel morman se va adauga la baza pachetului de carti din mana, deci: 
---adaugare in coada + extragere din fata = QUEUE
Un alt motiv ar fi intrucat jucatorii adauga la finalul pachetului si extrag prima carte din el.
Mormanul de carti ce se aduna pe masa va reprezenta singura stiva despre care va fi vorba
*/
#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include <random>
using std::cin;
using std::cout;

void pune_carte_jos(Queue& q, Stack& s)
{
	TElem carte = q.top();
	q.pop();
	s.push(carte);
	//cout << carte << " trece"<<'\n';
	cout << carte <<'\n';
}

void ia_cartile(Queue& q, Stack& s)
{
	while (!s.isEmpty())
	{
	//	cout << "intra" << '\n';
		TElem carte = s.pop();			// ia din stiva
//		cout << "trece1" << '\n';
		q.push(carte);					// si adauga in coada
	//	cout << "trece2" << '\n';
	}
}

/* // functia asta e cat de cat buna
void joaca(Queue& q1, Queue& q2, Stack& s)
{
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
			return;
	}
	// de regula, in majoritatea jocurilor de carti pe care le stiu eu, daca player2 ia carile de pe masa in mana, atunci tot player 1 va fi cel care va
	// relua jocul, adica cel care va da primul cartea jos. Aici nu se precizeaza nimic, asa ca nu sunt restrans sa parasesc functia la acest pas, pentru a
	// lasa while-ul din functia 'sim' sa faca "reluarea" jocului, adica sa faca sa fie din nou randul lui player1.
	
	

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

}
*/
void sim(Queue &q1, Queue &q2, Stack &s, const int &n)
{
//	shuffle(q1);
//	shuffle(q2);
	// nu se precizeaza ca trebuie sa fie vreo corespondenta intre numarul de carti rosii, numarul de carti negre
	cout << q1.getLen() << " " << q2.getLen() << '\n';
	while (q1.getLen() != n && q2.getLen() != n) // in cerinta nu se precizeaza ce se intampla daca ambii jucatori primesc numai carti negre; sper ca nu intra in discutie asa un caz
	{
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
		}
		// de regula, in majoritatea jocurilor de carti pe care le stiu eu, daca player2 ia carile de pe masa in mana, atunci tot player 1 va fi cel care va
		// relua jocul, adica cel care va da primul cartea jos. Aici nu se precizeaza nimic, asa ca nu sunt restrans sa parasesc functia la acest pas, pentru a
		// lasa while-ul din functia 'sim' sa faca "reluarea" jocului, adica sa faca sa fie din nou randul lui player1.



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
	}
	cout << q1.getLen() << " " << q2.getLen() << '\n';
	if (q1.getLen() != n || q2.getLen() != n) cout << "DE ASTA" << '\n';
}

int main()
{
	int n = 20; 
	//cin >> n;
	
	Queue q1, q2; // valoarea 0 a unui nod va reprezenta o carte rosie; 1 sau orice alta valoare o carte neagra
	q1.push(0);
	q1.push(1);
	q1.push(2);
	q1.push(0);
	q1.push(3);
	q1.push(0);
	q1.push(5);
	q1.push(6);
	q1.push(7);
	q1.push(0);
	q1.toString();

	q2.push(8);
	q2.push(0);
	q2.push(0);
	q2.push(0);
	q2.push(0);
	q2.push(0);
	q2.push(1);
	q2.push(2);
	q2.push(3);
	q2.push(0);
	q2.toString();


	Stack s;
	s.toString();

	sim(q1, q2, s, n);

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
