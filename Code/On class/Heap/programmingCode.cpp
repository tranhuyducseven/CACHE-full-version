#include <iostream>
using namespace std;
class Heap
{
private:
    int *data;
    int size;
    int capacity;

public:
    Heap()
    {
        this->data = NULL;
        this->size = 0;
        this->capacity = 0;
    }
    ~Heap()
    {
        this->clear();
    }

    void copyFromArray(int *arr, int n)
    {
        this->size = n;
        this->data = new int[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->data[i] = arr[i];
        }
    }
    void reHeapUp(int index)
    {
        if (index == 0)
            return;
        int parent = (index - 1) / 2;
        if (data[parent] < data[index])
        {
            swap(data[parent], data[index]);
            reHeapUp(parent);
        }
    }
    void reHeapDown(int index)
    {
        int leftChild = index * 2 + 1;
        int rightChild = leftChild + 1;
        int child = 0;
        if (leftChild <= size - 1)
        {
            if (rightChild <= size - 1 && data[rightChild] > data[leftChild])
                child = rightChild;
            else
                child = leftChild;
            if (data[index] < data[child])
                swap(data[index], data[child]);
            reHeapDown(child);
        }
    }
    void print()
    {
        for (int i = 0; i < this->size; i++)
        {
            cout << this->data[i] << " ";
        }
    }
    void clear()
    {
        if (this->data != NULL)
        {
            delete this->data;
            this->size = 0;
            this->capacity = 0;
        }
    }
    void insert(int key)
    {
        if (this->size >= this->capacity)
            return;
        else
        {
            data[this->size] = key;
            reHeapUp(size);
            size += 1;
        }
    }
    void build(int *arr, int n)
    {
        copyFromArray(arr, n);
        int index = n / 2 - 1;
        while (index >= 0)
        {
            reHeapDown(index);
            index -= 1;
        }
    }
    int remove()
    {

        if (this->size == 0)
            throw "Empty heap";
        else
        {
            int maxData = data[0];
            data[0] = data[size - 1];
            size = size - 1;
            reHeapDown(0);
            return maxData;
        }
    }
};
int main()
{
    Heap *h = new Heap();
    int arr[8] = {78, 67, 32, 56, 8, 23, 19, 45};
    h->copyFromArray(arr, 8);
    int largest = h->remove();
    h->print();
    cout << endl
         << largest;
    delete h;
    return 0;
}