#include <iostream>
#include "Widget.h"

using namespace std;

/*
 * unique_ptr은 pImpl에 간단히 사용할 수 없다
 */

void Func()
{
    Widget w(1, "Hello World");

    /* 컴파일 시점에 오류가 발생하는 지점
     * Widget 의 소멸자 작성이 필요한 순간
     * 
     * 1. Widget 소멸자 작성 도중
     * 2. unique_ptr<WidgetImpl> 소멸자 작성 도중
     * 3. default_delete<WidgetImpl>::operator()(WidgetImpl* ptr) 작성 도중
     * 4. delete ptr 부분에서 WidgetImpl 이 완전한 타입이어야 한다. */
}

int main(int argc, char* argv[])
{
    Func();

    return 0;
}
