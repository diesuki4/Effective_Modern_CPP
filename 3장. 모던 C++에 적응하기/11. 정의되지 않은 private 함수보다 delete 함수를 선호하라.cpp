#include <iostream>

using namespace std;

/*
 * 정의되지 않은 private 함수보다 delete 함수를 선호하라
 * 
 * 1. 클래스 내부, friend 클래스에서 호출 시 컴파일 타임에 오류를 감지할 수 있다.
 * 2. 클래스가 아닌 비멤버 함수에서도 사용할 수 있다.
 * 3. 특정 템플릿 함수의 인스턴스화(생성) 를 막을 수 있다.
 */

class CPP98
{
private:
    int data;
    /*
     * private 으로 인한 접근 불가
     * 
     * 클래스 내부, friend 클래스에서 호출시
     * 링크 에러를 발생시키기 위해 몸체를 정의하지 않는다.
     */
    CPP98(const CPP98&);
    CPP98& operator= (const CPP98&);

public:
    CPP98(int data = 0) : data(data) { }

    void doSomething()
    {
        CPP98 a;

        // 링크 에러 !!
        // CPP98 b(a);

        // 링크 에러 !!
        // a = b;
    }
};

class CPP11
{
private:
    int data;

public:
    CPP11(int data = 0) : data(data) { }
    /* 
     * C++은 함수의 접근성을 확인 후, 삭제 여부를 확인하기 때문에
     * 
     * ghcnf 불가 이유를 삭제가 아닌, 접근성의 문제로 치부하는 컴파일러들이 있다.
     * 
     * 따라서, 삭제된 함수는 public 에 선언하는 것이 관례다.
     */
    CPP11(const CPP11&) = delete;
    CPP11& operator= (const CPP11&) = delete;

    void doSomething()
    {
        CPP11 c;

        // 컴파일 에러 !!
        // CPP11 d(c);

        // 컴파일 에러 !!
        // d = c;
    }
};

// int 형만 처리하는 함수
void processInt(int num) { }
/*
 * delete 함수 선언들은 컴파일되지는 않지만,
 * 오버로딩 후보로는 간주된다.
 */
void processInt(bool) = delete;
void processInt(char) = delete;
/*
 * double 버전의 delete 함수 선언이 오버로딩 후보에 올랐으므로
 * float 은 int, bool, char 보다는 double 버전의 함수를 선택하게 된다.
 */
void processInt(double) = delete;

/*
 * 포인터에는 특별한 처리가 필요한 포인터가 2개 있는데
 * 바로 void* 와 char* 다.
 * 
 * void* 는 역참조와 증감이 불가하다는 점에서,
 * char* 는 문자열을 나타낸다는 점에서 특별하다.
 */

/*
 * 함수 템플릿을 만들되, void* 와 char* 는
 * 특수화를 통해 쓰지 못 하게 하고 싶은 경우
 */

class CPP98w
{
public:
    /*
     * C++98 방식에서는 이 문제를 해결할 수 없었다.
     */
    template <typename T>
    static void processPointer(T* ptr) { }

private:
    /*
     * 템플릿 특수화는 클래스 범위에는 작성이 불가능하기 때문.
     * (GCC 에서는 안 됐고, MSVC 에서는 됐다.)
     */
    template <>
    static void processPointer<void>(void*);
    template <>
    static void processPointer<char>(char*);
};

class CPP11w
{
public:
    template <typename T>
    static void processPointer(T* ptr) { }
};
/*
 * delete 선언은 클래스 내부 private 영역에 작성할 필요가 없으므로
 * 바깥에서 특정 템플릿 함수를 삭제할 수 있다.
 */
template <>
void CPP11w::processPointer<void>(void*) = delete;
template <>
void CPP11w::processPointer<char>(char*) = delete;

/*
 * 단순히 함수 템플릿만 필요하다면, 당연히 클래스를 쓰지 않고도 가능하다.
 */
template <typename T>
void processPointer(T* ptr) { }

template <>
void processPointer<void>(void*) = delete;
template <>
void processPointer<char>(char*) = delete;

int main(int argc, char* argv[])
{
    CPP98 a;

    // 컴파일 에러 !!
    // CPP98 b(a);

    CPP98 b;

    // 컴파일 에러 !!
    // b = a;

    b.DoSomething();

    CPP11 c;

    // 컴파일 에러 !!
    // CPP11 d(c);

    CPP11 d;

    // 컴파일 에러 !!
    // d = c;

    d.doSomething();

    processInt(10);
    // processInt(true);     // processInt(bool)
    // processInt('A');      // processInt(char)
    // processInt(3.0F);     // processInt(double)
    // processInt(3.0);      // processInt(double)

    int*  pi = nullptr;
    void* pv = nullptr;
    char* pc = nullptr;

    CPP98w::processPointer(pi);
    // CPP98w::processPointer(pv);
    // CPP98w::processPointer(pc);

    CPP11w::processPointer(pi);
    // CPP11w::processPointer(pv);
    // CPP11w::processPointer(pc);

    processPointer(pi);
    // processPointer(pv);
    // processPointer(pc);

    return 0;
}
