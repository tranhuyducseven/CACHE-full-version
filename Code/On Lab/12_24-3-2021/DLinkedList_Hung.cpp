#include <bits/stdc++.h>
using namespace std;

template <class T>
class DLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList() : head(NULL), tail(NULL), count(0){};
    ~DLinkedList(){};
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &item);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

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

        void Print()
        {
            cout << data << endl;
        }
    };
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(){};
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();

        // Prefix ++ overload
        Iterator &operator++();

        // Postfix ++ overload
        Iterator operator++(int);

        void PrintNode()
        {
            cout << "---------- Index -----------" << endl;
            cout << index << endl;
            cout << "---------- Value of index ---------" << endl;
            if (current == NULL)
                cout << "NULL!" << endl;
            else
                current->Print();
            cout << "---------- Size of List ------------" << endl;
            cout << pList->size() << endl;
            cout << "------------------------------------------" << endl;
        }
    };
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
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true: 
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false: 
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
    this->pList = pList;
    if (begin == true)
    {
        if (pList != NULL)
        {
            this->current = pList->head;
            this->index = 0;
        }
        else
        {
            this->current = NULL;
            this->index = -1;
        }
    }
    else
    {
        this->current = NULL;
        if (pList != NULL)
            this->index = pList->count;
        else
            this->index = 0;
    }
}

template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    this->pList = iterator.pList;
    this->current = iterator.current;
    this->index = iterator.index;
    return *this;
}

template <class T>
void DLinkedList<T>::Iterator::remove()
{
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if (this->current == NULL)
        throw std::out_of_range("Segmentation fault!");
    else if (this->current == this->pList->head)
    {
        this->current = NULL;
        this->index = -1;
        pList->removeAt(0);
    }
    else if (this->current == this->pList->tail)
    {
        this->current = this->pList->tail->previous;
        pList->removeAt(pList->size() - 1);
        this->index--;
    }
    else
    {
        Node *temp = this->pList->head;
        while (temp != this->current)
            temp = temp->next;
        this->current = temp->previous;
        pList->removeAt(index);
        this->index--;
    }
}

template <class T>
void DLinkedList<T>::Iterator::set(const T &e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (this->current == NULL)
        throw std::out_of_range("Segmentation fault!");
    else
        this->current->data = e;
}

template <class T>
T &DLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (this->current == NULL)
        throw std::out_of_range("Segmentation fault!");
    else
        return (this->current->data);
}

template <class T>
bool DLinkedList<T>::Iterator::operator!=(const Iterator &iterator)
{
    /*
        Operator not equals
        * Returns false if two iterators points the same node and index
    */
    if (this->current == iterator.current && this->index == iterator.index)
        return false;
    else
        return true;
}
// Prefix ++ overload
template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if (this->current == NULL && (this->index == pList->size() || this->index == 0))
        throw std::out_of_range("Segmentation fault!");
    else if (this->current == NULL && this->index == -1)
    {
        this->current = pList->head;
        this->index++;
    }
    else
    {
        this->current = this->current->next;
        this->index++;
    }
    return *this;
}
// Postfix ++ overload
template <class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    Iterator temp = *this;
    ++*this;
    return temp;
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

class DataLog
{
private:
    list<int> logList;
    list<int>::iterator currentState;

public:
    DataLog();
    DataLog(const int &data);
    void addCurrentState(int number);
    void subtractCurrentState(int number);
    void save();
    void undo();
    void redo();

    int getCurrentStateData()
    {
        return *currentState;
    }

    void printLog()
    {
        for (auto i = logList.begin(); i != logList.end(); i++)
        {
            if (i == currentState)
                cout << "Current state: ";
            cout << "[ " << *i << " ] => ";
        }
        cout << "END_LOG";
    }
};

DataLog::DataLog()
{
    /*
     * TODO:  add the first state with 0
     */
    this->logList.push_back(0);
    this->currentState = prev(this->logList.end());
}

DataLog::DataLog(const int &data)
{
    /*
     * TODO:  add the first state with data
     */
    this->logList.push_back(data);
    this->currentState = prev(this->logList.end());
}

void DataLog::addCurrentState(int number)
{
    /*
     * TODO: Increase the value of current state by number
     */
    *(this->currentState) = *(this->currentState) + number;
}

void DataLog::subtractCurrentState(int number)
{
    /*
     * TODO: Decrease the value of current state by number
     */
    *(this->currentState) = *(this->currentState) - number;
}

void DataLog::save()
{
    /*
     * TODO: This function will create a new state, copy the data of the currentState
     *       and move the currentState Iterator to this new state. If there are other states behind the 
     *       currentState Iterator, we delete them all before creating a new state.
     */
    logList.erase(next(this->currentState, 1), this->logList.end());
    this->logList.push_back(this->logList.back());
    this->currentState = prev(this->logList.end());
}

void DataLog::undo()
{
    /*
     * TODO: Switch to the previous state of the data
     *       If this is the oldest state in the log, nothing changes
     */
    if (this->currentState == this->logList.begin())
        return;
    else
        this->currentState--;
}

void DataLog::redo()
{
    /*
     * TODO: Switch to the latter state of the data
     *       If this is the latest state in the log, nothing changes
     */
    this->currentState++;
    if (this->currentState == logList.end())
        this->currentState--;
}

int main()
{
    DLinkedList<int> list;
    int size = 10;
    for (int idx = 0; idx < size; idx++)
    {
        list.add(idx);
    }
    DLinkedList<int>::Iterator it = list.begin();
    for (; it != list.end(); it++)
    {
        cout << *it << " |";
    }
    return 0;
}
