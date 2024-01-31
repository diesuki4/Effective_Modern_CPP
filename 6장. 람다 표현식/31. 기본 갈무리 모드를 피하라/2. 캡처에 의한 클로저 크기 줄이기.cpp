/*
 * https://stackoverflow.com/questions/23149555/when-a-c-lambda-expression-has-a-lot-of-captures-by-reference-the-size-of-the#answer-23150097
 */
#include <iostream>
#include <tuple>

using namespace std;

/*
 * 캡처에 의한 클로저 크기 줄이기
 */

int main(int argc, char* argv[])
{
    int i;
    short s;
    double d;

    // 캡처 변수를 각각 캡처하지 말고
    auto lambda1 = [&]() { cout << i << s << d; };
    cout << sizeof(lambda1) << endl;

    /* 튜플에 담아 전달하면, 상태(멤버 변수) 의 크기는
     * 참조 크기만큼만 차지하게 된다. */
    tuple<int, short, double> tp(i, s, d);

    auto lambda2 = [&]() { cout << get<0>(tp) << get<1>(tp) << get<2>(tp); };
    cout << sizeof(lambda2) << endl;

    return 0;
}
