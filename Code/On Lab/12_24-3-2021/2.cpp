
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
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
    ~DLinkedList();
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
    };
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
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
    };
};
 
 
 
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) 
{
    this->pList = pList;
    if (begin) {
        if (pList) {
            current = pList->head;
            index = 0;
        }
        else {
            current = nullptr;
            index = -1;
        }
    }
    else {
        current = nullptr;
        if (pList) index = pList->size();
        else index = -1;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator)
{
    this->pList = iterator.pList;
    this->current = iterator.current;
    this->index = iterator.index;
    return *this;
}

template <class T> 
void DLinkedList<T>::Iterator::set(const T &e)
{
    if (!current) throw (std::out_of_range("Segmentation fault!"));
    current->data = e;
}

template<class T>
T& DLinkedList<T>::Iterator::operator*() 
{
    if (!current) throw (std::out_of_range("Segmentation fault!"));
    return current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove() 
{
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if (!current) throw std::out_of_range("Segmentation fault!");
    int data = this->current->data;
    if (this->current->previous) {
        this->current = this->current->previous;
        index--;
    }
    else {
        this->current = nullptr;
        index = -1;
    } 
    pList->removeItem(data);
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) 
{
    return (this->current != iterator.current && this->index != iterator.index);
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++() 
{
    if (!current && index == pList->size())
        throw (std::out_of_range("Segmentation fault!"));
    if (!current && index == -1)
        current = pList->head;
    else current = current->next;
    ++index;
    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) 
{
    if (current == nullptr && index == pList->size())
        throw (std::out_of_range("Segmentation fault!"));
    Iterator temp = *this;
    ++(*this);
    return temp;
}
template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
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
    if (begin) {
        if (pList) {
            current = pList->head;
            index = 0;
        }
        else {
            current = nullptr;
            index = -1;
        }
    }
    else {
        current = nullptr;
        if (pList) index = pList->size();
        else index = -1;
    }
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
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
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
    if (!current) throw std::out_of_range("Segmentation fault!");
    int data = this->current->data;
    if (current == pList->head) {
        current = nullptr;
        index = -1;
    }
    else {
        int t = pList->indexOf(data);
        Node* temp = pList->head;
        while (t > 1) {
            temp = temp->next;
            t--;
        }
        current = temp;
        index--;
    }
    pList->removeItem(data);
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (!current) throw (std::out_of_range("Segmentation fault!"));
    current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (!current) throw (std::out_of_range("Segmentation fault!"));
    return current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns true if two iterators points the same node and index
    */
    return (this->current != iterator.current && this->index != iterator.index);
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end*/
    if (!current && index == pList->size())
        throw (std::out_of_range("Segmentation fault!"));
    if (!current && index == -1)
        current = pList->head;
    else current = current->next;
    ++index;
    return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if (current == nullptr && index == pList->size())
        throw (std::out_of_range("Segmentation fault!"));
    Iterator temp = *this;
    ++(*this);
    return temp;
}
//End test 4