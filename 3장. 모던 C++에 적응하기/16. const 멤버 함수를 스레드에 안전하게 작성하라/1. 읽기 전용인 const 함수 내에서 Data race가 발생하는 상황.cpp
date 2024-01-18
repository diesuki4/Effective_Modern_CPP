#include <iostream>

using namespace std;

/*
 * 읽기 전용인 const 함수 내에서 Data race가 발생하는 상황
 *
 * 여러 스레드가 같은 Widget 객체에 접근한다고 가정
 */

class Widget
{
    mutable double value {0.0};
    mutable bool   valueIsValid {false};

public:
    /* Getter 는 값을 수정하지 않으므로
     * 읽기 전용인 const 로 선언하는 게 적절하다. */
    double getValue() const
    {
        /* 하지만, 계산 비용 때문에 캐싱을 활용하기 위해
         * mutable 변수를 쓰게 되면
         *
         * 이 블록에서 Data race 로 인해, 계산이 여러 번 수행될 수 있다. */
        if (valueIsValid == false)
        {
            double valA = expensiveCompute1();
            double valB = expensiveCompute2();

            value = valA + valB;
            valueIsValid = true;
        }

        return value;
    }

    // 비용이 큰 계산 작업
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
