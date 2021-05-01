#include <iostream>
#include <math.h>
using namespace std;

void ascendingSort(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void descendingSort(int a[], int n)
{
   for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] < a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void mySort(int a[], int n, void (*sort)(int[], int))
{
     sort(a,n);
}
int main()
{
    int n = 5;
    int a[5] = {1, 2, 3, 4, 5};
    void (*sortAlgorithm)(int[], int) = descendingSort;
    mySort(a, n, sortAlgorithm);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }

    return 0;
}
