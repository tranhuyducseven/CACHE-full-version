#ifndef SORTINGAPPLICATION_H
#define SORTINGAPPLICATION_H
#include <iostream>
#include <string>
using namespace std;
#endif
/* Your helping functions go here */
string bubbleSort(string s)
{
    for (int i = 0; i < (int)s.length() - 1; i++)
    {
        for (int j = 0; j < (int)s.length() - 1 - i; j++)
        {
            if ((int)s[j] > (int)s[j + 1])
            {
                char temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }

    return s;
}
bool isPermutation(string a, string b)
{
    //TODO
    if ((int)a.length() < (int)b.length())
        return false;
    a = bubbleSort(a);
    b = bubbleSort(b);
    for (int i = 0; i < (int)a.length(); i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}


int main()
{
    string a = "abbac";
    string b = "baba";
    cout << isPermutation(a, b);
}