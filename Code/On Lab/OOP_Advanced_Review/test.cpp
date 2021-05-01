#include <iostream>
#include <string>
#include <string.h>
using namespace std;
int countElement(const char*c){
    int count=1;
    for(int i=0;c[i]!='\0';i++){
        count++;
    }
    return count;
}
bool checkAuthor(const char *A, const char *B)
{
    bool check = false;
    int a = strlen(A);
    int b = strlen(B);
    for (int i = 0; i < a; i++)
    {
        if (A[i] == B[0])
        {
            int start = i;
            bool check = true;
            for (int j = 0; j < 5; j++)
            {
                if (B[j] != B[start])
                {
                    check = false;
                    break;
                }
                start++;
            }
            if (check)
            {
                return check;
            }
        }
    }
    return check;
}
int main()
{
    const char *a = "Nguyen Dinh Huy, Nguyen Thi Xuan Anh";
    const char *b = "Nguyen Dinh Huy";
    cout <<countElement(b)<<endl;

    return 0;
}