#include <iostream>
using namespace std;
// int countWaySumOfSquare(int x)
// to find number of ways to express x as sum of squares of unique natural numbers.

// For example:

// Input  : x = 100
// Output : 3
// Explain: 100 = 10^2 = 8^2 + 6^2 = 1^2 + 3^2 + 4^2 + 5^2 + 7^2
int power(int number, int n)
{
    if (n == 0)
        return 1;
    else
        return number * power(number, n - 1);
}
int countWaySumOfSquare(int x, int number)
{
    int value = x - power(number, 2);
    if (value == 0)
        return 1;
    if (value < 0)
        return 0;
    return countWaySumOfSquare(x, number + 1) + countWaySumOfSquare(value, number + 1);
}
int countWaySumOfSquare(int x)
{
    return countWaySumOfSquare(x, 1);
}
int main()
{
    cout << countWaySumOfSquare(100);

    return 0;
}