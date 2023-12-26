#include <iostream>
#include <vector>

using namespace std;

/*
 * 인터페이스 설계자가 유니폼 초기화에서 고려해야 할 것
 */

class OldWidget
{
public:
    OldWidget()        { }
    OldWidget(int i)   { cout << "int 로 처리" << endl; }
    OldWidget(char c)  { cout << "char 로 처리" << endl; }
    OldWidget(bool b)  { cout << "bool 로 처리" << endl; }
    OldWidget(float f) { cout << "float 로 처리" << endl; }
};

class NewWidget : private OldWidget
{
public:
    NewWidget(int i)   : OldWidget(i) { }
    NewWidget(char c)  : OldWidget(c) { }
    NewWidget(bool b)  : OldWidget(b) { }
    NewWidget(float f) : OldWidget(f) { }

    // 추가
    NewWidget(initializer_list<double> li) { cout << "다 가로채버렸다." << endl; }
};

void print(vector<int> v)
{
    for (int e : v)
        cout << e << " ";
    cout << endl;
}

/*
 * 템플릿 작성자 입장에서는 사용자가
 *
 * vector<int> (5, 2) 를 의도했는지
 * vector<int> {5, 2} 를 의도했는지 알 수 없다.
 *
 * 따라서, 파라미터를 받아 내부에서 객체를 생성하는
 * 이런 템플릿을 만들 때는
 * 
 * 사용자에게 어떤 초기화 방식을 사용하는지
 * 문서화해 알려야 한다.
 */
template <typename T, typename... Ts>
void Func(Ts&&... params)
{
    T obj1(forward<Ts>(params)...);
    T obj2{forward<Ts>(params)...};

    print(obj1);
    print(obj2);
}

int main(int argc, char* argv[])
{
    /*
     * vector 에는 initializer_list 생성자가 존재하고
     *
     * 유니폼 초기화의 문제점에 가장 큰 영향을 받는 클래스 중 하나다.
     */
    vector<int> v1(5, 2); // 2 2 2 2 2
    vector<int> v2{5, 2}; // 5 2

    /*
     * 스콧은 이렇게 ()를 쓰는지, {}를 쓰는지에 따라 결과가 달라지는 것을
     * vector 인터페이스 설계의 오류로 간주하고 있다.
     *
     * ()를 쓰든 {}를 쓰든 결과는 같게 설계해야 한다.
     */

    /*
     * 클래스를 설계할 때 initializer_list 생성자가 존재한다면,
     * 형 변환이 가능한 모든 타입은 이 생성자가 가로챌 수 있음을 염두해야 한다.
     *
     * 대표적으로 잘 쓰고 있던 기존 클래스에 initializer_list 생성자를 추가하는 경우다.
     */
    OldWidget ow1{1};     // int 로 처리
    OldWidget ow2{'1'};   // char 로 처리
    OldWidget ow3{true};  // bool 로 처리
    OldWidget ow4{1.F};   // float 로 처리
    cout << endl;

    /*
     * 따라서, initializer_list 생성자는 꼭 필요할 때만 추가하자.
     */
    NewWidget nw1{1};     // 다 가로채버렸다.
    NewWidget nw2{'1'};   // 다 가로채버렸다.
    NewWidget nw3{true};  // 다 가로채버렸다.
    NewWidget nw4{1.F};   // 다 가로채버렸다.

    /*
     * 결과로
     * 
     * {2, 2, 2, 2, 2} 가 나오길 바라는지
     * {5, 2} 가 나오길 바라는지는 사용자만 알고 있다.
     */
    Func<vector<int>>(5, 2);

    return 0;
}
