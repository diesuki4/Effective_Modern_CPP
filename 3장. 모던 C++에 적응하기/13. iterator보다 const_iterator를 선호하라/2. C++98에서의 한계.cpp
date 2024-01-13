#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * C++98에서의 한계
 */

typedef vector<int>                 Vec;
typedef vector<int>::iterator       VecItr;
typedef vector<int>::const_iterator VecConstItr;

int main(int argc, char* argv[])
{
    Vec v {0, 1, 2, 3};

    /* C++98 에서는 비상수 컨테이너에서 const_iterator 를 얻는
     * cbegin(), cend() 같은 함수가 없었다. */

    // iterator ==> const_iterator 는 형 변환이 가능
    VecConstItr cit = static_cast<VecConstItr>(v.begin());

    const Vec& crv = v;
    cit = crv.begin();

    VecConstItr cbegin = static_cast<VecConstItr>(v.begin());
    VecConstItr cend   = static_cast<VecConstItr>(v.end());

    cit = find(cbegin, cend, 4);

    /* C++98 에서는 insert() 인자로 const_iterator 를 전달할 수 없었다.
     *
     * 형 변환을 시도하면?
     * 
     * const_iterator ==> iterator 는 형 변환이 불가 (C++11 에서도 마찬가지)
     * v.insert(static_cast<VecItr>(cit), 5);
     * 
     * reinterpret_cast 로도 안 된다.
     * v.insert(reinterpret_cast<VecItr>(cit), 5); */

    int* p;

    // 이건 되지만
    const int* cp = p;

    // 이건 안 되는 것과 같은 이유다.
    // p = cp;
    // p = reinterpret_cast<int*>(cp);

    /* const_iterator 는 const iterator 가 아니기 때문에 const_cast 도 불가
     * v.insert(const_cast<VecItr>(cit), 5); */

    /* 이런 이유들로 너무 쓰기가 불편했기에 차라리 안 쓰는 게 좋았다. */

    return 0;
}
