/*
 * https://pages.cs.wisc.edu/~driscoll/typename.html
 */
#include <iostream>
#include <vector>

using namespace std;

/*
 * 의존적인 타입 (Dependent type)
 */

/*
 * 템플릿 매개변수 T 에 따라 타입이 달라지는 것을
 * 
 * <의존적> 이라고 한다.
 */
template <class T>
class Widget
{
    // 의존적이지 않은 타입
    int i;
    vector<int> vi;

    // 의존적인 타입
    T t;
    vector<T> vt;
};

int main(int argc, char* argv[])
{
    

    return 0;
}
