#include<iostream>
using namespace std;
int findGCD(int a, int b)
{
    if(a%b==0) return b;
    else if(b%a==0) return a;
    else return findGCD(b,a%b);
     
    
}
int main(){
    cout<<findGCD(124,32)<<endl;
         return 0;
}