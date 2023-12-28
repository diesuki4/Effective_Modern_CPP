/*
 * https://pages.cs.wisc.edu/~driscoll/typename.html
 */
#include <iostream>

using namespace std;

/*
 * typename 키워드를 붙여줘야 하는 경우
 *
 * 템플릿 매개변수에 붙이는 typename 과는 다른 얘기다.
 */

struct Foo
{
    typedef int A;
};

struct Goo
{
    static const double A;
};

struct Hoo
{
    template <typename T>
    struct A
    {
        T data;
    };
};

template <typename T>
struct Bar
{
    Foo::A a;           // 타입
    double d = Goo::A;  // 값
    Hoo::A<int> hoo;    // 템플릿

    /*
     * T::A x;
     *
     * 그런데, T::A 는 T 에 따라
     *
     * 타입이 될 수도 있고,
     * 값이 될 수도 있고,
     * 템플릿이 될 수도 있다.
     * 
     * 컴파일러 입장에서는
     * 이게 타입인지 확실하지 않기 때문에
     * 컴파일 에러를 발생시킨다.
     */

    typename T::A x;
    /*
     * 이렇게 범위 지정 연산자(::) 를 통해
     * 한정되고 (Qualified)
     *
     * 템플릿 매개변수 T 에 따라 타입이 달라지는
     * 의존적인 (Dependent) 타입 앞에는
     *
     * 반드시 typename 키워드를 붙여
     * 이것이 확실하게 타입이라는 것을
     *
     * 컴파일러에게 알려야 한다.
     */

    Hoo::A<T> y;
    /*
     * 하지만, 이렇게 템플릿 인자가 뒤에 오는 경우에는
     * 컴파일러가 Hoo::A<T> 가 타입이라는 것을 확실히 알기 때문에
     * 
     * typename 을 붙이지 않아도 된다.
     */
};

int main(int argc, char* argv[])
{


    return 0;
}
