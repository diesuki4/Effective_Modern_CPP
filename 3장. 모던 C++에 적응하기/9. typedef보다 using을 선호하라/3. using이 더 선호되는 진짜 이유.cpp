#include <iostream>
#include <list>

using namespace std;

/*
 * using이 더 선호되는 진짜 이유
 * 
 * typedef 는 템플릿화될 수 없지만, using 은 가능하다.
 */

/*
 * typedef 를 템플릿화하려면
 * 구조체 안에 내포하는 편법을 사용해야 했다.
 *
 * template <typename T>
 * typedef list<T> MyList98;
 */
template <typename T>
struct MyList98
{
    typedef list<T> type;
};

// 이것을 다른 템플릿에서 사용하려면
template <typename T>
class SomeClass98
{
    /*
     * MyList98<T>::type 은
     * 한정되고(Qualified) 의존적인(Dependent) 타입이 되므로
     * 
     * typename 을 붙여주기까지 해야 했다.
     */
    typename MyList98<T>::type list;
};

/*
 * 하지만, 모던 C++ 에서는 간단하게 템플릿화할 수 있다.
 * 
 * 템플릿화된 using 선언을 별칭 템플릿(Alias templates) 이라고 한다.
 */
template <typename T>
using MyList11 = list<T>;

template <typename T>
class SomeClass11
{
    /*
     * 컴파일러는 MyList11<T> 가 타입임을 알 수 있다.
     * 
     * 의존적인 타입이지만, 한정되지 않았으므로
     * typename 키워드를 붙일 필요도 없다.
     */
    MyList11<T> list;
};

int main(int argc, char* argv[])
{


    return 0;
}
