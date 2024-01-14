#include <iostream>

using namespace std;

/*
 * 그래도 신중하게 사용하자
 */

void OldFunc() noexcept
{
    return;
}
/* 함수에서 noexcept 여부를 바꾸면 throw() 예외 명세와 마찬가지로
 * 클라이언트 코드가 깨진다. */
void NewFunc()
{
    throw 100;
    return;
}

/* 우리가 알아둬야 할 중요한 사실은 대부분의 함수는
 * 예외에 중립적인(Exception-neutral) 함수라는 것이다.
 *
 * <예외에 중립적인 함수>
 * 스스로 예외를 던지지는 않지만, 예외를 던지는 함수를 호출할 수는 있는 함수
 *
 * 이런 함수들은 noexcept 으로 지정할 수 없고,
 * 그래서 대부분의 함수는 noexcept 이 아닌 것이다. */
int ExceptionNeutralFunC()
{
    NewFunc();

    return 100;
}

/* 아래처럼 함수를 noexcept 으로 선언하기 위해 어거지로 구현하는 것은
 * 매우 나쁜 방식이다. */
int BadImplementation() noexcept
{
    try
    {
        /* 예외가 전파될 수 있다는 사실을 숨기기 위해
         * 함수 내에서 예외를 처리 */
        NewFunc();
    }
    catch (int expt)
    {
        // -1 반환을 이용해 내부에서 예외가 처리됐음을 알린다.
        return -1;
    }

    // 예외가 발생하지 않았으면 100 반환
    return 100;

    /* 이런 방식은 코드도 복잡해지고, 사용자가 반환 값도 검증해야 하고,
     * noexcept 으로 인한 최적화 이점보다 내부에서 처리할 게 더 많아졌다.
     *
     * 간단히, 배보다 배꼽이 더 커졌다는 것. */
}

int main(int argc, char* argv[])
{
    // OldFunc();
    try
    {
        NewFunc();
    }
    catch (int expt)
    {
        cout << "갑자기 예외를 전파하도록 바뀌었네.." << endl;
    }

    return 0;
}
