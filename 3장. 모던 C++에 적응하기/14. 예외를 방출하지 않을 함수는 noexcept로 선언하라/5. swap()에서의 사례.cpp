#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

/*
 * swap()에서의 사례
 */

/* 조건부 noexcept */
namespace mystd
{
    class Widget {};
    class Button {};

    void swap(Widget& a, Widget& b) noexcept;
    void swap(Button& a, Button& b);

    template <typename T, size_t N>
    void swap(T (&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b)));
    // void swap(Widget(&a)[3], Widget(&b)[3]) noexcept(true);
    // void swap(Button(&a)[3], Button(&b)[3]) noexcept(false);

    template <typename T1, typename T2>
    void swap(pair<T1, T2>& p1, pair<T1, T2>& p2) noexcept(noexcept(p1.first, p2.first) && noexcept(p1.second, p2.second));
    // void swap(pair<Widget, Button>& p1, pair<Widget, Button>& p2) noexcept(true && false);

    /* 이렇듯 swap() 의 noexcept 여부는
     * 개별 요소들에 대한 swap() 의 noexcept 여부에 의존한다.
     *
     * 그렇기 때문에 더 높은 수준의 자료구조에서도 noexcept 이 되게 하기 위해서는
     * swap() 함수는 가능한 noexcept 으로 작성하는 것이 바람직하다. */
}

int main(int argc, char* argv[])
{
    using namespace mystd;

    return 0;
}
