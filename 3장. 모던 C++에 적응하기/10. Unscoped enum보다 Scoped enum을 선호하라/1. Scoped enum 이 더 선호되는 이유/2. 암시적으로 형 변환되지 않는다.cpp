#include <iostream>

using namespace std;

/*
 * 암시적으로 형 변환되지 않는다
 */

enum EUnscoped
{
    Red, Black, Blue
};

enum class EScoped
{
    Green, Yellow, White
};

void processInt(int num)
{
    return;
}

int main(int argc, char* argv[])
{
    EUnscoped color1 = Red;

    // Unscoped enum 은 정수형으로 암시적 변환된다.
    if (color1 < 14.5)
        processInt(color1);

    EScoped color2 = EScoped::Green;

    /*
     * Scoped enum 은 암시적으로 변환되지 않는다.
     *
     * if (color2 < 14.5)
     *     processInt(color2);
     */
    if (static_cast<double>(color2) < 14.5)
        processInt(static_cast<int>(color2));

    return 0;
}
