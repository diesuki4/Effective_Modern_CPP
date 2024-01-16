#include <iostream>
#include <array>

using namespace std;

/*
 * 가능한 한 항상 사용하라의 의미
 * 
 * constexpr 은 noexcept 과 유사하게
 * 사용자가 고려해야 하는 함수(혹은 변수) 인터페이스의 일부다.
 *
 * constexpr 을 가능하게 하게 위해 적용한 제약들을
 * 최대한 오래 유지하겠다는 의지가 있을 때 사용하라
 * 
 * 얼마 안 가 다시 non-constexpr 로 만들 거면 쓰지 말라는 뜻.
 */

/* constexpr 로 만든다는 것은, 상수 표현식 위치에 쓰일 수 있다는 사실을 천명하는 것.
 *
 * 따라서 나중에 non-constexpr 함수로 바꾸게 되면, 상수 표현식 위치에서 사용된 사용자 코드들이 깨지게 된다.*/
constexpr unsigned mypow(unsigned base, unsigned exp)
{
    /* constexpr 함수 내에 입출력 기능을 추가하는 경우 흔히 그렇게 된다.
     *
     * 일반적으로 constexpr 함수 내에서는 입출력이 허용되지 않기 때문
     * 
     * cout << "A" << endl;*/
    if (exp == 0)
        return 1;

    return mypow(base, exp - 1);
}

int main(int argc, char* argv[])
{
    int arr[mypow(2, 3)];

    array<int, mypow(3, 2)> arr2;

    return 0;
}
