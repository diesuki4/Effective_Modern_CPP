#include <iostream>
#include "Widget1.h"
#include "Widget2.h"
#include "Widget3.h"
#include "Widget4.h"
#include "Widget5.h"

using namespace std;

/*
 * 유니폼 초기화의 단점
 *
 * 종종 예상치 못한 행동을 보인다.
 */

void Func(int i) { }

int main(int argc, char* argv[])
{
    auto x1(1);     // int
    auto x2{2};     // int
    auto x3 = 3;    // int
    auto x4 = {4};  // initializer_list<int>

    Func(x1);
    Func(x2);
    Func(x3);
    // initializer_list<int> 에서 int 로 형 변환할 수 없습니다.
    // Func(x4);

    Widget1 a(10, true);     // int, bool
    Widget1 b{10, true};     // int, bool
    Widget1 c = {10, true};  // Widget1 c{10, true} 와 대체로 동일하게 취급된다.
    Widget1 d(10, 5.0);      // int, double
    Widget1 e{10, 5.0};      // int, double
    cout << endl;

    /*
     * {} 를 사용한 유니폼 초기화 구문은 이상하게도
     * initializer_list 를 받는 생성자를 <강하게 선호> 한다.
     *
     * 형 변환 등으로 initializer_list 버전 생성자로
     * 해석될 여지가 조금이라도 있으면
     *
     * 컴파일러는 반드시 initializer_list 생성자를 선택한다.
     */

    Widget2 f(10, true);     // int, bool
    Widget2 g{10, true};     // initializer_list<long double>
    Widget2 h(10, 5.0);      // int, double
    Widget2 i{10, 5.0};      // initializer_list<long double>
    cout << endl;

    /*
     * 복사 생성자나 이동 생성자가 호출되어야 하는 상황에도
     *
     * initializer_list 생성자가 이를 가로챈다.
     * (GCC 에서는 가로채고, MSVC 에서는 가로채지 않는다.)
     */

    Widget3 w3;
    Widget3 j(w3);        // 복사 생성자
    Widget3 k{w3};        /* 
                           * Widget3 => float 형 변환
                           * float => long double 암시적 형 변환 가능
                           * initializer_list<long double>
                           */
    Widget3 l(move(w3));  // 이동 생성자
    Widget3 m{move(w3)};  // k 와 동일한 현상 발생
    cout << endl;

    /*
     * Widget4 w4{10, 5.0};
     *     
     * 유니폼 초기화를 std_initializer 생성자로 받으려는
     * 너무 강한 선호 때문에
     *
     * std_initializer 의 우선순위가 가장 높아도 호출할 수 없는
     * 기이한 현상이 생기기도 한다.
     *
     * 위처럼 (int, double) 생성자를 가로채 놓고는
     * 유니폼 초기화의 특징인 축소 변환을 허용하지 않음에 따라 사용할 수도 없게 되었다.
     */

    /*
     * 컴파일러가 std_initializer<T> 생성자를 포기하는 경우는
     *
     * 인자들이 T 로 형 변환될 수 없을 때 뿐이다.
     */
    Widget5 n(10, true);     // int, bool
    Widget5 o{10, true};     // int, bool
    Widget5 p(10, 5.0);      // int, double
    Widget5 q{10, 5.0};      // int, double
    cout << endl;

    /*
     * initializer_list 생성자가 존재하는 객체를
     *
     * 빈 유니폼 초기화로 생성하면?
     */
    Widget2 r{};    // 기본 생성자
    Widget2 s();    // Widget2 객체를 반환하는 s() 라는 함수의 extern 선언

    Widget2 t{{}};  // initializer_list<long double>
    Widget2 u({});  // initializer_list<long double>

    return 0;
}
