/*
 * https://underin1365.tistory.com/15
 */
#include <iostream>
#include <stdexcept>

using namespace std;

/*
 * 커스텀 terminate_handler
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

void my_terminate_handler()
{
    cout << "안 잡힌 예외 때문에 프로그램 터졌다~" << endl;

    /* 처리기에서 프로그램을 종료시켜 주지 않으면
     * 어차피 abort() 가 실행된다. */
    exit(-1);
}

int main(int argc, char* argv[])
{
    // 새로운 처리 함수를 등록하고, 기존 함수를 반환한다.
    void* old_handler = set_terminate(my_terminate_handler);

    Func1();

    return 0;
}
