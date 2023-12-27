#include <iostream>

using namespace std;

/*
 * 커스텀 nullptr_t 타입 구현하기
 *
 * nullptr_t 타입의 동작 원리를 이해한다.
 */

void Func(int no) { cout << "Func(int)" << endl; }
void Func(int* p) { cout << "Func(int*)" << endl; }

namespace mystd
{
    // my_nullptr_t 라는 타입이 존재한다고 가정
    struct my_nullptr_t
    {
        // 모든 포인터 타입에 대해 0 으로 변환된다.
        template <typename T>
        operator T* ()
        {
            return 0;
        }

        // 주소를 구할 수 없도록 한다.
        void operator& () const = delete;
    };

    // mynullptr 이라는 리터럴이 존재한다고 가정
    my_nullptr_t mynullptr;
}

int main(int argc, char* argv[])
{
    using namespace mystd;

    Func(mynullptr);         // int*
    Func(my_nullptr_t());    // int*

    void* p1 = mynullptr;       // 암시적 형 변환에 의해 p1 = 0;
    void* p2 = my_nullptr_t();  // 암시적 형 변환에 의해 p2 = 0;

    // if (0 == 0 && 0 == 0)
    if (p1 == my_nullptr_t() && p2 == mynullptr)
        cout << "모두 mynullptr 과 비교가 가능하다." << endl;

    /*
     * 실제로는 std 네임스페이스에 다음과 같이 선언되어 있다.
     * using nullptr_t = decltype(nullptr);
     */

    return 0;
}
