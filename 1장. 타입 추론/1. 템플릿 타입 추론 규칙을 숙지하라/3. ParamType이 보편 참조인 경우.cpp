#include <iostream>

using namespace std;

/*
 * ParamType이 보편 참조인 경우
 */

                      // int        const int        const int&      27
template <typename T> // int&       const int&       const int&      int
void Func(T&& param)  // int&       const int&       const int&      int&&
{
    /*
     * 호출 인자가 l-value 이면
     * T 와 ParamType 모두 l-value 레퍼런스로 추론된다.
     * 
     * 템플릿 인자 추론에서 T 가 레퍼런스로 추론되는 유일한 경우다.
     * 
     * 호출 인자가 r-value 이면 정상적인 추론이 진행된다.
     */

    return;
}

int main(int argc, char* argv[])
{
    int x = 10;
    const int  cx  = x;
    const int& crx = x;

    Func(x);
    Func(cx);
    Func(crx);
    Func(27);

    return 0;
}
