#include <iostream>
#include <atomic>

using namespace std;

/*
 * 책에서 말하는 atomic의 복사 초기화가 불가능한 이유
 */

int main(int argc, char* argv[])
{
    /*
     * 책에서는 atomic 을 예로 들어
     * 복사할 수 없는 객체는 등호(=) 로 복사 초기화가 불가능하다고 하는데
     * 
     * 이는 생각해 볼 여지가 있다.
     */

    atomic<int> ai1 = 1;
    /*
     * 이게 된다면 생성자가 explicit 이 아니기 때문이다.
     * 
     * explicit 생성자가 아니라면 다음 형 변환이 가능하다.
     * atomic<int> ai1 = atomic<int>(1);
     * 
     * 컴파일러는 이 형 변환이 가능하다는 것만 확인하면,
     * 복사 생성자에 접근할 수 있는지에 관계없이
     * 
     * 바로 다음처럼 최적화시켜 버린다.
     * atomic<int> ai1(1);
     */

    /*
     * atomic<int> ai2 = atomic<int>(2);
     * 
     * 이게 안 되는 건 복사 생성자에 접근할 수 없기 때문이다.
     * 
     * 컴파일러는 이 구문만 보고는 복사 생성자를 호출할 수 없다며 오류를 발생시키지만,
     * 정작 복사 생성자를 public 으로 바꾸면
     * 
     * 복사 생성자는 쓰지도 않고 다음처럼 최적화시켜 버린다.
     * atomic<int> ai2(2);
     */

    return 0;
}
