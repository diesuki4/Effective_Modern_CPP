#include <iostream>
#include <tuple>
#include <type_traits>

using namespace std;

/*
 * Unscoped enum이 유용한 경우
 * 
 * tuple 내의 필드를 지칭할 때
 */

/*
 * 아래 Scoped enum 의 형 변환을 좀 더 편하게 사용하기 위해
 * 함수 템플릿으로 만들면 다음과 같다.
 * 
 * 컴파일 타임(Compile time) 에 결과가 정해져야 하기 때문에
 * constexpr 함수여야 한다.
 * 
 * 모든 enum 타입에 대해 동작해야 하기 때문에
 * 함수 템플릿이어야 한다.
 */
template <typename E>
constexpr auto toUtype(E enumerator) noexcept
{
    // underlying_type_t() 함수는 enum 의 기반 타입을 반환한다.
    return static_cast<underlying_type_t<E>>(enumerator);
}

int main(int argc, char* argv[])
{
    // 사용자 번호, 이름, 이메일
    using UserInfo = tuple<int, string, string>;
    UserInfo ui = {10, "Kim", "aaa@bbb.com"};

    int no = get<0>(ui);
    string name = get<1>(ui);
    string email = get<2>(ui);

    /*
     * Unscoped enum 을 사용하면, 정수로의 암시적 변환 덕분에
     * 
     * 인덱스에 해당하는 필드를 기억하지 않아도 된다.
     */
    enum EUnscoped { No, Name, Email };

    no = get<No>(ui);
    name = get<Name>(ui);
    email = get<Email>(ui);

    /*
     * 여기서 만약 Scoped enum 을 사용하면, 훨씬 장황해진다.
     */
    enum class EScoped { No, Name, Email };

    no = get<static_cast<unsigned>(EScoped::No)>(ui);
    name = get<static_cast<unsigned>(EScoped::Name)>(ui);
    email = get<static_cast<unsigned>(EScoped::Email)>(ui);

    /*
     * Unscoped enum 에 비해 좀 더 복잡하긴 하지만
     * 
     * 이름 공간 오염과 암시적 형 변환을 방지한다는 장점이 있다.
     */
    no = get<toUtype(EScoped::No)>(ui);
    name = get<toUtype(EScoped::Name)>(ui);
    email = get<toUtype(EScoped::Email)>(ui);

    return 0;
}
