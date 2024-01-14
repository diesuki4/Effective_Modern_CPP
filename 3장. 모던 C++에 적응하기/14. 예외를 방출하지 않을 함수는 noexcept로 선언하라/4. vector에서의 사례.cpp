#include <iostream>
#include <vector>

using namespace std;

/*
 * vector에서의 사례
 */

class Widget
{
    int data;

public:
    Widget(int data)          : data(data)           {                                  }
    Widget(const Widget& rhs) : data(rhs.data)       { cout << "복사 " << data << endl; }
    Widget(Widget&& rhs)      : data(move(rhs.data)) { cout << "이동 " << data << endl; }
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
     * 모든 원소를 복사로 옮겼기 때문에, 강한 예외 안전성을 보장했다. */
    v.push_back(0);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* C++11 부터는 이동을 이용해 이 과정이 효율적으로 수행될 수 있다.
     * 
     * 다만, 이동을 이용하기 때문에 도중에 예외가 발생해 끊기게 되면
     * 원본 원소들은 손상된 채로 남게 된다. */
    v.push_back(1);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* 따라서, vector 는 메모리 재할당 시에
     * 이동이 안전하다는 보장이 있을 때만 이동을 사용한다.
     * 
     * 다음 2가지 경우에만 이동이 사용된다.
     * 
     * 1. 이동 생성자가 noexcept 일 때
     * 2. 이동 생성자가 noexcept 은 아니지만, 복사 생성자가 없을 때 */
    v.push_back(2);
    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl << endl;

    /* 이렇게 표준 라이브러리의 여러 함수들은
     * 
     * <가능하면 이동하되 필요하면 복사한다>
     * 라는 전략을 활용한다. */

    return 0;
}
