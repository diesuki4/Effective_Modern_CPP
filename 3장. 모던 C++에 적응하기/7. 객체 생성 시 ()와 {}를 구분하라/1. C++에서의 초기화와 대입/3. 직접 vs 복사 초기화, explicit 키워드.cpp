#include <iostream>

using namespace std;

/*
 * 직접 vs 복사 초기화, explicit 키워드
 *
 * 다음과 같은 복사 초기화에서는
 * Widget w = 1;
 *
 * RVO 같은 컴파일러 최적화가 항상 일어난다고 보면 된다.
 * => Widget w = Widget(1);
 * => Widget w(1);
 */

class Widget1
{
    int data;

public:
    Widget1(int data) : data(data) { cout << "Widget1::생성자" << endl; }
    Widget1(const Widget1& rhs) : data(rhs.data) { cout << "Widget1::복사 생성자" << endl; }

    Widget1& operator= (const Widget1& rhs)
    {
        cout << "Widget1::복사 대입 연산자" << endl;

        data = rhs.data;

        return *this;
    }
};

class Widget2
{
    int data;

public:
    explicit Widget2(int data) : data(data) { cout << "Widget2::생성자" << endl; }
    Widget2(const Widget2& rhs);

private:
    Widget2& operator= (const Widget2& rhs);
};

int main(int argc, char* argv[])
{
    Widget1 a(2);            // 생성자
    Widget1 b = 1;           // 생성자
    Widget1 c = Widget1(3);  // 생성자

    Widget2 d(2);            // 생성자

    /*
     * Widget2 e = 1;        // 생성자
     *
     * 실제로는 다음과 같다.
     * Widget2 e(Widget(1));
     *
     * 현재 explicit 생성자로 인해 1 이 Widget(1) 로
     * 암시적 형 변환될 수 없으므로 컴파일 오류가 발생한다.
     *
     * 하지만, explicit 키워드를 뺀다고 해도
     * 컴파일러 최적화에 의해
     *
     * 복사 생성자가 아닌, 일반 생성자로 변경된다.
     * Widget2 e(1);
     *
     * 이때, 복사 생성자를 거치지 않고 생성자로 바로 변경되므로
     * 복사 생성자에 접근할 수 없어도 컴파일 오류가 발생하지 않는다.
     */

    Widget2 f = Widget2(3);   // 생성자
    /*
     * 복사 생성자에 접근할 수 없으면, 컴파일 오류가 발생한다.
     *
     * 하지만, 복사 생성자를 public 으로 바꾸고 몸체를 구현하지 않고 두면
     * 링크 에러가 발생하지 않고 실행되어 생성자가 호출된다.
     *
     * 문법적으로는 아래와 같지만
     * Widget f(Widget2(3));
     *
     * 컴파일러 최적화에 의해
     * Widget f(3); 으로 변경되는 것 같다.
     */

    /*
     * 정리하자면 다음과 같다.
     */

    // 이게 안 된다면 explicit 생성자 때문이다.
    Widget1 g = 1;

    // 이게 안 된다면 복사 생성자에 접근할 수 없기 때문이다.
    Widget2 h = Widget2(1);

    return 0;
}
