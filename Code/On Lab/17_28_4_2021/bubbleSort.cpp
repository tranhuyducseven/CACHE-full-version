#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    SLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    ~SLinkedList(){};
    void add(T e)
    {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }
    int size()
    {
        return this->count;
    }
    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node()
        {
            next = 0;
        }
        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort();
};
template <class T>
void SLinkedList<T>::bubbleSort()
{
    Node *cur = NULL;
    for (int i = 0; i < this->size() - 1; i++)
    {
        cur = this->head;
        for (int j = 0; j < this->size() - i - 1; j++)
        {
            if (cur->data > cur->next->data)
            {
                T dataTemp = cur->data;
                cur->data = cur->next->data;
                cur->next->data = dataTemp;
            }
             cur=cur->next;
        }       
        this->printList();
    }
}
int main()
{

    int arr[] = {9, 2, 8, 4, 1};
    SLinkedList<int> list;
    for (int i = 0; i < int(sizeof(arr)) / 4; i++)
        list.add(arr[i]);
    list.bubbleSort();
    return 0;
}