#include <iostream>

using namespace std;

/*
 * 초기화와 대입
 * 
 * 등호(=) 가 있다고 해서 무조건 대입이 아니다.
 */

class Widget
{
    int data;

public:
    Widget(int data) : data(data)
    {
        cout << "생성자" << endl;
    }

    Widget(const Widget& rhs) : data(rhs.data)
    {
        cout << "복사 생성자" << endl;
    }

    Widget& operator= (const Widget& rhs)
    {
        cout << "복사 대입 연산자" << endl;

        data = rhs.data;

        return *this;
    }
};

int main(int argc, char* argv[])
{
    int x(0);       // 직접 초기화
    int y{0};       // 유니폼 초기화
    int z = 0;      // 복사 초기화
    int w = {0};    // 대체로 int w{0} 과 동일하게 취급된다.

    z = w;          // 대입

    Widget w1 = 3;  // 생성자를 호출하는 초기화
    Widget w2 = w1; // 복사 생성자를 호출하는 초기화

    w1 = w2;        // 복사 대입 연산자를 통한 대입

    return 0;
}
