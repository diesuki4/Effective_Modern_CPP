#include <iostream>

using namespace std;

/*
 * Unhandled Exception
 */

class Widget
{
    int num;

public:
    Widget(int num) : num(num) { cout << "생성자 " << num << endl; }
    ~Widget()                  { cout << "소멸자 " << num << endl; }
};

void Func3()
{
    Widget w(1);
    throw 100;
}

void Func2()
{
    Widget w(2);
    Func3();
}

void Func1()
{
    Widget w(3);
    Func2();
}

/* 사용자 코드 어디서도 예외를 잡지 않고 더 깊이 전파시켜 버리면
 *
 * 프로그램은 자동으로 void std::terminate() 함수를 호출한다.
 *
 * 이 함수는 terminate_handler 타입의 함수 포인터를 실행하도록 하고
 * 여기에는 void std::abort() 함수가 기본으로 등록되어 있다.
 *
 * 그래서 Unhandled Exception 이 발생하면 abort() 가 실행되어
 * 프로그램이 꺼져버리는 것이다. */
namespace mystd
{
    using terminate_handler = void(*)();

    void abort()
    {
        exit(-1);
    }

    terminate_handler TH = abort;

    void terminate()
    {
        TH();
    }

    terminate_handler set_terminate(terminate_handler newTH)
    {
        terminate_handler oldTH = TH;

        TH = newTH;

        return oldTH;
    }
}

int main(int argc, char* argv[])
{
    /* 예외가 잡히지 않았으므로, 스택 풀기 없이 프로그램이 종료된 후
     * OS 에 자원이 반환된다.*/
    Func1();

    return 0;
}
