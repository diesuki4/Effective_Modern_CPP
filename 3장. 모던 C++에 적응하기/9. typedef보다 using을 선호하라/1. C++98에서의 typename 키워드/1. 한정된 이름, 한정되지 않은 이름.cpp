/*
 * https://pages.cs.wisc.edu/~driscoll/typename.html
 */
#include <iostream>

using namespace std;

/*
 * 한정된 이름(Qualified name), 한정되지 않은 이름(Unqualified name)
 */

namespace Myspace
{
    int num = 0;
};

struct Mystruct
{
    static const double d;
};

int main(int argc, char* argv[])
{
    /*
     * <한정된 이름>
     * 
     * 이렇게 범위 지정 연산자(::) 를 통해
     * 범위(Scope) 를 지정하는 이름이다.
     */
    Myspace::num;
    Mystruct::d;

    /*
     * <한정되지 않은 이름>
     *
     * 범위를 지정하지 않은 이름이다.
     */
    using namespace Myspace;

    num;

    return 0;
}
