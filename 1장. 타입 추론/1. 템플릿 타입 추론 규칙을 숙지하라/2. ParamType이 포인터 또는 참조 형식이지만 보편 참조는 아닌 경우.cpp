#include <iostream>

using namespace std;

/*
 * ParamType이 포인터 또는 참조 형식이지만 보편 참조는 아닌 경우
 */

                      // int       const int       const int&
template <typename T> // int       const int       const int
void Func1(T& param)  // int&      const int&      const int&
{
    /*
     * 호출 인자가 const 이면
     * 최종 ParamType 의 타입도 const 가 되는 것에 주목하자.
     * 
     * 객체의 상수성(Constness) 이 유지된다.
     */
    
    return;
}

                           // int           const int        const int&
template <typename T>      // int           int              int
void Func2(const T& param) // const int&    const int&       const int&
{
    /*
     * T 추론 과정에서 참조성(&, Referenceness) 은 무시된다.
     */

    return;
}

                      // int*      const int*
template <typename T> // int       const int
void Func3(T* param)  // int*      const int*
{
    /*
     * T 추론 과정에서 레퍼런스와 마찬가지로
     * 포인터 또한 무시된다.
     */

    return;
}

int main(int argc, char* argv[])
{
    int x = 10;
    const int  cx  = x;
    const int& crx = x;
    const int* cpx = &x;

    Func1(x);
    Func1(cx);
    Func1(crx);

    Func2(x);
    Func2(cx);
    Func2(crx);

    Func3(&x);
    Func3(cpx);

    return 0;
}
