#include <iostream>
#include "Widget.h"

using namespace std;

/*
 * shared_ptr에서는 불완전 타입이 허용되는 이유
 */

void Func()
{
    Widget w(1, "Hello World");

    /* Widget 의 소멸자 작성이 필요한 순간
     * 
     * 1. Widget 소멸자 작성 도중
     * 2. shared_ptr<WidgetImpl> 소멸자 작성 도중
     * 3. ControlBlock 소멸자 작성 도중
     * 4. 전달된 소멸자 호출
     * 5. 소멸자를 작성할 때 삭제자의 정보가 필수가 아니다. */
}

int main(int argc, char* argv[])
{
    Func();

    return 0;
}
