/*
 * https://stackoverflow.com/questions/8584431/why-is-the-keyword-typename-needed-before-qualified-dependent-names-and-not-b#answer-8584507
 */
#include <iostream>

using namespace std;

/*
 * C++에서 이름의 3가지 의미
 */

struct Foo
{
    // 1. A 라는 이름은 타입이다.
    typedef int A;
};

struct Goo
{
    // 2. A 라는 이름은 값이다.
    static const double A;
};

struct Hoo
{
    // 3. A 라는 이름은 템플릿이다.
    template <typename T>
    struct A
    {
        T data;
    };
};

template <typename T>
struct Bar
{
    /*
     * 컴파일러는 각각의 A 가
     * 타입, 값, 템플릿이라는 것을 이미 알고 있다.
     */
    Foo::A a;           // 타입
    double d = Goo::A;  // 값
    Hoo::A<int> hoo;    // 템플릿
};

int main(int argc, char* argv[])
{


    return 0;
}
