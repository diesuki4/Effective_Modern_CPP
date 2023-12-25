#include <iostream>

using namespace std;

/*
 * 템플릿 매개변수와 함수 매개변수의 추론이 다를 수 있다
 *
 * 매개변수 (Parameter)
 * 템플릿이나 함수의 선언부에서 받는 쪽
 *
 * 인자 (Argument)
 * 함수 호출 등에서 전달하는 쪽
 */

// 템플릿 매개변수 T
template <typename T>
// 함수 매개변수 param
void Example(T/*ParamType*/ param)
{
    return;
}

/*
 * int x = 10;
 * Func1(x);
 *
 * 컴파일러는 호출 인자 x 를 통해 (템플릿 인자를 명시하지 않은 경우)
 *
 * 템플릿 매개변수의 타입 T,
 * 함수 매개변수의 타입 ParamType 을 추론한다.
 *
 * ParamType 에 const, 참조 한정사 (&, &&) 등이 붙으면
 * 이 둘의 결과가 다를 수 있다.
 */
                          // int
template <typename T>     // int
void Func1(const T param) // const int
{
    return;
}

                      // int
template <typename T> // int
void Func2(T& param)  // int&
{
    return;
}

                           // int
template <typename T>      // int
void Func3(const T& param) // const int&
{
    return;
}

int main(int argc, char* argv[])
{
    // 템플릿 인자 int
    // 함수 인자 5
    Example<int>(5);

    int x = 10;

    Func1(x);
    Func2(x);
    Func3(x);

    return 0;
}
