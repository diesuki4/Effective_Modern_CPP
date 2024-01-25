/*
 * https://stackoverflow.com/questions/1628768/why-does-an-overridden-function-in-the-derived-class-hide-other-overloads-of-the
 * https://stackoverflow.com/questions/32946364/c-inheritance-and-name-hiding
 * https://stackoverflow.com/questions/6397938/ambiguous-access
 */
#include <iostream>

using namespace std;

/*
 * 이름 은폐 (Name Hiding)
 *
 * 자식에 부모 멤버와 같은 이름의 변수(혹은 함수) 가 정의되어 있으면
 * 부모의 멤버가 가려지는 현상
 *
 * C++ 의 이름 결정 규칙 (Name Resolution Rule)
 *
 * 1. 현재 범위(Scope) 부터 매칭되는 첫 번째 이름을 찾는다.
 * 2. 이름을 찾은 범위에서 오버로드 함수를 찾는다.
 *
 * 결론적으로, <이름 결정 규칙> 에 의해 <이름 은폐> 가 발생하는 것이다.
 * 이것은 이름에 관한 것이기 때문에, 함수의 시그니처가 달라도 동일하게 적용된다.
 */

namespace AAA
{
    int num;

    void Func()
    {
        /* 지역 변수 num 으로 인해 AAA::num 은 가려지게 된다.
         *
         * 이렇게 내부(Inner) 범위의 이름은 외부(Outer) 범위의 이름을 가린다. */
        int num = 0;
    }
}

class Base
{
    int data;

public:
    virtual void printA() { cout << "Base::printA" << endl; }

    void printC(string s) { cout << "Base::printC(" << s << ")" << endl; }

    virtual void printD(string s) { cout << "Base::printD(" << s << ")" << endl; }

    void printE(string s)         { cout << "Base::printE(" << s << ")" << endl; }
};

class Derived : public Base
{
    int data;

public:
    void Func()
    {
        /* 상속 관계에서 자식 기준으로 부모는 외부 범위, 자신은 내부 범위가 되므로
         * Base::data 는 가려지게 된다. */
        data = 5;
    }

    /* 이는 함수에도 동일하게 적용된다.
     * 그리고, 결정된 이름과 같은 범위에 있는 함수들만 오버로딩 후보가 된다. */

     /* 일반적인 오버라이딩
      * 자식이 부모의 이름을 가리므로, 자식에서는 자신의 함수로 결정된다. */
    void printA() override { cout << "Derived::printA" << endl; }

    /* 부모의 printC(string) 과 오버로딩 관계가 아니다.
     * 현재 클래스는 내부 범위, 부모는 외부 범위가 된다.
     *
     * 결정된 이름과 같은 범위에 있는 함수들만 오버로딩 후보가 되므로
     * 자식에서는 부모의 printC(string) 을 호출할 수 없다. */
    void printC(int i)     { cout << "Derived::printC(" << i << ")" << endl; }

    /* 가상 함수여도 동일하게 적용된다.
     * 이름 은폐는 가상 함수보다 더 Low-level(저수준) 의 개념이다. */
    virtual void printD(int i) { cout << "Derived::printD(" << i << ")" << endl; }

    using Base::printE;
    /* 이제 외부 범위에 있던 부모 함수를 내부 범위로 끌고 왔으므로
     * 이 둘은 오버로딩 관계가 된다. */
    void printE(int i)         { cout << "Derived::printE(" << i << ")" << endl; }
};

class Mother
{
public:
    void printF(string s) { cout << "Mother::printF(string)" << endl; }
};

class Father
{
public:
    void printF(int i) { cout << "Father::printF(int)" << endl; }
};

class Child : public Mother, public Father
{
public:
    /* 다중 상속 관계에서는 두 함수를 모두 가져와야
     * 오버로딩 관계가 된다. */
    using Mother::printF;
    using Father::printF;
};

int main(int argc, char* argv[])
{
    Derived derived;
    Base& base = static_cast<Base&>(derived);

    base.printA();       // Derived
    base.printC("AAA");  // Base
    base.printD("BBB");  // Base
    base.printE("CCC");  // Base

    derived.printA();       // Derived
    // derived.printC("AAA");
    derived.Base::printC("AAA");    // 부모 Scope 를 정해주면 호출 가능
    // derived.printD("BBB");
    derived.Base::printD("BBB");    // 부모 Scope 를 정해주면 호출 가능
    derived.printE("CCC");  // Base
    derived.printE(1);      // Base

    Child child;

    child.printF("DDD");   // Mother
    child.printF(10);      // Father  

    return 0;
}
