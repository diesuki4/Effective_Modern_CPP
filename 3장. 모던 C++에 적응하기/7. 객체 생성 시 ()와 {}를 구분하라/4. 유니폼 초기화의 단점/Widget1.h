#pragma once

#include <iostream>

using namespace std;

class Widget1
{
public:
    Widget1(int i, bool b)   { cout << "int, bool" << endl; }
    Widget1(int i, double d) { cout << "int, double" << endl; }
};
