#include <iostream>

using namespace std;

/*
 * nullptr은 정수로 해석되지 않는다
 */

/*
 * C++11 에서 nullptr 이 등장하긴 했지만,
 * 여전히 0, NULL 을 사용하는 사람들이 있기 때문에
 *
 * 이런 정수와 포인터의 오버로드는 지양해야 한다.
 */
void Func(int no) { cout << "Func(int)" << endl; }
void Func(int* p) { cout << "Func(int*)" << endl; }

int main(int argc, char* argv[])
{
    Func(0);                    // int
    Func(NULL);                 // int

    Func(static_cast<int*>(0)); // int*
    /*
     * 리터럴 nullptr 의 실제 타입은 nullptr_t 이다.
     */
    Func(nullptr);              // int*
    Func(nullptr_t());          // int*

    return 0;
}
