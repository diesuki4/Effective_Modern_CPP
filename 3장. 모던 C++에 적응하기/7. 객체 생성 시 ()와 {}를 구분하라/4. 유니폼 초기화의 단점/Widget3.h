#pragma once

#include <iostream>

using namespace std;

class Widget3
{
public:
    Widget3() { }
    Widget3(const Widget3& rhs) { cout << "복사 생성자" << endl; }
    Widget3(Widget3&& rhs)      { cout << "이동 생성자" << endl; }

    Widget3(initializer_list<long double> li) { cout << "initializer_list<long double>" << endl; }

    // 추가
    operator float() const
    {
        cout << "Widget3 => float 형 변환" << endl;
        return 0.F;
    }
};
