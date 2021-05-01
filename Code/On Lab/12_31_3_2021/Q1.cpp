#ifndef QUEUE_H
#define QUEUE_H
#include "DLinkedList.h"
template <class T>
class Queue
{
protected:
    DLinkedList<T> list;

public:
    Queue() {}
    void push(T item);
    T pop();
    T top();
    bool empty();
    int size();
    void clear();
};

#endif /* QUEUE_H */

template <class T>
class DLinkedList
{
public:
    class Node; //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList();
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
};
template <class T>
void DLinkedList<T>::add(const T &e)
{
    /* Insert an element into the end of the list. */
    Node *temp = new Node(e);
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->previous = tail;
        tail->next = temp;
        tail = temp;
    }
    this->count++;
}

template <class T>
void DLinkedList<T>::add(int index, const T &e)
{
    /* Insert an element into the list at given index. */
    if (index < 0 || index > this->count)
        throw out_of_range("...");
    Node *temp = new Node(e);
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else if (index == 0)
    {
        temp->next = head;
        head->previous = temp;
        head = temp;
    }
    else if (index == this->count)
    {
        temp->previous = tail;
        tail->next = temp;
        tail = temp;
    }
    else
    {
        Node *node = head;
        for (int i = 0; i < index - 1; i++)
            node = node->next;
        Node *nextNode = node->next;
        node->next = temp;
        temp->previous = node;
        temp->next = nextNode;
        nextNode->previous = temp;
    }
    this->count++;
}

template <class T>
int DLinkedList<T>::size()
{
    /* Return the length (size) of list */
    return this->count;
}

template <class T>
T DLinkedList<T>::get(int index)
{
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this->count || this->count == 0)
        throw out_of_range("...");
    Node *temp = head;
    if (index == 0)
        return temp->data;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T &e)
{
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this->count || this->count == 0)
        throw out_of_range("...");
    Node *temp = head;
    if (index == 0)
        temp->data = e;
    else
    {
        for (int i = 0; i < index; i++)
            temp = temp->next;
        temp->data = e;
    }
}

template <class T>
bool DLinkedList<T>::empty()
{
    /* Check if the list is empty or not. */
    return (this->count == 0);
}

template <class T>
int DLinkedList<T>::indexOf(const T &item)
{
    /* Return the first index wheter item appears in list, otherwise return -1 */
    if (head->data == item)
        return 0;
    else
    {
        Node *temp = head;
        for (int i = 1; i < this->count; i++)
        {
            temp = temp->next;
            if (temp->data == item)
                return i;
        }
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::contains(const T &item)
{
    /* Check if item appears in the list */
    if (head->data == item)
        return true;
    else
    {
        Node *temp = head;
        for (int i = 0; i < this->count - 1; i++)
        {
            temp = temp->next;
            if (temp->data == item)
                return true;
        }
    }
    return false;
}

template <class T>
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
    /* Remove the first apperance of item in list and return true, otherwise return false */
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
    /* Remove all elements in list */
    while (this->head != NULL)
        removeAt(0);
    tail = NULL;
}
template <class T>
void Queue<T>::push(T item)
{
    // TODO: Push new element into the end of the queue
    this->list.add(item);
}
template <class T>
T Queue<T>::pop()
{
    // TODO: Remove an element in the head of the queue
    return this->list.removeAt(0);
}
template <class T>
T Queue<T>::top()
{
    // TODO: Get value of the element in the head of the queue
    return this->list.get(0);
}
template <class T>
bool Queue<T>::empty()
{
    // TODO: Determine if the queue is empty
    return this->list.empty();
}
template <class T>
int Queue<T>::size()
{
    // TODO: Get the size of the queue
    return this->list.size();
}
template <class T>
void Queue<T>::clear()
{
    // TODO: Clear all elements of the queue
    this->list.clear();
}
int main()
{

    
    return 0;
}