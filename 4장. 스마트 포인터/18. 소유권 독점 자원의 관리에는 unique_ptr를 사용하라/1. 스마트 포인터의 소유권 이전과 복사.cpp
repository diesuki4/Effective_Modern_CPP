#include <iostream>
#include <memory>

using namespace std;

/*
 * 스마트 포인터의 소유권 이전과 복사
 */

unique_ptr<int> getUnique()
{
    return unique_ptr<int>(new int(5));
}

void custom_deleter(int* p)
{
    cout << "자원이 해제되었습니다." << endl;
    delete p;
}

int main(int argc, char* argv[])
{
    // 복사 생성이 아니라, 이동 생성을 통한 소유권 이전이다.
    unique_ptr<int> a1(unique_ptr<int>(new int(5)));
    unique_ptr<int> a2(getUnique());
    unique_ptr<int> a3 = move(a2);

    // 이건 복사이므로, 불가
    // unique_ptr<int> a4(a1);

    unique_ptr<int, void(*)(int*)> a5(new int(5), custom_deleter);
    // 아예 다른 템플릿 클래스이므로, 서로 소유권 이전이 불가
    // a5 = move(a2);

    // shared_ptr 은 커스텀 삭제자를 써도, 같은 클래스 템플릿이므로
    // 서로 복사/이동이 가능
    shared_ptr<int> b1(new int(5), custom_deleter);
    shared_ptr<int> b2(b1);
    weak_ptr<int> wkptr(b2);

    return 0;
}
