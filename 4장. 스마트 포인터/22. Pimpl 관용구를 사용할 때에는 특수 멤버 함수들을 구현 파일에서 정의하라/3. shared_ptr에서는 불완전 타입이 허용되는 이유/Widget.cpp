#include "Widget.h"

struct WidgetImpl
{
    int index;
    string name;
};

// WidgetImpl 은 이 시점에 완전한 타입이어야 한다.
Widget::Widget(int index, const string& name) : pImpl(new WidgetImpl{index, name})
{
}
