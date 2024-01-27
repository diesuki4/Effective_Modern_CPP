#pragma once
#include <memory>
#include <string>

using namespace std;

struct WidgetImpl;

class Widget
{
    unique_ptr<WidgetImpl> pImpl;

public:
    Widget(int index, const string& name);

    /* 컴파일러가 소멸자를 볼 때 WidgetImpl 이 완전한 타입이도록 하면 된다.
     * 즉, WidgetImpl 정의를 본 이후에 소멸자를 보도록 지연시키면 된다. */
    ~Widget();
};
