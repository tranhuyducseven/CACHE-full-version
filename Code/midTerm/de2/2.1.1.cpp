#include <iostream>
using namespace std;
int foo(int n)
{
    if (n <= 0)
        return 0;
    else if (n % 2 == 0)
        return foo(n - 1) + foo(n - 2) + n;
    else
        return 2 * foo(n - 1) + 1;
}
int main()
{
    cout << foo(8) << endl;
    return 0;
}