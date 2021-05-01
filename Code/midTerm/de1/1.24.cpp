#include <iostream>
using namespace std;
int foo(int n)
{
    if (n <= 3)
        return 1;
    else
        return foo(n - 1) + foo(n - 2) + foo(n - 3);
}
int main()
{
    cout << "Result is " << foo(10);
    return 0;
}