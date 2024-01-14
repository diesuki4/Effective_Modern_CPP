#include <iostream>

using namespace std;

/*
 * 암시적으로 noexcept으로 선언되는 것들
 */
namespace mystd
{
    /* 모든 메모리 해제 함수들 */
    void operator delete  (void* ptr) noexcept;
    void operator delete[](void* ptr) noexcept;
}

class Widget
{
    /* 모든 소멸자 */
    ~Widget() noexcept;
};

class Button
{
    /* 명시적으로 noexcept 이 아님을 알리거나
     * 이런 소멸자를 갖는 객체를 멤버로 가질 경우
     *
     * 소멸자는 noexcept 으로 지정되지 않는다.
     *
     * 다만 이런 경우는 흔치 않으며,
     * 적어도 표준 라이브러리에는 존재하지 않는다.
     *
     * 이펙티브 C++ 에서는 자원 누수 문제 때문에
     * 절대 예외가 소멸자 밖으로 방출되도록 두지 말라고 한다.
     *
     * noexcept 으로 선언하기 위해 어거지로 구현하는 건 나쁘지만
     * 소멸자는 예외인 것.*/
    ~Button() noexcept(false);
};

int main(int argc, char* argv[])
{
    

    return 0;
}
