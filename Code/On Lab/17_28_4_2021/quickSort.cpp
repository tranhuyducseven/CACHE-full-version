#include <iostream>
using namespace std;

template <class T>
class Sorting
{
private:
    static T *Partition(T *start, T *end);

public:
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void insertionSort(T *start, T *end);

    static void hybridQuickSort(T *start, T *end, int min_size);
};
template <class T>
T *Sorting<T>::Partition(T *start, T *end)
{
}

template <class T>
void Sorting<T>::insertionSort(T *start, T *end)
{
}

template <class T>
void Sorting<T>::hybridQuickSort(T *start, T *end, int min_size)
{
    if()
}
int main()
{
    int array[] = {1, 2, 6, 4, 7, 8, 5, 3};
    int min_size = 4;
    Sorting<int>::hybridQuickSort(&array[0], &array[8], min_size);
    return 0;
}