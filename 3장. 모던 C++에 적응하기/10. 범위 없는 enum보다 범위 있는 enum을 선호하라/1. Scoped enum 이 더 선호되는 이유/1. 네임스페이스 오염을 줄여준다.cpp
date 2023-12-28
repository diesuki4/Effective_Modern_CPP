#include <iostream>

using namespace std;

/*
 * 이름 공간 오염을 줄여준다
 */

namespace Myspace
{  // EUnscoped

    void Func()
    {  // num
        /*
         * 일반적으로 중괄호 내에서의 선언이나 정의는
         * 그 범위에 속하는데
         */
        int num;
    }  // num

    /*
     * Unscoped enum 의 중괄호 안의 이름들은
     * enum 정의가 포함된 중괄호 범위에 속한다.
     *
     * 이렇게 자신을 정의하는 범위 밖으로 새어 나간다는 것 때문에
     * 범위가 없다(Unscoped) 고 한다.
     */
    enum EUnscoped
    {
        Red, Black, Blue
    };

    // 따라서, 이름 공간이 오염되어 다음이 불가능하다.
    // auto Red = 4;

    /*
     * 이름이 범위 밖으로 새어 나가지 않으므로
     * 범위가 있다(Scoped) 고 한다.
     */
    enum class EScoped
    {  // EScoped
        Green, Yellow, White
    }; // EScoped

}; // EUnscoped

int main(int argc, char* argv[])
{


    return 0;
}
