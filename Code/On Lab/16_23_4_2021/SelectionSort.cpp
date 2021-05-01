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

    static void selectionSort(T* start, T* end);
};

template <class T>
void Sorting<T>::selectionSort(T* start, T* end)
{
    T* current = start;
    int size = end - start;
    if (size == 1) {
        printArray(start, end);
    }
    for (int i = 0; i < size - 1; i++) {        //boi vi neu chi con 1 phan tu cuoi, no da duoc tu dong sap xep roi, nen chi can chay size - 1 lan la du?
        T* min = (end - 1);     //tai ho cho "du" end.
        for (int j = 1; j < size - i; j++) {
            if (*(end - 1 - j) <= *min) {           //tim phan tu nho nhat cuoi cung tu phai qua <=> tim phan tu nho nhat dau tien tu trai qua
                min = (end - 1 - j);
            }
        }
        //sau khi tim duoc phan tu nho nhat, SWAP 2 cai voi nhau!thang dau buoi
        T value = *current;
        *current = *min;
        *min = value;
        printArray(start, end);
        current++;
    }
}

int main() {

    int arr[] = { 9, 2, 8, 1, 0, -2 };
    Sorting<int>::selectionSort(&arr[0], &arr[6]);
    return 0;
}