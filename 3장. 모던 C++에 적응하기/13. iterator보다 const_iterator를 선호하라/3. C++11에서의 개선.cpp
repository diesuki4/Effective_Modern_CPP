#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * C++11에서의 개선
 */

using Vec = vector<int>;
using VecItr = vector<int>::iterator;
using VecConstItr = vector<int>::const_iterator;

int main(int argc, char* argv[])
{
    Vec v{0, 1, 2, 3};

    /* cbegin(), cend() 함수로 쉽게 const_iterator 를 얻을 수 있다. */
    VecConstItr cbegin = v.cbegin();
    VecConstItr cend   = v.cend();

    VecConstItr cit = find(cbegin, cend, 4);

    /* insert(), erase() 같은 STL 함수들도
     * const_iterator 를 기본으로 받도록 변경됐다.
     *
     * iterator ==> const_iterator 는 암시적 형 변환된다. */
    v.insert(cit, 5);

    return 0;
}
