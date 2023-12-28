#include <iostream>
#include <type_traits>

using namespace std;

/*
 * <type_traits> 헤더의 사례
 */

int main(int argc, char* argv[])
{
    /*
     * <type_traits> 헤더에 존재하는 아래 변환들에는
     * 모두 ::type 이 붙어있는데
     * 
     * 내부적으로 모두 템플릿화 구조체에 내포된 typedef 와 typename 키워드가
     * 사용됐다는 걸 유추할 수 있다.
     */
    remove_const<int>::type A;        // int
    remove_const<const int>::type B;  // int

    remove_reference<int>::type C;    // int
    remove_reference<int&>::type D;   // int
    remove_reference<int&&>::type E;  // int

    int num;
    add_lvalue_reference<int>::type F   = num;  // int&
    add_lvalue_reference<int&>::type G  = num;  // int&
    add_lvalue_reference<int&&>::type H = num;  // int&

    /*
     * using 이 더 좋은 방법임을 깨달은 후
     * 
     * C++14 부터는 _t 를 붙여 using 으로 구현한 버전들을 제공한다.
     */
    remove_const_t<const int> I;          // int
    remove_reference_t<int&&> J;          // int
    add_lvalue_reference_t<int> K = num;  // int&

    /*
     * 사실 엄청 쉽게 구현할 수 있다.
     * 
     * template <typename T>
     * using remove_const_t = typename remove_const<T>::type;
     */

    return 0;
}
