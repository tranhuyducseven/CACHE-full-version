#include <bits/stdc++.h>
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
        if (index < 0 || index >= this->count)
        {
            throw out_of_range(" Index is out of range ");
        }
        else if (index == 0)
        {
            if (this->count == 0)
            {
                throw out_of_range(" Index is out of range ");
            }
            else
            {
                Node *temp = this->head;
                this->head = temp->next;
                int val = temp->data;
                delete temp;
                this->count--;
                return val;
            }
        }
        else
        {

            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            Node *temp = pre->next;
            pre->next = temp->next;
            int val = temp->data;
            delete temp;

            if (index == count - 1)
            {
                this->tail = pre;
            }
            this->count--;
            return val;
        }
    }

    virtual bool removeItem(int item)
    {

        Node *pre = this->head;
        while (pre->next != nullptr)
        {
            if (head->data == item)
            {
                Node *temp = this->head;
                this->head = temp->next;
                delete temp;
                this->count--;
            }

            if (pre->next->data == item)
            {
                Node *temp = pre->next;
                pre->next = temp->next;
                delete temp;
                this->count--;
            }
            pre = pre->next;
        }
        return true;
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
        if (index < 0 || index >= this->count)
        {
            throw out_of_range(" Index is out of range ");
        }
        else if (index == 0)
        {
            if (this->count == 0)
            {
                throw out_of_range(" Index is out of range ");
            }
            else
            {
                return head->data;
            }
        }
        else
        {

            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            return pre->next->data;
        }
    }

    virtual void set(int index, int element)
    {
        if (index < 0 || index >= this->count)
        {
            throw out_of_range(" Index is out of range ");
        }
        else if (index == 0)
        {
            if (this->count == 0)
            {
                throw out_of_range(" Index is out of range ");
            }
            else
            {
                this->head->data = element;
            }
        }
        else
        {

            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            pre->next->data = element;
        }
    }

    virtual int indexOf(int item)
    {
        Node *pre = this->head;
        for (int i = 0; pre->next != NULL; i++)
        {
            if (head->data == item)
            {
                return 0;
            }
            if (pre->next->data == item)
            {
                return i + 1;
            }
            pre = pre->next;
        }
        return -1;
    }

    virtual bool contains(int item)
    {
        Node *pre = this->head;
        for (int i = 0; pre->next != NULL; i++)
        {
            if (head->data == item)
            {
                return true;
            }
            if (pre->next->data == item)
            {
                return true;
            }
            pre = pre->next;
        }

        return false;
    }

    virtual void clear()
    {
        if (this->count > 0)
        {
            Node *pre = this->head;
            while (pre->next != NULL)
            {
                Node *temp = pre;
                pre = pre->next;
                delete temp;
            }
            delete pre;
            this->head = NULL;
            this->tail = NULL;
            this->count = 0;
        }
        else{
            return;
        }
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

    IntSLinkedList list;
    list.clear();
    cout << list.toString();
    return 0;
}