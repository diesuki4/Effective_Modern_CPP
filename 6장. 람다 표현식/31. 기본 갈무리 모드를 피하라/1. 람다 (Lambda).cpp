/*
 * https://lunchballer.com/archives/284
 * https://stackoverflow.com/questions/66758070/the-size-of-closure-lambda-function-not-same-as-stdfunction-or-pointer#answer-66758404
 * https://stackoverflow.com/questions/17197997/lambda-captures-and-member-variables#answer-17198032
 */
#include <iostream>

using namespace std;

/*
 * 람다 (Lambda)
 *
 * 코드에 존재하는 표현식을 람다라고 한다.
 * 따라서, 런타임에 람다는 존재하지 않는다.
 *
 * 람다가 실체화된 런타임 객체를 클로져(익명 함수 객체) 라고 한다.
 *
 * 의미적으로 정확히 다음과 같다.
 * 클래스 => 람다, 객체 => 클로져
 */

// 개별 캡처가 없는 빈 람다 객체의 크기는 1 이다.
class f1lambda
{
    using fp = int(*)(int);

    static auto anonymous_static_function(int y)
    {
        return 10 * y;
    }

public:
    auto operator() (int y) const
    {
        return anonymous_static_function(y);
    }

    // 빈 람다 객체는 함수 포인터에 담길 수 있다.
    operator fp () const
    { 
        return anonymous_static_function;
    }
};

// 캡처 변수마다 크기 추가된다.
class f2lambda
{
    const int x;

public:
    f2lambda(int x) : x{x}
    {
    }

    // 람다 함수는 선언과 정의가 하나인 멤버 함수로 처리되기 때문에, 기본적으로 inline 이다.
    auto operator() (int y) const
    {
        return x * y;
    }
};

int g_num = 0;

int main(int argc, char* argv[])
{
    auto f1 = [](int y) { return 10 * y; };
    auto f1l = f1lambda();

    cout << f1(2) << ", size = " << sizeof(f1) << endl;
    cout << f1l(2) << ", size = " << sizeof(f1l) << endl;

    int x = 10;

    auto f2 = [x](int y) { return x * y; };
    auto f2l = f2lambda(x);

    cout << f2(3) << ", size = " << sizeof(f2) << endl;
    cout << f2l(3) << ", size = " << sizeof(f2l) << endl;

    /* 런타임에서 변수 lambda 는 임시 클로져 t 의 복사본이다.
     * 따라서, t 는 이 구문이 끝나면 소멸한다.
     *
     * 실제로는 복사 생략에 의해 임시 객체의 생성과 복사 없이
     * lambda 변수에 바로 클로져가 생성된다. */
    auto lambda = [](int num)
    {
        return ++num;
    };

    // 람다는 실행이 아니라, 클로져 객체 생성 시에 변수들을 캡처한다.
    auto f3 = [x]() { cout << "[f3] x = " << x << endl; };
    ++x;
    f3();

    // 당연히 레퍼런스로 캡처하면, 호출 직전까지의 변경 사항이 적용된다.
    auto f4 = [&x]() { cout << "[f4] x = " << x << endl; };
    ++x;
    f4();

    /* 개별 캡처는 static 이 아닌 지역 변수만 가능하다.
     * 전역, static, 멤버 변수는 불가
     * 
    auto f5 = [&g_num]() {};
    auto f5 = [g_num]() {};
     *
     * 개별 캡처를 사용하지 않으면 전역, static, 멤버 변수를 모두 가져와 쓸 수 있다.
     * 이때, 이들은 값 캡처에서도 const 가 아니다.
     *
     * 멤버 변수는 암묵적으로 this 를 전달해 접근된다. */
    auto f5 = [ ]() { cout << "[f5] g_num = " << ++g_num; };
    f5();
    cout << ", size: " << sizeof(f5) << endl;
    auto f6 = [=]() { cout << "[f6] g_num = " << ++g_num; };
    f6();
    cout << ", size: " << sizeof(f6) << endl;
    auto f7 = [&]() { cout << "[f7] g_num = " << ++g_num; };
    f7();
    cout << ", size: " << sizeof(f7) << endl;

    return 0;
}
