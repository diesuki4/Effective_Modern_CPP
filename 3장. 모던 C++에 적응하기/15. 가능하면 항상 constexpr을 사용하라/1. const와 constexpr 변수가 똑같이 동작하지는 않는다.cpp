#include <iostream>
#include <array>

using namespace std;

/*
 * const와 constexpr 변수가 똑같이 동작하지는 않는다
 */

class Widget
{
    int data;

public:
    constexpr Widget(int num) : data(num) {}

    void SetData(int num) { data = num; }
};

int main(int argc, char* argv[])
{
    const int cNum = 5;
    // 불가
    // cNum = 10;

    int arr[cNum];            // int arr[5]
    array<int, cNum> arr2;    // array<int, 5>

    const int cNum2 = cNum;
    int arr5[cNum2];

    int num = 10;
    const int cNum3 = num;
    // 컴파일 시점 상수로 초기화되지 않았으므로, 불가
    // int arr6[cNum3];

    /* constexpr 변수는 실제로 const 다. */

    constexpr Widget w(5);
    // Non-const 멤버 함수 호출 불가
    // w.SetData(10);

    constexpr int cexpNum = 5;
    // 불가
    // cexpNum = 10;

    int arr3[cexpNum];           // int arr[5]
    array<int, cexpNum> arr4;    // array<int, 5>

    constexpr int cexpNum2 = cexpNum;
    int arr7[cexpNum2];
    /* const 와 달리, constexpr 변수는 Non-const 변수로 초기화 자체가 불가
     * 이처럼 constexpr 변수가 완전히 const 변수와 동일하게 동작하지는 않는다.
     * 
     * constexpr int cexpNum3 = num;*/

    /* 모든 constexpr ==> const
     * 모든 const !==> constexpr
     *
     * 컴파일 시점 상수에 사용하기 위해서는 constexpr 을 쓰는 게 적합하다.
     * constexpr 변수는 예외 없이 상수 표현식에 사용이 가능 */

    return 0;
}
