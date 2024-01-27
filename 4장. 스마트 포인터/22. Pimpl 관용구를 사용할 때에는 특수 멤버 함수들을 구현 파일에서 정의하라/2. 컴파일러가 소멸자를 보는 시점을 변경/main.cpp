#include <iostream>
#include "Widget.h"

using namespace std;

/*
 * 컴파일러가 소멸자를 보는 시점을 변경
 */

void Func()
{
    Widget w(1, "Hello World");

    /* 상황은 같다. */
}

int main(int argc, char* argv[])
{
    Func();

    return 0;
}
