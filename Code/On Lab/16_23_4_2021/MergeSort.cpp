#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T* start, T* end)
    {
        long size = end - start + 1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T* left, T* middle, T* right) {
        /*TODO*/
        
        long leftsize{ middle - left + 1 }, rightsize{ right - middle };
        T* arrLeft = new T[leftsize];
        T* arrRight = new T[rightsize];

        T* scan = left;
        long i = 0;
        while (scan <= middle) {
            arrLeft[i] = *scan;
            i++; scan++;
        }
        long j = 0;
        while (scan <= right) {
            arrRight[j] = *scan;
            j++; scan++;
        }
        i = 0; j = 0; scan = left;
        while (i < leftsize && j < rightsize) {
            if (arrLeft[i] < arrRight[j]) {
                *scan = arrLeft[i];
                i++;
            }
            else {
                *scan = arrRight[j];
                j++;
            }
            scan++;
        }
        for (long z = i; z < leftsize; z++) {
            *scan = arrLeft[z];
            scan++;
        }
        for (long z = j; z < rightsize; z++) {
            *scan = arrRight[z];
            scan++;
        }
        delete[] arrLeft;
        delete[] arrRight;          //phai delete rieng ra!
     
        Sorting::printArray(left, right);

    }
    static void mergeSort(T* start, T* end) {
        /*TODO*/
        if (start == end) return;
        long mid = (end - start) / 2;
        T* midPointer = start + mid;
        mergeSort(start, midPointer);
        mergeSort(midPointer + 1, end);
        merge(start, midPointer, end);
    }
};


int main() {
    int arr[] = { 0,2,4,3,1,4 };
    Sorting<int>::mergeSort(&arr[0], &arr[5]);
    return 0;
}

#endif /* SORTING_H */