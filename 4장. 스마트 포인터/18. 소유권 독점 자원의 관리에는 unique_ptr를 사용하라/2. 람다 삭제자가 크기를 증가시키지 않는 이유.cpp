/*
 * https://stackoverflow.com/questions/33289652/c-stdunique-ptr-why-isnt-there-any-size-fees-with-lambdas#answer-33290240
 */
#include <iostream>
#include <memory>

using namespace std;

/*
 * 람다 삭제자가 크기를 증가시키지 않는 이유
 * 
 * EBO(Empty Base Optimization) 를 활용한 최적화
 */

/*
 * Base 가 상태(멤버 변수) 를 갖지 않는 빈 클래스이면
 * 부모로 상속시켜 EBO 가 적용되도록 한다.
 * 
 * 자식의 크기만큼만 차지하게 된다.
 */
template <class Base, class Derived, bool = is_empty_v<Base> && !is_final_v<Derived>>
class _My_compressed_pair : private Base
{
public:
    Derived val1;
};

/*
 * Base 가 빈 클래스가 아니면
 * 그냥 두 클래스의 크기만큼 차지하게 된다.
 */
template <class Base, class Derived>
class _My_compressed_pair<Base, Derived, false>
{
public:
    Base val1;
    Derived val2;
};

/*
 * 객체 포인터와 삭제자를 _Compressed_pair 로 묶으면
 * 객체 포인터는 항상 크기를 차지하는 반면,
 * 
 * 삭제자는 빈 클래스(람다 등) 일 경우 EBO 가 적용되어 공간을 차지하지 않고,
 * 
 * 상태(멤버 변수) 가 있는 클래스나 함수 포인터일 경우 크기를 차지하게 된다.
 */
template <typename Tp, typename Dp = default_delete<Tp>>
class my_unique_ptr
{
    // <삭제자, 객체 포인터>
    _My_compressed_pair<Dp, Tp*> __ptr__;

public:
    // ...
};

void custom_deleter(int* p) { delete p; }
auto lambda_deleter = [](int* p) { delete p; };

int main(int argc, char* argv[])
{
    cout << sizeof(my_unique_ptr<int, decltype(custom_deleter)*>) << endl;  // 8 Bytes
    cout << sizeof(my_unique_ptr<int, decltype(lambda_deleter)>) << endl;   // 4 Bytes

    return 0;
}
