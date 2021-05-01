#include <iostream>
using namespace std;
void foo(int w)
{
    if (w > 0)
    {
        foo(w - 1);
        cout << w << " ";
        foo(w - 1);
    }
}
int main()
{
    foo(3);
    cout << "xxxxx";
    return 0;
}