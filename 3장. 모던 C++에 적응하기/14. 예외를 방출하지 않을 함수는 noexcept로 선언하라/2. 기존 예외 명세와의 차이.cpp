#include <iostream>

using namespace std;

/*
 * 기존 예외 명세와의 차이
 */

// C++98 의 예외 명세는 이제 비권장(Deprecared) 기능이다.
void CPP98() throw(/*int*/ const char*)
{
    // throw 100;
    throw "Exception !!";
}

// noexcept 의 중요성은 const 와 비슷하다.
void CPP11() noexcept
{
    throw 100;
}

int main(int argc, char* argv[])
{
    // C++98 에서는 예외 명세가 변하면, 사용자 코드도 바뀌어야 했다.
    try                              { CPP98();              }
    // 여기에서 예외가 잡히므로, 스택이 풀린 후 블록이 실행된다.
    catch (/*int*/ const char* expt) { cout << expt << endl; }

    /* C++11 에서는 중요한 것이 어떤 예외인지가 아니라,
     * 예외를 방출하는지 아닌지라는 이분법적인 흑백논리를 기반으로 한다.
     *
     * 따라서, noexcept 로 지정한 함수는 예외 처리를 할 필요가 없다. */
    try              { CPP11();              }
    // 예외를 방출하는 noexcept 함수는 예외가 잡히지 않고, terminate() 가 호출된다.
    catch (int expt) { cout << expt << endl; }

    return 0;
}
