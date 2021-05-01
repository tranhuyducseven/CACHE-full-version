#include <iostream>
using namespace std;
void func(int *a, int *&b)
{
    int *t;
    t = a;
    a = b;
    b = t;
}
int main()
{
    int *p1 = new int;
    *p1 = 3;
    int *p2 = new int;
    *p2 = 5;
    func(p1, p2);
    cout << "*p1 is: " << *p1 << endl
         << "*p2 is " << *p2 << endl;
    return 0;
}