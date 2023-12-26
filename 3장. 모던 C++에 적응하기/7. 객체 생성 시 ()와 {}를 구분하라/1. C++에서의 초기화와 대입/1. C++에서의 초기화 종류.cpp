#include <iostream>

using namespace std;

/*
 * C++에서의 초기화 종류
 */

int main(int argc, char* argv[])
{
    // 직접 초기화 (Direct Initialization)
    int a(1);

    // 직접 리스트 초기화 (Direct-list Initialization)
    int b[]{1, 2};
    // auto 로 선언할 때는 하나의 값만 사용할 수 있다.
    // auto c{1, 2};
    auto c{1};

    // 복사 초기화 (Copy Initialization)
    int d = 2;

    // 복사 리스트 초기화 (Copy-list Initialization)
    auto e = {1, 2};
    // auto 로 선언할 때는 자료형이 모두 같아야 한다.
    // auto f = {1, 2.0};
    float f[] = {1, 2.0};

    // 유니폼 초기화 (Uniform Initialization)
    int g{3};

    // 기본 초기화 (Default Initialization)
    // 쓰레기 값
    int h;
    
    // 값 초기화 (Value Initialization)
    // 0
    int i{};
    // 0 0 0 0 0
    int j[5]{};

    return 0;
}
