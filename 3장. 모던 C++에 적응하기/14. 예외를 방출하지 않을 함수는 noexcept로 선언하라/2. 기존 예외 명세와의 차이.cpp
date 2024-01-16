#include <iostream>

using namespace std;

/*
 * 기존 예외 명세와의 차이
 */

 // C++98 의 예외 명세는 이제 비권장(Deprecated) 기능이다.
void CPP98() throw(/*int*/ const char*)
{
    // throw 100;
    throw "Exception !!";
}

/* noexcept 의 중요성은 const 와 비슷한 정도다.
 *
 * 다만 예외 명세는 특이하게도, 이것이 지켜지지 않았다고 해서
 * 컴파일 에러를 발생시키지는 않는다.
 *
 * noexcept 함수가 noexcept 보장이 없는 코드에 의존할 수 있으므로
 * 허용은 하되, 런타임에서 강제 종료로 해결하는 것이다.
 *
 * 실제로 C 에서 C++ 의 std 네임스페이스로 옮겨진 strlen() 같은 함수들도
 * 예외 명세가 빠져있다.
 *
 * noexcept 함수 내에서 noexcept 보장이 없는 함수 호출이 가능함을 알기 때문. */
void CPP11() noexcept
{
    throw 100;
}

int main(int argc, char* argv[])
{
    // C++98 에서는 예외 명세가 변하면, 사용자 코드도 바뀌어야 했다.
    try                              { CPP98(); }
    // 여기에서 예외가 잡히므로, 스택이 풀린 후 블록이 실행된다.
    catch (/*int*/ const char* expt) { cout << expt << endl; }

    /* C++11 에서는 중요한 것이 어떤 예외인지가 아니라,
     * 예외를 방출하는지 아닌지라는 이분법적인 흑백논리를 기반으로 한다.
     *
     * 따라서, noexcept 로 지정한 함수는 예외 처리를 할 필요가 없다. */
    try              { CPP11(); }
    // 예외를 방출하는 noexcept 함수는 예외가 잡히지 않고, terminate() 가 호출된다.
    catch (int expt) { cout << expt << endl; }

    return 0;
}
