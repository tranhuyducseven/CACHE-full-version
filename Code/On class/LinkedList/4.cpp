#include <iostream>
#include <sstream>
using namespace std;
class IntDLinkedList
{
public:
    class Node; // Forward declaration

private:
    Node *head;
    Node *tail;
    int count;

public:
    IntDLinkedList() : head(NULL), tail(NULL), count(0){};
    virtual void add(int element)
    {
        Node *temp = new Node(element);
        if (this->count == 0)
        {
            this->head = temp;
            this->tail = temp;
            this->count++;
        }
        else if (this->count > 0)
        {

            temp->prev = this->tail;
            this->tail->next = temp;
            this->tail = temp;
            this->count++;
        }
    }

    virtual void add(int index, int element)
    {
        Node *temp = new Node(element);
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
        else if (index == count)
        {
            Node *temp = new Node(element);
            if (this->count == 0)
            {
                this->head = temp;
                this->tail = temp;
                this->count++;
            }
            else if (this->count > 0)
            {

                temp->prev = this->tail;
                this->tail->next = temp;
                this->tail = temp;
                this->count++;
            }
        }
        else{
            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            Node *tmp = pre->next;
            temp->prev = pre;
            pre->next = temp;
            temp->next = tmp;
            tmp->prev = temp;
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

        return this->count;
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
        Node *prev;

    public:
        Node() : data(0), next(NULL), prev(NULL){};
        Node(int data) : data(data), next(NULL), prev(NULL){};
    };
};
int main()
{

    // Test: Adding items (prepend)
    IntDLinkedList list;
    int size = 10;
    for (int index = 0; index < size; index++)
    {
        list.add(list.size(), index);
    }

    cout << list.toString();
}