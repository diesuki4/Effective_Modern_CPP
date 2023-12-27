#include <iostream>
#include <mutex>

using namespace std;

/*
 * nullptr의 장점
 *
 * 1. 코드의 가독성을 높여준다.
 * 2. 어떤 포인터 타입으로든 변환될 수 있다.
 * 3. 템플릿과 함께 사용될 때 특히 빛난다.
 */

class Widget { };

// 이 함수들은 뮤텍스를 락하고 호출해야 한다고 가정
int    f1(shared_ptr<Widget> spw) { return 1; }
double f2(unique_ptr<Widget> upw) { return 1.0; }
bool   f3(Widget* pw)             { return true; }

/*
 * 코드 중복을 줄이고자 다음과 같이
 * 함수 템플릿을 이용해 동일한 패턴을 템플릿화시켰다.
 */
template <typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mtx, PtrType ptr)
{
    lock_guard<MuxType> lg(mtx);

    return func(ptr);
}

int main(int argc, char* argv[])
{
    /*
     * 1. 코드의 가독성을 높여준다.
     */

    // 결과값의 주소를 반환하는 함수라고 가정
    auto findRecord = [](int data) { return reinterpret_cast<int*>(0x1A2B3C4D); };
    auto result = findRecord(5);

    if (result == 0)
        cout << "findRecord() 의 반환형을 파악할 수 없다." << endl;
    else if (result == nullptr)
        cout << "findRecord() 의 반환형이 포인터임을 파악할 수 있다." << endl;

    mutex mtx;

    /*
     * 뮤텍스를 잠그고 함수를 호출하는 부분이
     * 중복되고 있다.
     */
    {
        lock_guard<mutex> lg(mtx);
        auto result = f1(0);
    }
    {
        lock_guard<mutex> lg(mtx);
        auto result = f2(NULL);
    }
    {
        lock_guard<mutex> lg(mtx);
        auto result = f3(nullptr);
    }

    /*
     * auto result1 = lockAndCall(f1, mtx, 0);
     * 
     * 컴파일 오류가 발생한다.
     * 
     * 템플릿에서 PtrType 이 int 로 추론되면서,
     * f1() 의 매개변수인 shared_ptr 과 호환되지 않기 때문이다.
     */

    /*
     * auto result2 = lockAndCall(f2, mtx, NULL);
     *
     * f1() 과 같은 이유로 컴파일 오류가 발생한다.
     */

    // 정상적으로 컴파일 된다.
    auto result3 = lockAndCall(f3, mtx, nullptr);
    /*
     * 3. 템플릿과 함께 사용될 때 특히 빛난다.
     *
     * nullptr 은 템플릿에서 정수가 아닌, nullptr_t 타입으로 추론된다.
     *
     * 2. 어떤 포인터 타입으로든 변환될 수 있다.
     *
     * nullptr_t 는 f3() 의 Widget* 를 포함해
     * 어떤 포인터 타입으로도 암시적 변환이 가능하기 때문이다.
     */

    return 0;
}
