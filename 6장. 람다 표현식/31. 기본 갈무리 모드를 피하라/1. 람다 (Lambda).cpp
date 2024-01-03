/*
 * https://lunchballer.com/archives/284
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

int main(int argc, char* argv[])
{
    /*
     * 런타임에서 변수 lambda 는 임시 클로져 t 의 복사본이다.
     * 따라서, t 는 이 구문이 끝나면 소멸한다.
     */
    auto lambda = [](int num)
    {
        return ++num;
    };

    return 0;
}
