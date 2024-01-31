/*
 * https://cplusplus.com/forum/general/202662/
 * https://en.cppreference.com/w/cpp/language/copy_elision
 */
#include <iostream>

using namespace std;

/*
 * 람다 이동의 의미
 * 
 * C++17 부터 공식화된 복사 생략(Copy Elision) 에 의해
 * 
 * 실제로는 람다 클로져도 임시 객체 생성 후 복사되는 것이 아니라,
 * 인자를 그대로 생성자에 보내 바로 생성된다.
 * 
 * 따라서, 굳이 람다 클로져에 move 를 사용하면
 * [생성] 과정이 [생성] => [이동] 으로 늘어나게 된다.
 */

class Widget
{
    int data;

public:
    Widget(int data = 0) : data{data}           { cout << "생성" << endl; }
    Widget(const Widget& rhs) : data{rhs.data}  { cout << "복사" << endl; }
    Widget(Widget&& rhs) : data{move(rhs.data)} { cout << "이동" << endl; }

    Widget& operator= (const Widget& rhs)
    {
        cout << "복사 대입" << endl;
        data = rhs.data;
        return *this;
    }

    Widget& operator= (Widget&& rhs)
    {
        cout << "이동 대입" << endl;
        data = move(rhs.data);
        return *this;
    }
};

int main(int argc, char* argv[])
{
    Widget wcopy = Widget(5);
    // Widget wcopy(5);
    cout << "ㅡㅡㅡㅡㅡ" << endl;

    Widget wmove = move(Widget(5));
    // Widget t(5);
    // Widget wmove = move(t);
    cout << "ㅡㅡㅡㅡㅡ" << endl;

    Widget w;
    cout << "ㅡㅡㅡㅡㅡ" << endl;

    auto fcopy = [w]() { cout << "fcopy" << endl; };
    // auto fcopylambda(w);
    cout << "ㅡㅡㅡㅡㅡ" << endl;

    auto fmove = move([w]() { cout << "fmove" << endl; });
    // auto fmovelambda t(w);
    // auto fmovelambda = move(t);

    return 0;
}
