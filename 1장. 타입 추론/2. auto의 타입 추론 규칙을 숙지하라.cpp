#include <iostream>
#include <vector>

using namespace std;

/*
 * auto의 타입 추론 규칙을 숙지하라
 *
 * auto 의 타입 추론과 템플릿 타입 추론은
 * 중괄호 초기자 {} 가 관여하는 단 하나의 예외를 제외하고는 동일하다.
 */

template <typename T>
void Func(T param) {}

template <typename T>
void Gunc(initializer_list<T> param) {}

/* C++14 부터는 함수의 반환 타입, 람다의 매개변수에 auto 를 지정할 수 있으나
 * 
 * 여기에는 auto 가 아닌, 템플릿 타입 추론 규칙이 적용된다. */
auto createInitList()
{
    /* 템플릿 규칙은 initializer_list 를 추론할 수 없음
    return {1, 2, 3}; */
    return vector<int>{1, 2, 3};
}

auto lambda = [](auto param) { return 100; };
/* initializer_list 추론 불가
int result = lambda({1, 2, 3}); */

int main(int argc, char* argv[])
{
    auto x1 = 1;   // int
    cout << typeid(x1).name() << endl;

    auto x2(2);    // int
    cout << typeid(x2).name() << endl;

    auto x3 = {3}; // initializer_list<int>
    cout << typeid(x3).name() << endl;

    // C++11: initializer_list<int>
    // C++14: int
    auto x4{4};
    cout << typeid(x4).name() << endl;

    /* 컴파일 오류 !!
     * 
     * auto 는 중괄호 초기자 {} 가 initializer_list 를 나타낸다고 가정하지만,
     * 템플릿 타입 추론은 그렇지 않다.
     * 
    Func({1});*/

    Gunc({1});

    /* <참고>
     * initializer_list 를 이용해 컨테이너를 초기화할 수 있다. */
    initializer_list<int> il1 = {1, 2, 3};
    vector<int> v = il1;  // 생성자

    for (int e : v)
        cout << e << " ";
    cout << endl;

    initializer_list<int> il2 = {4, 5, 6};
    v = il2;  // 대입

    for (int e : v)
        cout << e << " ";
    cout << endl;

    return 0;
}
