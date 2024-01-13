#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

/*
 * C++11에서 const_iterator가 조금은 아쉬운 점
 */

namespace myspace
{
    /* C++11 에서는 std::begin() 과 std::end() 는 표준이 됐지만,
     * std::cbegin() 과 std::cend() 는 그렇지 않다.
     *
     * C++14 부터 std::cbegin(), std::rbegin() 등도 표준이 됐다. */
    template <typename C>
    auto cbegin(const C& container)
    {
        /* container.cbegin(); 으로 구현하지 않은 이유는 2가지다.
         *
         * 1. int[5] 같이 cbegin() 멤버 함수가 없어도 사용할 수 있다.
         * 2. std::begin() 에 const 객체가 전달되면, 알아서 const_iterator 가 반환된다. */
        return begin(container);
    }

    template <typename C>
    auto cend(const C& container)   { return end(container); }

    // 컨테이너에 상관 없이 사용할 수 있는, 일반성이 극대화된 자유 함수
    template <typename C, typename V>
    void findAndInsert(C& container, const V& targetVal, const V& insertVal)
    {
        auto cit = find(cbegin(container), cend(container), targetVal);

        container.insert(cit, insertVal);
    }
}

int main(int argc, char* argv[])
{
    list<int> l;

    // 일반성이 극대화된 sort() 자유(비멤버) 함수
    sort(l.begin(), l.end());
    // 일반성은 없지만 더 효율적인 sort() 멤버 함수
    l.sort();

    int arr[5] = {0};

    using myspace::cbegin;

    const int* cp = cbegin(arr);

    return 0;
}
