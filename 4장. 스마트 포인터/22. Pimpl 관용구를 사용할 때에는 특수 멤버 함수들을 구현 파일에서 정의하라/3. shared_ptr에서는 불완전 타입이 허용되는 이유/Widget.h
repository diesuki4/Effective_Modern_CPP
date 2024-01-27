/*
 * https://jwvg0425.tistory.com/38
 * https://ozt88.tistory.com/32
 * https://stackoverflow.com/questions/40619984/pimpl-idiom-using-shared-ptr-working-with-incomplete-types#answer-40620088
 * https://stackoverflow.com/questions/71821115/incomplete-types-with-shared-ptr-and-unique-ptr
 * https://stackoverflow.com/questions/75408648/why-unique-ptr-requires-complete-type-in-constructor#answer-75409250
 * https://stackoverflow.com/questions/18559931/how-to-safely-destruct-class-with-smart-pointer-to-incomplete-object-type#answer-18560156
 * https://www.nextptr.com/tutorial/ta1358374985/shared_ptr-basics-and-internals-with-examples
 */
#pragma once
#include <memory>
#include <string>

using namespace std;

struct WidgetImpl;

class Widget
{
    /* shared_ptr 은 WidgetImpl*, ControlBlock* 를 멤버로 가진다.
     * unique_ptr 과 달리 DeleterType 은 템플릿 인자가 아닌 생성자의 인자로 전달되며
     * 자신이 아닌, ControlBlock 의 일부가 된다.
     * 
     * 그렇기 때문에 Widget 의 소멸자를 작성할 때,
     * 
     * Widget 소멸자 => shared_ptr 소멸자 => ControlBlock 소멸자 => function<void(WidgetImpl*)>
     * 로 이어지겠지만, shared_ptr 은 선언할 때가 아닌 초기화할 때 삭제자를 전달하므로
     * 
     * 소멸자를 작성할 때 삭제자의 정보가 필수가 아니다. */
    shared_ptr<WidgetImpl> pImpl;

public:
    Widget(int index, const string& name);

    /* 암시적 소멸자
     * 
    ~Widget() = default;
     *
     * 이 시점에 컴파일러가 위의 shared_ptr<WidgetImpl> pImpl; 만 보고도
     * 소멸자를 작성할 수 있기 때문에 불완전한 타입이어도 되는 것이다. */
};
