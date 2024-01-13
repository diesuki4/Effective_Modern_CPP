#include <iostream>

using namespace std;

/*
 * noexcept의 최적화 이점
 */

// throw 와 아예 예외 명세가 없는 함수는 최적화 유연성이 없다.
void CPP98() throw(int)
{
    throw 100;
}

/* noexcept 함수는 컴파일러에게 더 최적화할 수 있는 여지를 준다.
 * 
 * 컴파일러의 최적화기(Optimizer) 는 프로그램이 실행될 수 있는 모든 경로를 표현한
 * 제어 흐름 그래프(Control Flow Graph) 를 이용해 최적화를 진행한다.
 *
 * 이때 noexcept 함수는 예외로 인한 경로의 수를 줄여 최적화에 도움을 줄 수 있다.
 *
 * 또, 스택 풀기가 가능한 상태(Unwindable state) 로 함수를 실행할 필요가 없으므로
 * 컴파일러가 더 유연성을 확보할 수 있다. */
void CPP11() noexcept
{
    throw 100;
}

int main(int argc, char* argv[])
{
    try              { CPP98();              }
    catch (int expt) { cout << expt << endl; }

    try              { CPP11(); }
    catch (int expt) { cout << expt << endl; }

    return 0;
}
