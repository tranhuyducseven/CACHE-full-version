#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
class DLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList();
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    void getTail()
    {
        cout << this->tail->data << endl;
    }
    void getHead()
    {
        cout << this->head->data << endl;
    }
    bool empty();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    T removeAt(int index);
    bool removeItem(const T &item);
    void clear();

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
};
template <class T>
void DLinkedList<T>::add(const T &e)
{
    Node *temp = new Node(e);
    if (this->count == 0)
    {
        this->head = temp;
        this->tail = temp;
        this->count++;
    }
    else if (this->count > 0)
    {

        temp->previous = this->tail;
        this->tail->next = temp;
        this->tail = temp;
        this->count++;
    }
}

template <class T>
void DLinkedList<T>::add(int index, const T &e)
{
    Node *temp = new Node(e);
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
            this->head->previous = temp;
            this->head = temp;
            this->count++;
        }
    }
    else if (index == count)
    {
        Node *temp = new Node(e);
        if (this->count == 0)
        {
            this->head = temp;
            this->tail = temp;
            this->count++;
        }
        else if (this->count > 0)
        {

            temp->previous = this->tail;
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
        temp->previous = pre;
        pre->next = temp;
        temp->next = tmp;
        tmp->previous = temp;
        this->count++;
    }
}

template <class T>
int DLinkedList<T>::size()
{
    return this->count;
}
template <class T>
DLinkedList<T>::DLinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
}

template <class T>
T DLinkedList<T>::get(int index)
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
void DLinkedList<T>::set(int index, const T &e)
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
            this->head->data = e;
        }
    }
    else
    {

        Node *pre = head;
        for (int i = 0; i < index - 1; i++)
        {
            pre = pre->next;
        }
        pre->next->data = e;
    }
}

template <class T>
bool DLinkedList<T>::empty()
{
    if (this->count == 0)
    {
        return true;
    }
    return false;
}

template <class T>
int DLinkedList<T>::indexOf(const T &item)
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

template <class T>
bool DLinkedList<T>::contains(const T &item)
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
template<class T>
T DLinkedList<T>::removeAt(int index)
{

    /* Remove element at index and return removed value */
    if (index < 0 || index >= this->count)
        throw out_of_range("...");
    T value;
    if (this->count == 1)
    {
        Node *del = head;
        value = del->data;
        delete del;
        head = NULL;
        tail = NULL;
    }
    else
    {
        if (index == 0)
        {
            Node *del = head;
            head = head->next;
            head->previous = NULL;
            value = del->data;
            delete del;
        }
        else if (index == count - 1)
        {
            Node *del = tail;
            tail = tail->previous;
            tail->next = NULL;
            value = del->data;
            delete del;
        }
        else
        {
            if (index < count / 2)
            {
                Node *del = head;
                for (int i = 0; i < index; i++)
                    del = del->next;
                del->previous->next = del->next;
                del->next->previous = del->previous;
                value = del->data;
                delete del;
            }
            else
            {
                Node *del = tail;
                for (int i = count - 1; i > index; i--)
                    del = del->previous;
                del->previous->next = del->next;
                del->next->previous = del->previous;
                value = del->data;
                delete del;
            }
        }
    }
    this->count--;
    return value;
}

template <class T>
bool DLinkedList<T>::removeItem(const T &item)
{
    Node *scan = head;
    for (int i = 0; i < count; i++)
    {
        if (scan->data == item)
        {
            this->removeAt(i);
            return true;
        }
        scan = scan->next;
    }
    return false;
}

template <class T>
void DLinkedList<T>::clear()
{
    if (this->count > 0)
    {
        /* Remove all elements in list */
        while (this->head != NULL)
            removeAt(0);
        tail = NULL;
    }
}

template <class T>
string DLinkedList<T>::toString()
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
int main()
{
    DLinkedList<int> list;
    int size = 6;
    int value[] = {1, 2, 3, 4, 5, 6};

    for (int idx = 0; idx < size; idx++)
    {
        list.add(value[idx]);
    }
    for (int i = 0; i < size; i++)
    {
        cout << "index: " << i << endl;
        list.removeAt(list.size() - 1);
        cout << list.toString() << endl;
    }
}