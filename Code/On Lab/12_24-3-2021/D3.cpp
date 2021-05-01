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