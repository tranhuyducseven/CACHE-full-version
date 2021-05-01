#include <iostream>
using namespace std;

template <class T>
class Sorting
{
private:
    static T* Partition(T* start, T* end);

public:
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void insertionSort(T* start, T* end);

    static void hybridQuickSort(T* start, T* end, int min_size);
};

template <class T>
void Sorting<T>::insertionSort(T* start, T* end) {
    cout << "Insertion sort: "; printArray(start, end);
    T* e = end - 1;
    T* temp = start;
    while (temp != e) {
        T value = *(temp + 1);
        T* rollback = temp;
        temp = temp + 1;
        while (rollback >= start && value < *rollback) {
            *(rollback + 1) = *rollback;
            rollback--;
        }
        rollback++;
        *rollback = value;
    }
}

template <class T>
T* Sorting<T>::Partition(T* start, T* end)
{
    cout << "Quick sort: "; printArray(start, end);
    T pivot = *start;
    T* i = start + 1;
    T* j = end - 1;
    while (i <= j) {
        while (*i < pivot) {
            i++;
        }
        while (*j > pivot) {
            j--;
        }
        if (i < j) {
            T temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
        }
    }
    *start = *j;
    *j = pivot;
    return j;
}

template <class T>
void Sorting<T>::hybridQuickSort(T* start, T* end, int min_size) {
    int size = end - start+1;
    if (size < min_size && size >= 1) {
        insertionSort(start, end);
    }
    else if (start < end) {
        T* mid = Partition(start, end);
        hybridQuickSort(start, mid, min_size);      //phai la mid thay vi mid-1, boi vi cai end cua ham hybrid truyen vao 1 cai end "qua lo", nen minh cung xu ly "qua lo"
        hybridQuickSort(mid + 1, end, min_size);
    }

}

int main() {
    int array[] = { 2, 6, 4, 12, 23, 1, 0, -12 };
    int min_size = 4;
    Sorting<int>::hybridQuickSort(&array[0], &array[8], min_size);
    return 0;
}