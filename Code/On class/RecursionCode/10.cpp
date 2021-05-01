#include <iostream>
using namespace std;
int strLen(char *str)
{
   if(*str=='\0') return 0;
   else
   return 1+strLen(++str);
    
}
int main()
{
    char str[] = "Truong DH Bach Khoa";
    cout << strLen(str);
    return 0;
}