/*
 * https://stackoverflow.com/questions/26743991/redefining-vs-overriding-in-c#answer-26744071
 */
#include <iostream>

using namespace std;

/*
 * 재정의(Redefining), 오버라이딩(Overriding)
 * 
 * 비가상 함수의 재정의는 오버라이딩이 아니다.
 *
 * 가상/비가상 함수 모두 재정의할 수 있지만,
 * 가상 함수의 재정의만 오버라이딩이라고 한다.
 *
 * 이펙티브 C++ 항목 36 에서는 절대 비가상 함수를 재정의하지 말라고 당부한다.
 *
 * 자식에서 재정의할 것이라면 꼭 부모를 virtual 로 선언해 오버라이드 하라는 것이다.
 *
 * override, final 키워드는 오버라이딩에 관한 것이기 때문에,
 * 비가상 함수에서는 사용할 수 없다.
 */

class Base
{
public:
    virtual void printA() { cout << "Base::printA" << endl; }
    void printB()         { cout << "Base::printB" << endl; }
};

class Derived : public Base
{
public:
    /* 가상 함수를 재정의한 오버라이딩 */
    void printA() override { cout << "Derived::printA" << endl; }
    /* 비가상 함수 재정의 */
    void printB()          { cout << "Derived::printB" << endl; }
};

int main(int argc, char* argv[])
{
    Derived derived;
    Base& base = static_cast<Base&>(derived);

    /* 동적 바인딩에 의한 호출
     * 실제 객체 타입에 따라 런타임에 호출될 함수가 정해진다. */
    base.printA();       // Derived
    derived.printA();    // Derived

    /* 정적 바인딩에 의한 호출
     * 컴파일 타임에 호출될 함수가 정해진다. */
    base.printB();       // Base
    derived.printB();    // Derived

    return 0;
}
