#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
};
int main()
{
    int n = 5;
    int *p = new int[n];
    cout << sizeof(p);

    return 0;
}