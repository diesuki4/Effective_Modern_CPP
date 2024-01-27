#pragma once
// 표준 라이브러리는 전방 선언하면 안 된다.
#include <memory>
#include <string>

using namespace std;

struct WidgetImpl;

class Widget
{
    /* unique_ptr 은 _Compressed_pair<DeleterType, WidgetImpl*> 를 멤버로 가져,
     * DeleterType 이 unique_ptr<WidgetImpl> 타입의 일부가 된다.
     * 
     * 그렇기 때문에 Widget 의 소멸자를 작성할 때,
     * 
     * Widget 소멸자 => unique_ptr 소멸자 => default_delete => delete ptr
     * 로 이어져 WidgetImpl 이 완전한 타입이어야 하는 것이다. */
    unique_ptr<WidgetImpl> pImpl;

public:
    Widget(int index, const string& name);

    /* 컴파일러는 Widget 의 사용자 정의 소멸자가 없으면
     * 암시적 소멸자를 inline 으로 추가한다.
     * 
    ~Widget() = default;
     *
     * 하지만, 여기서 중점은 소멸자의 inline 여부나 정의가 분리돼있는지가 아니라
     * Widget 의 소멸자 작성 시점에 WidgetImpl 이 완전한 타입인지다.
     *
     * 이 시점에 컴파일러가 위의 unique_ptr<WidgetImpl> pImpl; 만 보고도
     * 소멸자를 작성할 수 있어야 하기 때문에 불완전한 타입이면 안 되는 것이다. */
    ~Widget();
};

/* 소멸자를 외부에 정의해도 컴파일러가
 * WidgetImpl 을 보기 전인 지점에 정의하면 문제는 해결되지 않는다. */
Widget::~Widget() = default;
