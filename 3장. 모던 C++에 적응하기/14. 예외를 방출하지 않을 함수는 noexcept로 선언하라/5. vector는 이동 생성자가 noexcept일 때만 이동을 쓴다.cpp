#include <iostream>
#include <vector>

using namespace std;

/*
 * vector는 이동 생성자가 noexcept일 때만 이동을 쓴다
 */

class Widget
{
    int data;

    void swap(Widget& rhs) noexcept
    {
        using std::swap;

        swap(data, rhs.data);
    }

public:
    Widget(int data) : data(data)
    {
        cout << "생성 " << data << endl;
    }

    Widget(const Widget& rhs) : data(rhs.data)
    {
        cout << "복사 " << data << endl;
    }

    /* 이동 생성자가 noexcept 이어야
     * vector 가 재할당 시에 믿고 이동을 쓸 수 있다. */
    Widget(Widget&& rhs) noexcept : data(move(rhs.data))
    {
        cout << "이동 " << data << endl;
    }

    /* Copy & Swap 관용구를 이용한 예외에 안전한
     * 복사, 이동 대입 연산자 동시 구현
     *
     * 여기선 관계 없는 내용이다. */
    Widget& operator= (Widget rhs) noexcept
    {
        swap(rhs);
        cout << "대입 " << data << endl;
        return *this;
    }
};

int main(int argc, char* argv[])
{
    vector<Widget> v;
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* push_back() 대신 emplace_back(), Perfect Forwarding 을 사용하면
     * 
     * (생성 => 이동) 과정을 (생성) 하나로 줄일 수 있다. */
    v.emplace_back(0);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* vector 는 메모리 재할당 시에
     * 이동이 안전하다는 보장이 있을 때만 이동을 사용한다.
     *
     * 1. 이동 생성자가 noexcept 일 때
     * 2. 이동 생성자가 noexcept 은 아니지만, 복사 생성자가 없을 때 */
    v.emplace_back(1);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* 이렇게 표준 라이브러리의 여러 함수들은
     *
     * <가능하면 이동하되 필요하면 복사한다>
     * 
     * 전략을 사용한다. */
    v.emplace_back(2);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    return 0;
}
