#include <iostream>
#include <mutex>

using namespace std;

/*
 * atomic 대신 mutex를 써야 하는 경우
 * 
 * 동기화가 필요한 변수(혹은 공간) 하나에 대해서는 atomic 이 적합하지만
 * 
 * 둘 이상을 하나의 단위로서 조작해야 할 때는, 뮤텍스를 쓰는 것이 바람직하다.
 */

class Widget
{
    mutable double value {0.0};
    mutable bool   valueIsValid {false};
    /* const 함수 getValue() 내에서는 const 변수만 사용이 가능하다.
     * 하지만, lock_guard 로 mutex 의 상태가 변해야 하므로
     *
     * const 대신 mutable 로 선언한다.
     *
     * atomic 과 같은 이유로
     * Widget 객체도 함께 복사, 이동이 불가능해진다. */
    mutable mutex  m;

public:
    double getValue() const
    {
        // 이제 계산은 1번만 수행될 수 있다.
        lock_guard<mutex> lg(m);

        if (valueIsValid == false)
        {
            double valA = expensiveCompute1();
            double valB = expensiveCompute2();

            value = valA + valB;
            valueIsValid = true;
        }

        /* 하나의 객체에 하나의 스레드만 접근한다면 동기화는 필요 없다.
         *
         * 하지만 그런 Thread-safe 한 상황은 점점 줄어들고 있기 때문에,
         * const 멤버 함수가 언제라도 동시에 실행될 수 있다고 가정하는 게 안전하다.
         *
         * 그리고 읽기 전용인 const 멤버 함수 내에서도, mutable 변수로 인해
         * 쓰기가 발생한다면 동기화가 필요하다. */

        return value;
    }

    double expensiveCompute1() const
    {
        return 123.456;
    }

    double expensiveCompute2() const
    {
        return 789.1011;
    }
};

int main(int argc, char* argv[])
{
    

    return 0;
}
