#include <iostream>

using namespace std;

/*
 * 커스텀 bool 타입 구현하기
 * 
 * bool 타입의 동작 원리를 이해한다.
 */

namespace mystd
{
    // mybool 이라는 타입이 존재한다고 가정
    struct mybool
    {
        bool flag;

        // bool 타입으로 형 변환 가능
        operator bool()
        {
            return flag;
        }

        // 주소를 구할 수 없도록 한다.
        void operator& () const = delete;
    };

    // mytrue, myfalse 라는 리터럴이 존재한다고 가정
    mybool mytrue{true};
    mybool myfalse{false};
}

int main(int argc, char* argv[])
{
    using namespace mystd;

    mybool mb = mytrue;

    if (mb)
        cout << "mytrue" << endl;
    else if (mb == myfalse)
        cout << "myfalse" << endl;

    bool bb = mytrue;

    if (bb == true)
        cout << "true" << endl;
    if (bb == myfalse)
        cout << "myfalse" << endl;

    return 0;
}
