#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "CalculatorMate.h"
using namespace std;

int main()
{
	string exp = "20/(18-2^5)*(30+45)-60+225";
	string postfix = infixToPostfix(exp);

	cout << "The postfix form is: " << postfix << endl;
	cout << "The evaluation of the postfix form is: " << postfixEvaluatin(postfix) << endl;
	return 0;
}