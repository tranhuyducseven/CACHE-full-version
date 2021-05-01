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
    SLinkedList();
    ~SLinkedList(){};
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    bool empty();
    void clear();
    bool removeItem(const T &item);
    T get(int index);
    void set(int index, const T &e);
    T removeAt(int index);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    T getTail()
    {
        if (this->count == 0)
        {
            return 0;
        }
        else
            return this->tail->data;
    }
    T getHead()
    {
        if (this->count == 0)
        {
            return 0;
        }
        else
            return this->head->data;
    }
    void reveredLinkedList();

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
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
};
template <class T>
T SLinkedList<T>::get(int index)
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
template <class T>
SLinkedList<T>::SLinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}
template <class T>
void SLinkedList<T>::add(const T &e)
{
    Node *temp = new Node(e, nullptr);
    if (this->count == 0)
    {
        this->head = temp;
        this->tail = temp;
        this->count++;
    }
    else if (this->count > 0)
    {
        this->tail->next = temp;
        this->tail = temp;
        this->count++;
    }
}

template <class T>
void SLinkedList<T>::add(int index, const T &e)
{
    Node *temp = new Node(e, nullptr);
    if (index < 0 || index > count)
    {
        return;
    }
    else if (index == 0)
    {
        if (this->count == 0)
        {
            this->head = temp;
            this->tail = temp;
            this->count++;
        }
        else if (this->count > 0)
        {
            temp->next = this->head;
            this->head = temp;
            this->count++;
        }
        else
            return;
    }
    else
    {
        Node *pre = this->head;
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

template <class T>
T SLinkedList<T>::removeAt(int index)
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
            T val = temp->data;
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
        T val = temp->data;
        delete temp;

        if (index == count - 1)
        {
            this->tail = pre;
        }
        this->count--;
        return val;
    }
}

template <class T>
bool SLinkedList<T>::removeItem(const T &item)
{
    Node *pre = this->head;
    bool check = false;
    while (pre->next != nullptr)
    {
        if (head->data == item)
        {
            Node *temp = this->head;
            this->head = temp->next;
            delete temp;
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
                pre->next = temp->next;
            }
            delete temp;
            this->count--;
            check = true;
        }
        pre = pre->next;
    }
    return check;
}

template <class T>
void SLinkedList<T>::clear()
{
    if (this->count > 0)
    {
        Node *pre = this->head;
        while (pre != NULL)
        {
            Node *temp = pre;
            pre = pre->next;
            delete temp;
            cout << "cleared" << endl;
        }

        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
    }
    else
    {
        return;
    }
}
template <class T>
string SLinkedList<T>::toString()
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
template <class T>
int SLinkedList<T>::size()
{
    return this->count;
}
template <class T>
void SLinkedList<T>::reveredLinkedList()
{
    Node *cur = head;
    Node *prev = NULL;
    Node *nextCur = NULL;
    tail = head;
    while (cur != NULL)
    {
        nextCur=cur->next;
        cur->next=prev;
        prev=cur;
        cur=nextCur;   
    }
    head = prev;

}
int main()
{
    SLinkedList<int> list;

    for (int i = 0; i < 0; ++i)
    {
        list.add(i);
    }

    
    cout << list.toString() << " Head:" << list.getHead() << " Tail: " << list.getTail() << " Size:" << list.size() << endl;
    list.reveredLinkedList();
    cout << list.toString() << " Head:" << list.getHead() << " Tail: " << list.getTail() << " Size:" << list.size() << endl;
}