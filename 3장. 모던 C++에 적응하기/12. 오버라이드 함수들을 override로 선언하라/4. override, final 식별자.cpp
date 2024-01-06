#include <iostream>

using namespace std;

/*
 * override, final 식별자
 * 
 *  오버라이딩이 일어나기 위한 조건
 * 
 * 1. 부모 함수가 가상 함수여야 한다.
 * 2. 이름이 같아야 한다. (소멸자 제외)
 * 3. 상수성(const) 이 같아야 한다.
 * 4. 반환 타입, 시그니처, 예외 명세가 같아야 한다.
 * 5. 참조 한정사가 같아야 한다.
 */

class Base
{
public:
    virtual void F1() const;
    virtual void F2(int x);
    virtual void F3()&;
    void F4() const;

    virtual void F5() const;
    virtual void F6(int x);
    virtual void F7()&;
    void F8() const;

    virtual void F9(double d);
};

class Derived : public Base
{
public:
    /* 모두 오버라이딩이 일어나지 않지만
     * 컴파일은 잘 된다. */
    virtual void F1();           // 상수성이 다르다.
    virtual void F2(unsigned x); // 시그니처가 다르다.
    virtual void F3()&&;         // 참조 한정사가 다르다.
    void F4() const;             // 부모가 가상 함수가 아니다.

    /* 컴파일 에러가 발생하며 오버라이딩이 일어나지 않았다는 걸 알려준다. */
    virtual void F5() override;           // 부모 함수를 오버라이드하지 않았습니다.
    virtual void F6(unsigned x) override; // 부모 함수를 오버라이드하지 않았습니다.
    virtual void F7() && override;        // 부모 함수를 오버라이드하지 않았습니다.
    void F8() const override;             // 부모 함수를 오버라이드하지 않았습니다.

    /* 자식 함수에서 override 식별자를 일관되게 적용하면
     * 부모의 시그니처를 변경했을 때,
     *
     * 컴파일 에러를 통해 영향이 어느 정도인지 파악할 수도 있다.*/

    /* final 식별자를 사용하면 하위 클래스부터는
     * 오버라이드하지 못 하도록 막을 수 있다. */
    void F9(double d) override final;
    /* 새로 선언한 함수에도 final 지정 가능
     * 하지만, 이럴 거면 비가상 함수로 선언하는 게..? */
    virtual void F10(int d) final;
};

/* 클래스를 final 로 지정하면 부모 클래스가 될 수 없다. */
class AAA final;
class BBB : public AAA;

/*
 * override, final 은 식별자(Identifier) 이지
 * static, const 같은 키워드(Keyword) 가 아니다.
 *
 * C++98 코드와의 하위 호환성 때문에 식별자로 지정됐고
 * 오버라이딩 같은 특정 상황이 아니면 식별자로서의 의미를 갖지 않는다.
 */
void override();
void final();

int main(int argc, char* argv[])
{


    return 0;
}
