#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end);
public:
    static void QuickSort(T* start, T* end);
};

template<class T>
T* Sorting<T>::Partition(T* start, T* end) {
    // TODO: return the pointer which points to the pivot after rearrange the array.
    
    T pivot = *start;
    T* i = start;
    T* j = end;
    do {
        do {
            i++;
        } while (*i < pivot);
        do {
            j--;
        } while (*j > pivot);
        T temp = *i;
        *i = *j;
        *j = temp;
    } while (i < j);
    T temp = *i;
    *i = *j;
    *j = temp;
    *start = *j;
    *j = pivot;
    return j;
}

template<class T>
void Sorting<T>::QuickSort(T* start, T* end) {
    // TODO
    // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
    if (start < end) {
        static bool firstTime = true;
        T* mid = Partition(start, end);
        if (firstTime) {
            cout << (int)(mid - start);
            firstTime = false;
        }
        else cout << " " << (int)(mid - start);  
            QuickSort(start, mid);          //mid day hoi "qua lo", nhung do la dieu can thiet, khi dau vao da "qua lo" san roi
            QuickSort(mid + 1, end);
    }
}


int main() {
    int array[] = { 3, 5, 7, 10 ,12, 14, 55, 23, 4, 99, 9, 6, 4, 8, -5, -3, 17 };
    cout << "Index of pivots: ";
    Sorting<int>::QuickSort(&array[0], &array[17]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array) cout << i << " ";
    return 0;
}

#endif /* SORTING_H */