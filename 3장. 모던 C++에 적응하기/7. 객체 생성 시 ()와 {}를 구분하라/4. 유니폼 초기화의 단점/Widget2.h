#pragma once

#include <iostream>

using namespace std;

class Widget2
{
public:
    Widget2(int i, bool b)   { cout << "int, bool" << endl; }
    Widget2(int i, double d) { cout << "int, double" << endl; }

    // 추가
    Widget2(initializer_list<long double> li) { cout << "initializer_list<long double>" << endl; }
};
