#include <iostream>
using namespace std;
int x = 0;
int foo(int n)
{
    if (n <= 0)
        return 0;
    else
    {
        cin >> x;
        return foo(n - 1) + x;
    }
}
int main()
{
    cout<<foo(5);
    return 0;
}