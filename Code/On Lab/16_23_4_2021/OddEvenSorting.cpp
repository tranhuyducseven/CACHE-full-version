#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void oddEvenSort(T* start, T* end);
};

template <class T>
void Sorting<T>::oddEvenSort(T* start, T* end)
{
    /*TODO*/
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        T* evenStart = start;
        while (evenStart < end - 1) {
            if (*evenStart > *(evenStart + 1)) {
                T temp = *evenStart;
                *evenStart = *(evenStart + 1);
                *(evenStart + 1) = temp;
                isSorted = false;
            }
            evenStart += 2;
        }
        T* oddStart = start + 1;
        while (oddStart < end - 1) {
            if (*oddStart > *(oddStart + 1)) {
                T temp = *oddStart;
                *oddStart = *(oddStart + 1);
                *(oddStart + 1) = temp;
                isSorted = false;
            }
            oddStart += 2;
        }
        printArray(start, end);
    }
}

int main() {
    int arr[] = { 3, 2, 3, 8, 5, 6, 4, 1 };
    Sorting<int>::oddEvenSort(&arr[0], &arr[8]);
    return 0;
}