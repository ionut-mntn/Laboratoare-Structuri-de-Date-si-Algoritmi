#include <iostream>
#include <string>
#include "Queue.h"
#include "Stack.h"
using namespace std;

//ordinea efectuarii operatilor
int prec(char c) //BC: O(1) AC O(1) WC: O(1) 
{
	if (c == '^')
	{
		return 3;
	}
	else
	{
		if (c == '*' || c == '/')
		{
			return 2;
		}
		else
		{
			if (c == '+' || c == '-')
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
	}
}

string infixToPostfix(string s)
{
	Queue d;
	d.pushfront("NULL");

	string S = "";
	int len = s.length();

	//Postfix form 
	//parcurgerea stringului initial in forma infixa
	for (int i = 0; i < len; i++) //BC: O(1) AC: O(n) WC: Θ(n)
	{
		//verific daca am ajuns pe un char numeric
		if (s[i] >= '0' && s[i] <= '9')//(s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		{
			//copiez in noul string numarul
			while (s[i] >= '0' && s[i] <= '9') //BC: O(1) AC: O(n) WC: O(n)
			{
				S = S + s[i];
				i++;
			}
			i--;
			S = S + ' ';
		}
		else
		{
			//daca gasesesc o paranteza deschisa practic pun ca marcator in coada caracterul "("
			if (s[i] == '(')
			{
				d.pushfront("(");
			}
			else
			{
				if (s[i] == ')')
				{
					//daca am ajuns la o inchdere de paranteza corecta inseamna ca trebuie sa scot din coada toti operatorii care au fost prezenti in paranteza respectiva 
					//Trebuie facuta aceasta operatiune pana ce regasesc paranteza respectiva
					while (d.front() != "NULL" && d.front()[0] != '(') //BC: O(1) AC: O(n) WC: O(n)
					{
						S += d.front()[0];
						S += ' ';
						d.popfront();
					}
					if (d.front() == "(")
					{
						d.popfront();
					}
				}
				else
				{
					//apelez precedenta operatoriala ca sa stiu daca pun in coada opratorul curent din string sau scot din coada operatorii care ar avea precedenta corecta
					while (d.front() != "NULL" && prec(s[i]) <= prec(d.front()[0])) //BC: O(1) AC: O(n) WC: O(n)
					{
						S = S + d.front()[0];
						S = S + ' ';
						d.popfront();
					}
					string newOperator = "";
					newOperator = newOperator + s[i];
					d.pushfront(newOperator);
				}
            }

		}
	}

	//pot sa mai ramana operatori pe coada ramasi
	while (d.front() != "NULL") //BC: O(1) AC: O(n) WC: O(n)
	{
		S = S + d.front()[0];
		S = S + ' ';
		d.popfront();
	}
	return S;
}

int postfixEvaluatin(string post)
{
	Stack stiva;
	int len = post.length();

	//efectuarea operatilor asupra elementelor de pe stiva
	for (int i = 0; i < len; i++) //BC: O(1) AC: O(n) WC: Θ(n)
	{
		if (post[i] == ' ')
		{
			continue;
		}
		else
		{
			if (isdigit(post[i]))
			{
				string nr = "";
				while (post[i] != ' ')
				{
					nr = nr + post[i];
					i++;
				}
				stiva.push(stoi(nr));
			}
			else
			{
				int val2 = stiva.peek();
				stiva.pop();
				int val1 = stiva.peek();
				stiva.pop();
	
				//cout << "val1: " << val1 << "  " << "val2: " << val2 << " operator:  " << post[i] << endl;
	
				switch (post[i])
				{
					case '+': stiva.push(val1 + val2); break;
					case '-': stiva.push(val1 - val2); break;
					case '*': stiva.push(val1 * val2); break;
					case '/': stiva.push(val1 / val2); break;
					case '^': stiva.push(pow(val1, val2)); break;
				}
			}
		}
	}

	int result = stiva.peek();
	return result;
}

