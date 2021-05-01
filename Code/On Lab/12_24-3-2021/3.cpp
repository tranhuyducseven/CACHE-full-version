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
    ~SLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    string toString();
    int size();

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
        Node(T data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
};
template <class T>
SLinkedList<T>::SLinkedList()
{
    this->count = 0;
}
template <class T>
SLinkedList<T>::~SLinkedList()
{
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
int SLinkedList<T>::size()
{
    return this->count;
}


template<class T>
T SLinkedList<T>::get(int index) {
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
int main()
{
   SLinkedList<int> list;
int size = 10;

for(int index = 0; index < size; index++){
    list.add(index);
    cout<<list.size()<<endl;
}

cout << list.toString();
}