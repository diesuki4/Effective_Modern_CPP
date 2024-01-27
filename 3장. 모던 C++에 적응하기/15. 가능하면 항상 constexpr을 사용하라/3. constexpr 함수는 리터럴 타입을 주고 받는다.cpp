/*
 * https://en.cppreference.com/w/cpp/language/constexpr
 * https://en.cppreference.com/w/cpp/language/destructor#Trivial_destructor
 */
#include <iostream>
#include <array>

using namespace std;

/*
 * constexpr 함수는 리터럴 타입을 주고 받는다
 */

/* <리터럴 타입>
 * 
 * 컴파일 타임에 값을 결정할 수 있는 타입
 * 
 * 모든 기본 타입 (C++11 에서는 void 제외)
 * 생성자와 적절한 멤버 함수가 constexpr 인 사용자 정의 타입 */

class Point
{
    unsigned x, y;

public:
    // 컴파일 시점에 생성자를 호출할 수 있다.
    constexpr Point(unsigned x = 0, unsigned y = 0) : x(x), y(y) {}

    constexpr unsigned GetX() const { return x; }
    constexpr unsigned GetY() const { return y; }

    /* C++11 에서는 2가지 제약 때문에 Setter 를 constexpr 로 사용할 수 없었다.
     * 
     * 1. constexpr 멤버 함수는 멤버 수정이 불가능하도록, 암묵적으로 const 로 선언됐다.
     * 2. 반환인 void 가 리터럴 타입이 아니었다.
     *
     * C++14 부터는 두 제약 모두 없어져, Setter 도 constexpr 로 선언할 수 있다.
     *
     * 1. constexpr 멤버 함수가 암묵적으로 const 가 되지 않는다.
     * 2. void 가 리터럴 타입에 속하게 됐다. */
    constexpr void SetX(unsigned newX) { x = newX; }
    constexpr void SetY(unsigned newY) { y = newY; }

    /* Trivial(자명한) 소멸자란?
     * 
     * 아무것도 하지 않는 소멸자
     *
     * 1. 사용자 정의가 아닌, 암시적 추가
     * 2. Non-virtual
     * 3. 모든 멤버의 소멸자도 Trivial */

    /* 컴파일 타임에 사용 가능한 사용자 정의 리터럴 타입은
     * 꼭 Trivial 소멸자를 가져야 한다.
     * 
     * 즉, 아무것도 하지 않는 소멸자만 컴파일 타임에 호출이 가능하다는 것.
     *
     * 따라서, 소멸자를 명시할 수 없고
     * 꼭 암시적으로 생성된 Trivial 소멸자를 사용해야 한다.
    ~Point() {} */
};

// 컴파일 타임에 중간 지점을 구하는 함수
constexpr Point MidPoint(const Point& p1, const Point& p2)
{
    return {(p1.GetX() + p2.GetX()) / 2,
            (p1.GetY() + p2.GetY()) / 2};
}

// 컴파일 타임에 X, Y 좌표를 바꾼 지점을 구하는 함수
constexpr Point SwapXY(const Point& p)
{
    Point result;

    result.SetX(p.GetY());
    result.SetY(p.GetX());

    return result;
}

int main(int argc, char* argv[])
{
    // 컴파일 시점에 생성자가 실행된다.
    constexpr Point p1(3, 4);
    constexpr Point p2(7, 8);

    /* 컴파일 시점에 사용자 정의 리터럴 타입을 통해 함수를 호출할 수 있다.
     *
     * 이렇게 런타임에 실행됐던 것들 일부를 컴파일 시점으로 옮겨,
     * 프로그램 실행 속도를 높일 수 있다. */
    constexpr Point mid = MidPoint(p1, p2);

    int arr[mid.GetX() * 10];
    array<int, SwapXY(mid).GetX()> arr2;

    return 0;
}
