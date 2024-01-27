#include "Widget.h"

struct WidgetImpl
{
    int index;
    string name;
};

Widget::Widget(int index, const string& name) : pImpl(new WidgetImpl{index, name})
{
}
