#include<iostream>
using namespace std;

void printArray(int n)
{
   if(n==0) cout<<n;
   else{    
       printArray(n-1);
       cout<<", "<<n;
   }
}
int main(){

    printArray(5);
    return 0;

}