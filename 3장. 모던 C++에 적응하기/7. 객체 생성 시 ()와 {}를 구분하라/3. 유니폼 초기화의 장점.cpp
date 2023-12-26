#include <iostream>
#include <vector>

using namespace std;

/*
 * 유니폼 초기화의 장점
 *
 * 1. C++이 지원하는 초기화 표현식 중 어디서나 사용할 수 있는 유일한 방법이다.
 * (멤버 변수, 복사 불가 객체 초기화 등에서 되는지 안 되는지를 고민할 필요가 없다.)
 * 
 * 2. 축소 변환(Narrowing conversion) 을 방지해준다.
 * 
 * 3. 가장 성가신 구문 해석(Most vexing parse) 에서 자유롭다.
 */

class Widget { };

int main(int argc, char* argv[])
{
    /*
     * 1. C++이 지원하는 초기화 표현식 중 어디서나 사용할 수 있는 유일한 방법이다.
     */
    int i{3};
    unique_ptr<int> uptr{new int};
    vector<int> v{1, 2, 3, 4, 5};

    /*
     * 2. 축소 변환을 방지해 준다.
     */

    // char 형에 담을 수 없다.
    // char c{500};

    double d = 3.0;
    // 실수부 손실 발생
    // int i{d};

    /*
     * 3. 가장 성가신 구문 해석에서 자유롭다.
     */

    // 프로그래머: 기본 생성자를 호출하는 Widget 타입의 객체 w1
    // 컴파일러: Widget 객체를 반환하는 함수 w1() 의 extern 선언
    Widget w1();

    // 유니폼 초기화는 이 문제에도 대응이 가능하다.
    Widget w2{};

    return 0;
}
