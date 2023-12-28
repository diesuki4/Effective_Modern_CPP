#include <iostream>
#include <unordered_map>

using namespace std;

/*
 * typedef와 using 비교
 *
 * using 을 별칭 선언(Alias declaration) 이라고 한다.
 */

// C++98
typedef unique_ptr<unordered_map<string, string>> UPtrMapSS98;
// 모던 C++
using UPtrMapSS11 = unique_ptr<unordered_map<string, string>>;

// C++98
typedef double (*FuncPtr98)(int, string&);
// 모던 C++ (더 직관적이다.)
using FuncPtr11 = double (*)(int, string&);

int main(int argc, char* argv[])
{


    return 0;
}
