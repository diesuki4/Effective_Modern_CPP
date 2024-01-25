/*
 * https://stackoverflow.com/questions/14248235/when-does-a-constexpr-function-get-evaluated-at-compile-time#answer-14248310
 */
#include <iostream>
#include <array>

using namespace std;

/*
 * constexpr 함수의 2가지 특징
 */

class Widget
{
    int data;

public:
    constexpr Widget(int num) : data(num) {}
};

/* 1. constexpr 변수와 달리, constexpr 함수의 반환 값은 자동으로 const 가 되지 않는다.
 *
 * constexpr 함수인 것과 반환 값이 const 인 것은 별개의 문제다.
 * 반환 값은 const Widget 이 아닌 Widget 타입. */
constexpr Widget Func(int data)
{
    return Widget(data);
}

/* 2. constexpr 함수는 컴파일 타임에도, 런타임에도 호출될 수 있다.
 *
 * 단, 모든 인자가 컴파일 시점 상수일 때만
 * 
 * 배열 크기, 템플릿 인자, enum 등 컴파일 타임에 정해져야 하는
 * 정수 상수 표현식(Integral constant expression) 에 사용될 수 있다.
 *
 * 이때, 인자 중 하나라도 컴파일 시점 상수가 아니면 컴파일 에러가 발생한다.
 *
 * 런타임 도중에는 자유롭게 호출할 수 있고 이때는 그냥 일반 함수처럼 동작한다.
 *
 * 따라서, 컴파일 타임 버전과 런타임 버전을 나누지 않아도 된다. */
constexpr int Add(int a, int b)
{
    return a + b;
}

static int g_num = 10;

int main(int argc, char* argv[])
{
    Widget w = Func(5);

    /* constexpr 함수의 결과는 상수 표현식이나 constexpr 변수에 담길 때만
     * 컴파일 시점에 계산된다.
     *
     * const 변수나 일반 변수는 원칙적으로는 런타임에 호출되어야 하나,
     *
     * 컴파일러 최적화에 의해 미리 계산될 수 있다.
     *
     * 하지만, 여기서 constexpr 의 컴파일 시점 계산과 컴파일러 최적화는
     * 별개의 문제다. */
    int arr[Add(2, 3)];     // int arr[5]
    array<int, Add(2, 3)>;  // array<int, 5>

    cout << Add(10, g_num) << endl;

    return 0;
}
