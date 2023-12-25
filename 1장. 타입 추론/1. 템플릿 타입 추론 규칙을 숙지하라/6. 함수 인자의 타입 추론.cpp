#include <iostream>

using namespace std;

/*
 * 함수 인자의 타입 추론
 */

void SomeFunc(int i, double d)
{
    cout << i << " " << d << endl;
}

                      // void (int, double)
template <typename T> // void (*)(int, double)
void Func1(T param)   // void (*)(int, double)
{
    param(1, 2.5);

    return;
}

                      // void (int, double)
template <typename T> // void (int, double)
void Func2(T& param)  // void (&)(int, double)
{
    param(3, 4.5);

    return;
}

int main(int argc, char* argv[])
{
    // void (int, double)
    // SomeFunc

    // void (*)(int, double)
    void (*fptr)(int, double) = SomeFunc;
    // void (&)(int, double)
    void (&fref)(int, double) = SomeFunc;

    cout << typeid(fptr).name() << endl;
    cout << typeid(fref).name() << endl;

    Func1(SomeFunc);
    Func2(SomeFunc);

    return 0;
}
