#include <iostream>
using namespace std;
// C++
class ListNode
{
public:
    int data;           // node value
    ListNode *next;     // pointer to the next node
    ListNode(int data); // constructor
};

class LinkedList
{
public:
    ListNode *head, *tail;  // pointers to the head and to the tail of the list
    LinkedList();           // constructor
    bool Empty();           // check if list is empty
    void addFirst(int val); // add val to the head of the list
    void addLast(int val);  // add val to the tail of the list
    bool removeFirst();     // delete first element of the list, return true is removed successfully
    bool removeLast();      // delete last element of the list, return true is removed successfully
    int size();             // return the size of the list
    void Print();           // print values of the list in one line
};
LinkedList::LinkedList()
{
    this->tail = NULL;
    this->head = NULL;
}
ListNode::ListNode(int data)
{
    this->data = data;
    this->next=NULL;
}
bool LinkedList::Empty()
{
    return this->tail == NULL && this->head == NULL;
}
void LinkedList::addFirst(int val)
{
    ListNode *temp = new ListNode(val);      
          temp->next = head;
        head = temp;
    
}
void LinkedList::addLast(int val)
{
    ListNode *temp = new ListNode(val);
    this->tail->next = temp;
    this->tail = temp;
}
bool LinkedList::removeFirst()
{
    if (this->head != NULL)
    {
        ListNode *temp = this->head->next;
        delete this->head;
        this->head = temp;
        return true;
    }

    else
        return false;
}
bool LinkedList::removeLast()
{
    if (this->tail != NULL)
    {
        ListNode *temp = head;
        while (temp->next != this->tail)
        {
            temp = temp->next;
        }
        delete this->tail;
        this->tail = temp;
        return true;
    }
    else
        return false;
}
int LinkedList::size()
{
    int size = 0;
    if (this->head == NULL)
    {
        return 0;
    }
    else
    {
        ListNode *temp = this->head;
        while (temp != NULL)
        {
            temp = temp->next;
            size++;
        }
    }
    return size;
}
void LinkedList::Print()
{
    ListNode *temp = this->head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

int main()
{
    LinkedList *node = NULL;
    node->addFirst(5);
    node->addFirst(6);
    // node->addLast(7);
    // node->addLast(88);
    node->Print();
}