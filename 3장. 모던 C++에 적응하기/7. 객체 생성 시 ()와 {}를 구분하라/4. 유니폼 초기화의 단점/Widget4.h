#pragma once

#include <iostream>

using namespace std;

class Widget4
{
public:
    Widget4() { }
    Widget4(int i, double d) { cout << "int, double" << endl; }

    Widget4(initializer_list<bool> li) { cout << "initializer_list<bool>" << endl; }
};
