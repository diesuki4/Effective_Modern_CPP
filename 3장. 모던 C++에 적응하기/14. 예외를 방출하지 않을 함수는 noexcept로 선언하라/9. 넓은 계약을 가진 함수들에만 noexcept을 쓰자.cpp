#include <iostream>
#include <stdio.h>

using namespace std;

/*
 * 넓은 계약을 가진 함수들에만 noexcept을 쓰자
 */

class Widget
{
    int m_size;

public:
    /* 넓은 계약(Wide contract) 을 가진 함수
     *
     * 프로그램의 상태와 무관하게 호출할 수 있고
     * 인자나 호출에 대한 전제 조건이 없다.
     *
     * 보통은 넓은 계약을 가진 함수들에만 noexcept 을 사용하는 경향이 있다. */
    size_t size() const noexcept
    {
        return m_size;
    }

    /* 좁은 계약(Narrow contract) 을 가진 함수
     * 
     * 호출에 대한 전제 조건이 있고
     * 이것이 위반되면 Undefined behavior 로 이어진다.
     *
     * 함수의 전제 조건이 정해져 있다면
     * 인자를 잘못 보낸 사용자의 탓이지, 검증하지 않은 함수의 탓은 아니다.
     *
     * 하지만, 일반적으로 Undefined behavior 보다 예외를 디버깅하는 게 더 쉽기 때문에
     * 
     * 좁은 계약을 가진 함수들에는 noexcept 을 잘 쓰지 않는다. */
    static void myPrintf(const char* fs, float f1, float f2)
    {
        printf(fs, f1, f2);
    }
};

int main(int argc, char* argv[])
{
    Widget::myPrintf("%.1f %.1f \n", 1.5F, 2.5F);
    Widget::myPrintf("%m %a \n", 1.5F, 2.5F);

    return 0;
}
