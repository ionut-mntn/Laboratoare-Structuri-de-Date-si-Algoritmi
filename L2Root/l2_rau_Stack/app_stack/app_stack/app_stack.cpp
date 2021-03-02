// app_stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Stack.h"
using std::cout;
int main()
{
    Stack s;
    cout << s.isEmpty() << '\n';
    s.push(2);
    s.push(1);
    s.push(3);
    s.push(10);
    s.push(11);
    s.push(9);
//    cout << s.isEmpty() << '\n';
//    Node* aux = s.temp_getTop();
//    cout << aux->data << '\n';
    cout << s.pop() << '\n';
    cout << s.pop() << '\n';
    cout << s.pop() << '\n';
    cout << s.pop() << '\n';
    cout << s.pop() << '\n';
    cout << s.pop() << '\n';
    cout << s.pop() << '\n';

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
