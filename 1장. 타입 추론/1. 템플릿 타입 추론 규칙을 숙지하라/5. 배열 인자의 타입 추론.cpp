#include <iostream>

using namespace std;

/*
 * 배열 인자의 타입 추론
 */

                      // const char [13]      const char*
template <typename T> // const char*          const char*
void Func1(T param)   // const char*          const char*
{
    /*
     * 배열은 포인터로 추론된다.
     */
    cout << sizeof(param) << endl;

    return;
}

                      // const char [13]
template <typename T> // const char [13]
void Func2(T& param)  // const char (&)[13]
{
    /*
     * 이처럼 함수의 매개변수가
     * T 에 대한 레퍼런스를 받도록 수정하면
     * 
     * 포인터가 아닌, 원본 배열 타입 그대로로 가져올 수 있다.
     */
    cout << sizeof(param) << endl;

    return;
}

                                              // int [6]
template <typename T, size_t N>               // T = int, N = 6
constexpr size_t arraySize(T (&)[N]) noexcept // int (&)[6]
{
    /*
     * 함수에서 원본 배열 타입을 그대로 가져올 수 있는 방법을 응용하면
     * 
     * 이처럼 배열의 크기를 반환하는 트릭을 구현할 수 있다.
     */
    return N;
}

int main(int argc, char* argv[])
{
    // const char[13]
    const char name[] = "Kim Chul Soo";

    // const char*
    const char* pName = name;

    Func1(name);
    Func1(pName);

    Func2(name);

    int arr1[] = {1, 2, 3, 4, 5, 6};

    cout << sizeof(arr1) / sizeof(int) << endl;

    int arr2[arraySize(arr1)];

    cout << sizeof(arr2) / sizeof(int) << endl;

    return 0;
}
