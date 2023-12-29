#include <iostream>

using namespace std;

/*
 * 항상 전방 선언이 가능하다
 * 
 * 전방 선언을 통해 컴파일 속도를 높일 수 있다.
 */

/*
 * 컴파일러들은 메모리 효율을 위해
 * 주어진 열거자들을 표현할 수 있는
 * 
 * 가장 작은 기반 타입(Underlying type) 을 선택하는 경향이 있다.
 */

enum EUnscoped1
{
    Red   = 1,
    Black = 50,
    Blue  = 100
};  // ==> char

enum EUnscoped2
{
    Gray   = 1,
    Cyan   = 9999,
    Purple = 0xFFFFFFFF
};  // ==> int

void processInt(EUnscoped1 color)
{
    return;
}

/*
 * 그렇기 때문에 기본(Default) 기반 타입이 없는 Unscoped enum 은
 * 컴파일러가 정의를 보기 전까지는 크기를 알 수 없으므로
 * 
 * 전방 선언을 할 수 없다.
 */

/*
 * 이것이 문제가 되는 이유는, 전방 선언을 하지 못 함으로 인해
 * 컴파일 속도에 영향을 미치기 때문이다.
 * 
 * 대부분의 파일에서 사용되는 "core.h" 라는 헤더에
 * enum 이 존재한다고 하면
 * 
 * 여기에 이름이 추가될 때마다
 * 모든 파일이 다시 컴파일 되어야 한다.
 * (어디 한 곳에서라도 새로 추가된 이름을 쓰고 있다면)
 * 
 * 이렇게 하나의 수정이 다른 파일을 컴파일 하도록 하는 것을
 * 컴파일 의존 관계가 늘어난다고 한다.
 */

/*
 * Scoped enum 은 기본 기반 타입이 int 로 정해져 있으므로
 * 컴파일러가 정의를 보지 않고도 크기를 알 수 있다.
 * 
 * 따라서, 이름들이 변경되어도 전방 선언을 사용한 파일들은
 * 다시 컴파일할 필요가 없다.
 */
enum class EScoped;

void processInt(EScoped color)
{
    return;
}

enum class EScoped
{
    Green, Yellow, White
};

/*
 * 사실, Unscoped enum 도 기본 기반 타입이 정해져 있지 않아서 그렇지
 * 기반 타입을 명시해주면 전방 선언이 가능하다.
 */
enum EUnscoped3 : int;
// 당연히 Scoped enum 도 기반 타입을 명시할 수 있다.
enum class EScoped2 : long;

int main(int argc, char* argv[])
{


    return 0;
}
