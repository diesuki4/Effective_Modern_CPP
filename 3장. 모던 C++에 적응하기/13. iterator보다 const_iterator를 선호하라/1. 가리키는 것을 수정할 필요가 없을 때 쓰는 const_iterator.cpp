#include <iostream>
#include <vector>

using namespace std;

/*
 * 가리키는 것을 수정할 필요가 없을 때 쓰는 const_iterator
 */

using Vec         = vector<int>;
using VecItr      = vector<int>::iterator;
using VecConstItr = vector<int>::const_iterator;

int main(int argc, char* argv[])
{
    int arr[] {0, 1, 2, 3};
    int* p = arr;
    const int* cp = arr;

    *p= 10;
    // *cp = 10;

    Vec v {0, 1, 2, 3};
    VecItr it = begin(v);
    VecConstItr cit = cbegin(v);

    *it = 10;
    // *cit = 10;

    return 0;
}
