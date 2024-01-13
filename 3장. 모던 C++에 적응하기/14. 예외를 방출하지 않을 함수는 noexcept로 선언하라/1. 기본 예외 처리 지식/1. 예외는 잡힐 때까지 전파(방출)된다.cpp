#include <iostream>

using namespace std;

/*
 * 예외는 잡힐 때까지 전파(방출)된다
 */

class Widget
{
    int num;

public:
    Widget(int num) : num(num) { cout << "생성자 " << num << endl; }
    ~Widget()                  { cout << "소멸자 " << num << endl; }
};

void Func3()
{
    Widget w(1);
    throw 100;
}

void Func2()
{
    Widget w(2);
    Func3();
}

void Func1()
{
    Widget w(3);
    Func2();
}

int main(int argc, char* argv[])
{
    try
    {
        Func1();
    }
    catch (int expt)
    {
        /* 예외가 잡히면 catch 블록을 실행하기 전에
         * 스택 풀기가 진행된다. */
        cout << "Func3() 에서 전파된 예외 " << expt << " 잡힘" << endl;
    }

    return 0;
}
