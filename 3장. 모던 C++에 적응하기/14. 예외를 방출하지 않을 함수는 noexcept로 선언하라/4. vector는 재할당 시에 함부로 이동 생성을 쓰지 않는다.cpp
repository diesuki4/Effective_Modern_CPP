#include <iostream>
#include <vector>

using namespace std;

/*
 * vector는 재할당 시에 함부로 이동 생성을 쓰지 않는다
 */

class Widget
{
    int data;

public:
    Widget(int data) : data(data)
    {
        cout << "생성 " << data << endl;
    }

    /* vector 의 메모리 재할당은 생성으로 진행되지, 대입이 아니다. */
    Widget(const Widget& rhs) : data(rhs.data)
    {
        cout << "복사 " << data << endl;
    }

    Widget(Widget&& rhs) : data(move(rhs.data))
    {
        cout << "이동 " << data << endl;
    }

    /* 삽입, 재할당 과정에서 대입은 사용되지 않는다. */
    Widget& operator= (const Widget& rhs)
    {
        data = rhs.data;
        cout << "복사 대입 " << data << endl;
        return *this;
    }

    Widget& operator= (Widget&& rhs)
    {
        data = move(rhs.data);
        cout << "이동 대입 " << data << endl;
        return *this;
    }
};

int main(int argc, char* argv[])
{
    /* vector 는 capacity 가 모자라면, 더 큰 새로운 동적 메모리를 할당해
     * 그곳으로 원소들을 옮기는 작업을 한다.
     *
     * 1. 더 큰 새로운 동적 메모리 할당
     * 2. 삽입 원소를 먼저 마지막에 추가
     * 3. 기존 원소들을 새로운 공간으로 옮김
     * 4. 모두 옮긴 후 기존 메모리 해제 */
    vector<Widget> v;
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* C++98 에서는 이동 시맨틱이 없었기 때문에, 모두 복사로 원소를 옮겼다.
     *
     * 모든 원소를 복사로 옮겼기 때문에, <강한 예외 안전성> 을 보장했다. */
    v.push_back(0);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* C++11 부터는 이동을 이용해 이 과정이 효율적으로 수행될 수 있다.
     *
     * 다만, 이동을 이용하기 때문에 도중에 예외가 발생해 끊기게 되면
     * 원본 원소들은 손상된 채로 남게 된다. */
    v.push_back(1);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* 그렇기에 vector 는 함부로 옮기기에 이동 생성을 쓰지 않는다. */
    v.push_back(2);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    return 0;
}
