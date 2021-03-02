#include <iostream>
using namespace std;

class Date
{
private:
    int m_year{ 1900 };
    int m_month{ 1 };
    int m_day{ 1 };

    // No constructor provided, so C++ creates a public default constructor for us
public:
    int getYear() { return m_year; }
    int getMonth() { return m_month; }
    int getDay() { return m_day; }
};

class A
{
private:
    int a;
    int b;
public:

    int get_a() { return a; }
    int get_b() { return b; }

    void afis() { cout << "cf"; }
};

class B
{
private:
    int a{ 2 };
    int b{ 3 };
public:

    int get_a() { return a; }
    int get_b() { return b; }

    void afis() { cout << "cf"; }
};

class C
{
private:
    int a;
    int b;
public:

    C() {};

    int get_a() { return a; }
    int get_b() { return b; }

    void afis() { cout << "cf"; }
};

class D
{
private:
    int a;
    int b;
public:

    D() = default;

    int get_a() { return a; }
    int get_b() { return b; }

    void afis() { cout << "cf"; }
};


int main()
{
    Date date{}; // calls implicit constructor
    /*
    std::cout << date.getYear() << '\n';
    std::cout << date.getMonth() << '\n';
    std::cout << date.getDay() << '\n';
    */
    A proba;
    cout << proba.get_a() << '\n';
    cout << proba.get_b() << '\n';

    B proba2;
    cout << proba2.get_a() << '\n';
    cout << proba2.get_b() << '\n';

    C proba3;
    cout << proba3.get_a() << '\n';
    cout << proba3.get_b() << '\n';

    D proba4;
    cout << proba4.get_a() << '\n';
    cout << proba4.get_b() << '\n';


    return 0;
}