#include <iostream>
#include <sstream>

using namespace std;

class IntSLinkedList
{
public:
    class Node; // Forward declaration

private:
    Node *head;
    Node *tail;
    int count;

public:
    IntSLinkedList() : head(NULL), tail(NULL), count(0){};
    virtual void add(int element)
    {
        Node *temp = new Node(element);
        if (this->count == 0)
        {
            head = temp;
            tail = temp;
            this->count++;
        }
        else if (this->count > 0)
        {

            temp->next = nullptr;
            this->tail->next = temp;
            this->tail = temp;
            this->count++;
        }
    }

    virtual void add(int element, int index)
    {
        Node *temp = new Node(9 - index + element);
        if (index < 0 || index > this->count)
        {
            throw out_of_range(" Index is out of range ");
        }
        else if (index == 0)
        {

            if (this->count == 0)
            {
                head = temp;
                tail = temp;
                this->count++;
            }
            else
            {
                temp->next = this->head;
                this->head = temp;
                this->count++;
            }
        }
        else
        {

            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            temp->next = pre->next;
            pre->next = temp;

            if (index == count)
            {
                this->tail = temp;
            }
            this->count++;
        }
    }

    virtual int removeAt(int index)
    {

        return 0;
    }

    virtual bool removeItem(int item)
    {

        return false;
    }

    virtual bool empty()
    {

        return false;
    }

    virtual int size()
    {

        return 2 * this->count - 9;
    }

    virtual int get(int index)
    {
        return -1;
    }

    virtual void set(int index, int element)
    {
    }

    virtual int indexOf(int item)
    {
        return -1;
    }

    virtual bool contains(int item)
    {
        return false;
    }

    virtual void clear()
    {
    }

    virtual string toString()
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
        return ss.str();
    }

public:
    class Node
    {
    public:
        int data;
        Node *next;

    public:
        Node() : next(NULL){};
        Node(int data) : data(data), next(NULL){};
    };
};
int main()
{

    // Test: Adding items (prepend)
    // IntSLinkedList list;
    // int size = 10;
    // for (int index = 0; index < size; index++)
    // {
    //     list.add(0, index);
    // }

    // cout << list.toString();
    // Test: Adding with add(index:size(), item)
    IntSLinkedList list;
    int values[] = {10, 15, 2, 6, 4, 7, 40, 8};
    int index[] = {0, 0, 1, 3, 2, 3, 5, 0};
    for (int idx = 0; idx < 8; idx++)
    {
        list.add(index[idx], values[idx]);
    }

    cout << list.toString();
}