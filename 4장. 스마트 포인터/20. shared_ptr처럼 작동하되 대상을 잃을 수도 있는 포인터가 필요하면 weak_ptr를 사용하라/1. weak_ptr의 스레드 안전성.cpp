/*
 * https://stackoverflow.com/questions/37679636/what-is-diffrence-between-lock-and-expired-weak-ptr-c#answer-39838212
 */
#include <iostream>
#include <memory>

using namespace std;

/*
 * weak_ptr의 스레드 안전성
 * 
 * lock() 함수는 단순히 shared_ptr 로의 변환이 아니라,
 * Strong Reference Count 증가를 통해
 * 
 * 멀티스레드 환경에서
 * 자원이 해제되지 않도록 잠그는 역할을 한다.
 */

int main(int argc, char* argv[])
{
    shared_ptr<int> sh(new int(5));
    weak_ptr<int> wk(sh);

    /* Not Thread-safe */
    if (!wk.expired())      // 여기서 유효성을 확인해도
    {
        // 여기서 다른 스레드로 컨텍스트가 넘어갔다면
        // 거기서 자원이 해제될 수 있다.
        shared_ptr<int> shlck = wk.lock();      // 그럼 다시 돌아왔을 때는 nullptr 이 담기게 된다.
        cout << *shlck << endl;
    }

    /* Thread-safe */
    if (shared_ptr<int> shlck = wk.lock())      // lock() 함수를 통해 Strong Reference Count 가 증가했다.
    {
        // 따라서, 여기서 다른 스레드로 넘어갔다고 해도
        // 그 스레드에서는 자원을 해제할 수 없다.
        cout << *shlck << endl;
    }

    return 0;
}
