/*
 * https://velog.io/@15ywt/c-%EC%8A%A4%EB%A7%88%ED%8A%B8-%ED%8F%AC%EC%9D%B8%ED%84%B0
 */
#include <iostream>

using namespace std;

/*
 * 스마트 포인터의 크기
 */

void custom_deleter(int* p)
{
    cout << "자원이 해제되었습니다." << endl;
    delete p;
}

int main(int argc, char* argv[])
{
    int *p = new int(5);
    unique_ptr<int> uq1(new int(5));

    if (sizeof(p) == sizeof(uq1))
        cout << "[" << sizeof(uq1) << "] Raw Pointer 와 unique_ptr 의 크기는 같다." << endl;

    unique_ptr<int, void(*)(int*)> uq2(new int(5), custom_deleter);

    if (sizeof(uq1) != sizeof(uq2))
        cout << "[" << sizeof(uq2) << "] unique_ptr 의 크기는 커스텀 삭제자를 사용하면 함수 포인터 크기만큼 추가된다." << endl;

    auto lambda_deleter = [](int* p)
    {
        cout << "자원이 해제되었습니다." << endl;
        delete p;
    };

    // 람다 lambda_deleter 는 상태(멤버 변수) 가 없는 클로져(익명 함수 객체) 로 생성되므로
    unique_ptr<int, decltype(lambda_deleter)> uq3(new int(5), lambda_deleter);

    if (sizeof(uq1) == sizeof(uq3))
        cout << "[" << sizeof(uq3) << "] 람다를 커스텀 삭제자로 지정하면 크기가 늘어나지 않는다." << endl;

    // Raw Pointer 와 제어 블록의 주소를 저장해야 하므로
    shared_ptr<int> sh1(new int(5));

    if (sizeof(p) != sizeof(sh1))
        cout << "[" << sizeof(sh1) << "] Raw Pointer 와 shared_ptr 의 크기는 다르다." << endl;

    // 제어 블록에 커스텀 삭제자를 위한 포인터가 이미 있으므로
    shared_ptr<int> sh2(new int(5), custom_deleter);

    if (sizeof(sh1) == sizeof(sh2))
        cout << "[" << sizeof(sh2) << "] shared_ptr 의 크기는 커스텀 삭제자와는 관계 없다." << endl;

    // shared_ptr 과 마찬가지로 Raw Pointer 와 제어 블록의 주소를 저장하므로
    weak_ptr<int> wk1(sh1);

    if (sizeof(wk1) == sizeof(sh1))
        cout << "[" << sizeof(sh2) << "] weak_ptr 의 크기는 shared_ptr 과 같다." << endl;

    return 0;
}
