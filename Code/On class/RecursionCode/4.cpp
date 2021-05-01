#include<iostream>
using namespace std;
int decimalToBinary(int decimal_number)                                             //20/2=10 du 0
{                                                                                                               //10/2=5 du 0          
    if(decimal_number==0) return 0;                      //5/2=2 du 1
    else{                                                                                                     //2/2=1 du 0  
        return decimalToBinary(decimal_number/2)*10 + decimal_number%2;
    }
} 
int main(){
    cout<<decimalToBinary(20);
}


