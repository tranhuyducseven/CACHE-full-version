#include<iostream>
using namespace std;

int myArrayToInt(char *str, int n) 
{ 
    if(n==1) return ((int)(str[n-1])-48);
    else{
        return ((int)(str[n-1])-48)+10*myArrayToInt(str,n-1);
    }
}
int main(){

    char str[]="2020";
    // cout<<power(4,2)<<endl;
   cout<<myArrayToInt(str, 4);
    return 0;
}