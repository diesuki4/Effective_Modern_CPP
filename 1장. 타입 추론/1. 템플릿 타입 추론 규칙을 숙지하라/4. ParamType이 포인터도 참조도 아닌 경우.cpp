#include <iostream>

using namespace std;

/*
 * ParamType이 포인터도 참조도 아닌 경우
 * 
 * 값에 의한 전달 (Pass by Value)
 */

                      // int       const int      const int&      27        const int*      const int* const
template <typename T> // int       int            int             int       const int*      const int*
void Func(T param)    // int       int            int             int       const int*      const int*
{
    /*
     * 새로운 복사본을 생성하는 것이기 때문에,
     * 참조성과 상수성 모두 무시된다.
     * 
     * 단, 이것은 값 전달 매개변수에 대해서만이다.
     * 
     * 변경이 불가능한 상수 객체를 가리키는
     * const int* 혹은 const int* const 가 전달되었을 때
     * 
     * 함수 내부에서 가리키는 객체의 변경이 가능해서는 안 된다.
     * 
     * 따라서, 이때는 값에 의한 전달이라도
     * 가리키는 객체에 대한 상수성은 보존된다.
     */

    return;
}

int main(int argc, char* argv[])
{
    int x = 10;
    const int  cx  = x;
    const int& crx = x;
    const int* cpx = &x;
    const int* const cpcx = &x;

    Func(x);
    Func(cx);
    Func(crx);
    Func(27);
    Func(cpx);
    Func(cpcx);

    return 0;
}
