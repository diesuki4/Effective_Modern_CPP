#include <iostream>
#include <atomic>

using namespace std;

/*
 * Data race 발생 변수를 atomic 으로 변경 시도
 *
 * 뮤텍스를 쓰는 게 너무 과하다 싶을 때는
 * atomic 을 활용해 동기화 비용을 줄일 수 있는 경우가 많다.
 */

class Widget
{
    /*  Data race 를 해결하기 위해 atomic 변수로 변경 시도
     *
     * atomic 변수는 복사, 이동이 불가능하기에
     * Widget 객체도 함께 복사, 이동이 불가능해진다. */
    mutable atomic<double> value {0.0};
    mutable atomic<bool>   valueIsValid {false};

public:
    double getValue() const
    {
        /* 한 스레드가 계산을 수행하는 도중
         * 다른 스레드가 valueIsValid 를 읽으면 계산은 또 수행된다.
         *
         * 단순히 Data race 가 발생하는 변수를 atomic 으로 변경하는 건
         * 여기선 해결책이 아니다. */
        if (valueIsValid == false)
        {
            double valA = expensiveCompute1();
            double valB = expensiveCompute2();

            // 이 둘의 순서를 바꿔도 해결되지 않는다.
            valueIsValid = true;
            value = valA + valB;
        }

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
