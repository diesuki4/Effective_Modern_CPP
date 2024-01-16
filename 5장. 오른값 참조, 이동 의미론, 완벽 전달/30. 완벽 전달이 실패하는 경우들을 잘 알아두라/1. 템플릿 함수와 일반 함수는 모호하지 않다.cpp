/*
 * https://learn.microsoft.com/ko-kr/cpp/cpp/overload-resolution-of-function-template-calls?view=msvc-170
 */
#include <iostream>

using namespace std;

/*
 * 템플릿 함수와 일반 함수는 모호하지 않다
 */

void f(int, int)
{
    cout << "f(int, int)" << endl;
}
template <typename T, typename U>
void f(T, U)
{
    cout << "f(T, U)" << endl;
}

template <typename... Args>
void fwd(Args&&... args)
{
    f(forward<Args>(args)...);
}
template <typename... Args>
void fwd2(Args&&... args)
{
    f<Args...>(forward<Args>(args)...);
}

int main(int argc, char* argv[])
{
    f(1, 1);      // f(2, 2)
    fwd(1, 1);    // f(2, 2)
    fwd2(1, 1);   // f<int, int>(2, 2)
    cout << endl;

    f<int, int>(2, 2);      // f<int, int>(2, 2)
    fwd<int, int>(2, 2);    // f(2, 2)
    fwd2<int, int>(2, 2);   // f<int, int>(2, 2)
    cout << endl;

    return 0;
}
