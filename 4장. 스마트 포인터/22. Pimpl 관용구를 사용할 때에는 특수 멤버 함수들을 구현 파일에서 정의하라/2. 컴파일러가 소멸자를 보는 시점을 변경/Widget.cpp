#include "Widget.h"

struct WidgetImpl
{
    int index;
    string name;
};

Widget::Widget(int index, const string& name) : pImpl(new WidgetImpl{index, name})
{
}

/* 이제 위에서 WidgetImpl 을 봤으므로,
 * 소멸자를 작성할 때 WidgetImpl 은 완전한 타입이 된다. */
Widget::~Widget() = default;
