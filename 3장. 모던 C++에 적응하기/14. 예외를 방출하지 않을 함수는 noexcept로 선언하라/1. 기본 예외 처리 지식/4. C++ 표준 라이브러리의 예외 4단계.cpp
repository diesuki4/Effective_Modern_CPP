/*
 * https://en.cppreference.com/w/cpp/language/exceptions
 * https://en.wikipedia.org/wiki/Exception_safety
 * https://m.blog.naver.com/mug896/140168091611
 */
#include <iostream>

using namespace std;

/*
 * C++ 표준 라이브러리의 예외 4단계
 */

/* <불변성>
 * 어떤 객체의 유효한 상태를 규정하는 조건
 *
 * 최대 힙에서의 불변성은 <언제나 가장 큰 값을 뽑을 수 있다> 로 정의할 수 있다.
 * 가장 큰 원소가 top 에 있지 않다면, 불변성이 깨진 것.
 * 
 * 불변성이 깨진 개체는 더 이상 유효하게 사용할 수 없다. */

int main(int argc, char* argv[])
{
    /* 1. 예외 없음 보장 (No-throw guarantee)
     * 
     * 예외적인 상황에서도 내부적인 처리 등을 통해 성공적으로 동작하며,
     * 사용자에게 예외가 전파되지 않는다.
     *
     * set::insert() 함수처럼, 예외 없이 반환 값을 통해 성공 여부를 알리는 경우도 해당
     * 
     * Non-throwing swap (예외를 방출하지 않는 swap() 구현) */

    /* 2. 강한 예외 안전성 (Strong exception safety)
     *
     * 예외가 발생하면 롤백을 통해 기존 상태로 되돌린다.
     * 
     * 롤백이라고 하지만, 실제로는 복사를 통해 진행하다가
     * 예외가 발생하면 취소하는 경우가 많다.
     *
     * 복사 생성을 통한 vector 메모리 재할당
     * 
     * Copy & Swap 관용구 */

    /* 3. 기본 예외 안전성 (Basic exception safety)
     *
     * 예외로 인해 개체의 값이 변할 수는 있지만, 불변성 깨짐이나 자원 누수는 발생하지 않는다.
     *
     * 예외 발생 가능성이 있는 이동 생성자를 통한 vector 메모리 재할당
     * 이동이 도중에 끊길 수 있지만, 그 vector 를 더 이상 못 쓰는 건 아니다.*/

    /* 4. 예외 안전성 없음 (No exception safety)
     *
     * 예외로 인해 개체의 불변성이 깨지거나 자원 누수로 이어질 수 있다.
     *
     * (그럴 일은 없지만) 컨테이너에 삽입 직후 예외가 발생해,
     * 원소 count 가 증가하지 않는 경우 불변성이 깨져 더 이상 사용할 수 없다. */

    return 0;
}
