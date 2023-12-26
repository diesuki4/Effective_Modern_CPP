#include <iostream>
#include <vector>

using namespace std;

/*
 * 유니폼 초기화 (Uniform Initialization)
 *
 * {} 를 이용해
 * 어떤 타입에도 사용할 수 있고, 어떤 것도 표현할 수 있는
 * 통일된 초기화 구문
 *
 * 어디서든 되는지 안 되는지 고민 없이 사용할 수 있다.
 */

class Widget
{
    int x = 0;
    // Non-static 멤버의 초기화에도 사용 가능
    int y{0};
    // 불가
    // int z(0);
};

int main(int argc, char* argv[])
{
    // C++98 에서는 다음처럼 vector 를 초기화해야 했다.
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);

    // 유니폼 초기화를 사용하면 (initializer_list 생성자가 존재하므로 가능)
    vector<int> v2{1, 2, 3, 4};

    // explicit 생성자를 가진 객체 초기화에도 사용할 수 있다.
    unique_ptr<int> uptr1(new int);
    unique_ptr<int> uptr2{new int};
    // 불가
    // unique_ptr<int> uptr3 = new int;

    return 0;
}
