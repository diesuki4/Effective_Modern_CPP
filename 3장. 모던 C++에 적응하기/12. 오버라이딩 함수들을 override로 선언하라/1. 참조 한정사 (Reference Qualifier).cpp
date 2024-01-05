#include <iostream>

using namespace std;

/*
 * 참조 한정사 (Reference Qualifier)
 * 
 * const 키워드로 비상수, 상수 객체에서 호출될 함수를 나눌 수 있는 것처럼
 * 
 * 참조 한정사로 lvalue, rvalue 객체에서 호출될 함수를 나눌 수 있다.
 */

class Widget
{
    string name;

public:
    Widget(const char* p = "") : name(p) { }

    void printA()       { cout << "비상수" << endl; }
    void printA() const { cout <<  "상수"  << endl; }

    void printB() &     { cout << "lvalue" << endl; }
    void printB() &&    { cout << "rvalue" << endl; }

    // 임시 객체의 멤버는 굳이 복사로 가져올 필요가 없다.
    string&  getName() &  { return name; }
    string&& getName() && { return move(name); }
};

int main(int argc, char* argv[])
{
    Widget w;
    const Widget cw;

    w.printA();         // printA()
    cw.printA();        // printA() const

    w.printB();         // printB() &
    Widget().printB();  // printB() &&

    Widget a("Hello");

    string s = a.getName();         // [복사] string&  getName() &
    s = Widget("World").getName();  // [이동] string&& getName() &&

    return 0;
}
