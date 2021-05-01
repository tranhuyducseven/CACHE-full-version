#include <iostream>
using namespace std;
void foo(int *x)
{
    cout << sizeof(x);
    cout<<sizeof(int);
}
int main()
{
    int x[3] = {1, 2, 3};
    foo(x);
    return 0;
}