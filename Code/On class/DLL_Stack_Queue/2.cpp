#include <iostream>
using namespace std;
#include <sstream>

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
                this->head->prev = temp;
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
        else
        {
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
            this->count++;
        }
    }

    virtual int removeAt(int index)
    {
        int data = 0;
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
                Node *temp = this->head->next;
                data = this->head->data;
                delete this->head;
                this->head = temp;
                this->count--;
            }
        }
        else if (index == count - 1)
        {
            if (this->count == 0)
            {
                throw out_of_range(" Index is out of range ");
            }
            else if (this->count > 0)
            {

                Node *temp = this->tail->prev;
                data = this->tail->data;
                delete this->tail;
                this->tail = temp;
                this->count--;
            }
        }
        else if (index > 0 && index < this->count - 1)
        {
            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            Node *temp = pre->next->next;
            Node *delNode = pre->next;
            pre->next = temp;
            temp->prev = pre;
            data = delNode->data;
            delete delNode;
            this->count--;
        }
        return data;
    }

    virtual bool removeItem(int item)
    {
        Node *pre = this->head;
        bool check = false;
        while (pre->next != nullptr)
        {
            if (head->data == item)
            {
                Node *temp = this->head->next;
                delete this->head;
                this->head = temp;
                this->count--;
                check = true;
            }

            if (pre->next->data == item)
            {
                Node *temp = pre->next;
                if (temp == this->tail)
                {
                    this->tail = pre;
                }
                else
                {
                    Node *tmp = temp->next;
                    pre->next = tmp;
                    tmp->prev = pre;
                }
                delete temp;
                this->count--;
                check = true;
            }
            pre = pre->next;
        }
        return check;
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
        else
        {
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
        Node *prev;

    public:
        Node() : data(0), next(NULL), prev(NULL){};
        Node(int data) : data(data), next(NULL), prev(NULL){};
    };
};
int main()
{

    IntDLinkedList list;
    int values[] = {10, 15, 2, 6, 4, 7, 40, 8};
    int index[] = {0, 0, 1, 3, 2, 3, 5, 0};
    for (int idx = 0; idx < 8; idx++)
    {
        list.add(index[idx], values[idx]);
    }
    cout << list.toString() << endl;
    list.clear();
    cout << list.toString();
}