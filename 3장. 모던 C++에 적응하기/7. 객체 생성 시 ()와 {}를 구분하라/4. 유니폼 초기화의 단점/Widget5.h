#pragma once

#include <iostream>

using namespace std;

class Widget5
{
public:
    Widget5(int i, bool b)   { cout << "int, bool" << endl; }
    Widget5(int i, double d) { cout << "int, double" << endl; }

    Widget5(initializer_list<string> li) { cout << "initializer_list<string>" << endl; }
};
