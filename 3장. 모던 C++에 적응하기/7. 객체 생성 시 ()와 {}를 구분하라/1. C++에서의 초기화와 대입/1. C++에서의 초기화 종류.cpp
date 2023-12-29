#include <iostream>

using namespace std;

/*
 * C++에서의 초기화 종류
 */

int main(int argc, char* argv[])
{
    // 직접 초기화 (Direct Initialization)
    int a(1);
    int b();    // 0

    // 직접 리스트 초기화 (Direct-list Initialization)
    int c[]{1, 2};
    // auto 로 선언할 때는 하나의 값만 사용할 수 있다.
    // auto d{1, 2};
    auto d{1};

    // 복사 초기화 (Copy Initialization)
    int e = 2;

    // 복사 리스트 초기화 (Copy-list Initialization)
    auto f = {1, 2};
    // auto 로 선언할 때는 자료형이 모두 같아야 한다.
    // auto g = {1, 2.0};
    float g[] = {1, 2.0};
    int h = {};    // 0

    // 유니폼 초기화 (Uniform Initialization)
    int i{3};

    // 기본 초기화 (Default Initialization)
    int j;    // 쓰레기 값
    
    // 값 초기화 (Value Initialization)
    int k{};      // 0
    int l[5]{};   // 0 0 0 0 0

    return 0;
}
