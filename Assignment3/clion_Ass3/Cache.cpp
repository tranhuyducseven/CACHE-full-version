#include "Cache.h"

FIFO::FIFO ()
{
    this->arr = new Elem *[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
        this->arr[i] = nullptr;
}

void FIFO::access (int)
{}

void FIFO::insert (Elem *e)
{
    this->arr[this->count++] = e;
}

int FIFO::remove ()
{
    int addr = this->arr[0]->addr;
    delete this->arr[0];
    for (int i = 0; i < MAXSIZE - 1; i++)
        this->arr[i] = this->arr[i + 1];
    return addr;
}

void FIFO::print ()
{
    for (int i = 0; i < this->count; i++)
        this->arr[i]->print();
}

FIFO::~FIFO ()
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (this->arr[i] != nullptr)
            delete arr[i];
    }
    delete[] arr;
    this->count = 0;

}

// HashTable For MRU-LRU
int OpenAddressingHash::hashFunction (int key, int i) const
{
    int h1 = key % this->size;
    int h2 = 1 + (key % (this->size - 1));
    return (h1 + i * h2) % this->size;
}

int OpenAddressingHash::insertKey (Node *node)
{
    int j;
    int i = 0;
    while (i < this->size)
    {
        j = this->hashFunction(node->elem->addr, i);
        if (this->status[j] != NON_EMPTY)
        {
            if (this->status[j] == DELETED)
            {
                delete this->data[j]->elem;
                delete this->data[j];
            }
            this->data[j] = node;
            this->status[j] = NON_EMPTY;
            return j;
        }
        else
            i += 1;
    }
    return -1;
}

int OpenAddressingHash::searchKey (int key)
{
    int i = 0;
    int j;
    do
    {
        j = this->hashFunction(key, i);
        if (this->data[j]->elem->addr == key && this->status[j] == NON_EMPTY)
            return j;
        i += 1;
    } while (this->status[j] != NIL && i < this->size);
    return -1;
}

void OpenAddressingHash::removeKey (int key)
{
    int k = this->searchKey(key);
    if (k != -1)
    {
        this->status[k] = DELETED;
    }
    else
        return;
}

Node *OpenAddressingHash::getNodeContainKey (int key)
{
    int k = this->searchKey(key);
    if (k != -1)
        return this->data[k];
    else
        return nullptr;
}

// MRU
MRU::MRU ()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->hash = new OpenAddressingHash(MAXSIZE);
}

void MRU::putOnTop (Node *node)
{
    node->next = this->head;
    node->prev = nullptr;
    if (this->head != nullptr)
        this->head->prev = node;
    this->head = node;
    if (this->tail == nullptr)
        this->tail = node;
}

void MRU::removeNode (Node *node)
{
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
    {
        this->head = node->next;
    }
    if (node->next != nullptr)
    {
        node->next->prev = node->prev;
    }
    else
    {
        this->tail = node->prev;
    }
    this->count--;
}

void MRU::insert (Elem *e)
{

    if (this->count == MAXSIZE)
        this->remove();
    Node *temp = new Node(e);
    this->hash->insertKey(temp);
    this->putOnTop(temp);
    this->count++;
}

void MRU::access (int key)
{
    Node *tmp = this->hash->getNodeContainKey(key);
    if (tmp != nullptr)
    {
        this->removeNode(tmp);
        this->putOnTop(tmp);
    }
}

int MRU::remove ()
{
    this->hash->removeKey(this->head->elem->addr);
    int addr = this->head->elem->addr;
    this->removeNode(this->head);
    return addr;
}

void MRU::print ()
{
    Node *tmp = this->head;
    while (tmp != nullptr)
    {
        tmp->elem->print();
        tmp = tmp->next;
    }
}

MRU::~MRU ()
{
    delete this->hash;
    this->count = 0;
}

int LRU::remove ()
{
    this->hash->removeKey(this->tail->elem->addr);
    int addr = this->tail->elem->addr;
    this->removeNode(this->tail);
    return addr;
}

//LFU
//MinHeap

void MinHeap::reHeapUp (int index)
{
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    if (data[parent]->freq > data[index]->freq)
    {
        swap(data[parent], data[index]);
        reHeapUp(parent);
    }
}

void MinHeap::reHeapDown (int index)
{
    int leftChild = index * 2 + 1;
    int rightChild = leftChild + 1;
    int child = leftChild;
    if (leftChild <= this->size - 1)
    {
        if (rightChild <= this->size - 1 && data[rightChild]->freq < data[leftChild]->freq)
            child = rightChild;
        if (data[index]->freq >= data[child]->freq)
            swap(data[index], data[child]);
        reHeapDown(child);
    }
}

void MinHeap::insertHeap (ElementHeap *ele)
{
    if (this->size == MAXSIZE)
        return;
    else
    {
        data[this->size] = ele;
        reHeapUp(this->size);
        this->size += 1;
    }
}

void MinHeap::access (int addr)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->data[i]->elem->addr == addr)
        {
            this->data[i]->freq += 1;
            this->reHeapDown(i);
            break;
        }
    }
}

void MinHeap::print ()
{
    for (int i = 0; i < this->size; i++)
    {
        this->data[i]->elem->print();
    }
}


int MinHeap::remove ()
{
    if (this->size > 0)
    {
        int addr = this->data[0]->elem->addr;
        data[0] = data[this->size - 1];
        this->size = this->size - 1;
        reHeapDown(0);
        return addr;
    }
    return -1;
}

LFU::LFU ()
{
    this->heap = new MinHeap(this->count);
}

void LFU::insert (Elem *e)
{
    auto *tmp = new ElementHeap(e);
    this->heap->insertHeap(tmp);
}

void LFU::access (int addr)
{
    this->heap->access(addr);
}

int LFU::remove ()
{
    return this->heap->remove();
}

void LFU::print ()
{
    this->heap->print();
}

LFU::~LFU ()
{
    this->heap = new MinHeap(this->count);
}

DBHashing::DBHashing (int (*h1) (int), int (*h2) (int), int s)
{
    this->h1 = h1;
    this->h2 = h2;
    this->size = s;
    this->arr = new Elem *[this->size];
    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = nullptr;
    }
    this->status = new STATUS_TYPE[this->size];
    for (int i = 0; i < this->size; i++)
    {
        this->status[i] = NIL;
    }
}

int DBHashing::searchHashing (int addr)
{
    int index1 = this->h1(addr);
    int index2 = this->h2(addr);
    int i = 0;
    int index;
    do
    {
        index = (index1 + i * index2) % this->size;
        if (this->arr[index]->addr == addr && this->status[index] == NON_EMPTY)
            return index;
        i += 1;
    } while (this->status[index] != NIL && i < this->size);
    return -1;
}

void DBHashing::insert (Elem *elem)
{
    int index1 = this->h1(elem->addr);
    int index2 = this->h2(elem->addr);
    int i = 0;
    int index;
    while (i < this->size)
    {
        index = (index1 + i * index2) % this->size;
        if (this->status[index] != NON_EMPTY)
        {
            this->arr[index] = elem;
            this->status[index] = NON_EMPTY;
        }
        else
            i += 1;
    }

}

void DBHashing::deleteNode (int addr)
{
    int k = this->searchHashing(addr);
    if (k != -1)
        this->status[k] = DELETED;
}

void DBHashing::print ()
{
    cout << "Prime memory:\n" << endl;
    for (int i = 0; i < this->size; i++)
        if (this->status[i] == NON_EMPTY)
            this->arr[i]->print();

}

Elem *DBHashing::search (int addr)
{
    int index = this->searchHashing(addr);
    if (index != -1)
        return this->arr[index];
    return nullptr;
}

DBHashing::~DBHashing ()
{
    for (int i = 0; i < this->size; i++)
    {
        delete this->arr[i];
    }
    delete[] this->arr;
    delete this->status;
}

AVL::AVL ()
{
    this->root = nullptr;
}

Tree *AVL::rotateRight (Tree *&node)
{
    Tree *leftTree = node->left;
    node->left = leftTree->right;
    leftTree->right = node;
    return leftTree;
}


Tree *AVL::rotateLeft (Tree *&node)
{
    Tree *rightTree = node->right;
    node->right = rightTree->left;
    rightTree->left = node;
    return rightTree;
}

Tree *AVL::leftBalance (Tree *&node, bool &taller)
{
    if (node->left->balance == -1)
    {
        node->left->balance = 0;
        node->balance = 0;
        node = rotateRight(node);
        taller = false;
    }
    else
    {
        if (node->left->right->balance == 0)
        {
            node->balance = 0;
            node->left->balance = 0;
            node->left->right->balance = 0;
        }
        else if (node->left->right->balance == -1)
        {
            node->balance = 1;
            node->left->balance = 0;
            node->left->right->balance = 0;
        }
        else
        {
            node->balance = 0;
            node->left->balance = -1;
            node->left->right->balance = 0;
        }
        node->left = rotateLeft(node->left);
        node = rotateRight(node);
        taller = false;
    }
    return node;
}

Tree *AVL::rightBalance (Tree *&node, bool &taller)
{
    if (node->right->balance == 1)
    {
        node->right->balance = 0;
        node->balance = 0;
        node = rotateLeft(node);
        taller = false;
    }
    else
    {
        if (node->right->left->balance == 0)
        {
            node->balance = 0;
            node->right->balance = 0;
            node->right->left->balance = 0;
        }
        else if (node->right->left->balance == 1)
        {
            node->balance = -1;
            node->right->balance = 0;
            node->right->left->balance = 0;
        }
        else
        {
            node->balance = 0;
            node->right->balance = 1;
            node->right->left->balance = 0;
        }
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
        taller = false;
    }
    return node;
}

void AVL::insert (Elem *value)
{
    bool isTaller = false;
    this->root = insertRec(this->root, value, isTaller);
}

Tree *AVL::insertRec (Tree *&node, Elem *&newElem, bool &taller)
{
    if (node == nullptr)
    {
        taller = true;
        node = new Tree(newElem);
        return node;
    }
    if (newElem->addr < node->ele->addr)
    {
        node->left = insertRec(node->left, newElem, taller);
        if (taller)
        {
            if (node->balance == -1)
            {
                node = leftBalance(node, taller);
            }
            else if (node->balance == 0)
            {
                node->balance = -1;
            }
            else
            {
                node->balance = 0;
                taller = false;
            }
        }
    }
    else if (newElem->addr > node->ele->addr)
    {
        node->right = insertRec(node->right, newElem, taller);
        if (taller)
        {
            if (node->balance == -1)
            {
                node->balance = 0;
                taller = false;
            }
            else if (node->balance == 0)
            {
                node->balance = 1;
            }
            else
            {
                node = rightBalance(node, taller);
            }
        }
    }
    return node;
}

Tree *AVL::removeRightBalance (Tree *&r, bool &isShorter)
{
    if (r->balance == -1)
    {
        r->balance = 0;
    }
    else if (r->balance == 0)
    {
        r->balance = 1;
        isShorter = false;
    }
    else
    {
        if (r->right->balance == 1)
        {
            r->balance = 0;
            r->right->balance = 0;
            r = rotateLeft(r);
        }
        else if (r->right->balance == 0)
        {
            r->balance = 1;
            r->right->balance = -1;
            isShorter = false;
            r = rotateLeft(r);
        }
        else
        {
            Tree *rRight = r->right;
            if (rRight->left->balance == 1)
            {
                r->balance = -1;
                rRight->balance = 0;
                rRight->left->balance = 0;
            }
            else if (rRight->left->balance == -1)
            {
                r->balance = 0;
                rRight->balance = 1;
                rRight->left->balance = 0;
            }
            else
            {
                r->balance = 0;
                rRight->balance = 0;
                rRight->left->balance = 0;
            }
            r->right = rotateRight(r->right);
            r = rotateLeft(r);
        }
    }
    return r;
}

Tree *AVL::removeLeftBalance (Tree *&r, bool &isShorter)
{
    if (r->balance == 1)
    {
        r->balance = 0;
    }
    else if (r->balance == 0)
    {
        r->balance = -1;
        isShorter = false;
    }
    else
    {
        if (r->left->balance == -1)
        {
            r->balance = 0;
            r->left->balance = 0;
            r = rotateRight(r);
        }
        else if (r->left->balance == 0)
        {
            r->balance = -1;
            r->left->balance = 1;
            isShorter = false;
            r = rotateRight(r);
        }
        else
        {
            Tree *rLeft = r->left;
            if (rLeft->right->balance == -1)
            {
                r->balance = 1;
                rLeft->balance = 0;
                rLeft->right->balance = 0;
            }
            else if (rLeft->right->balance == 1)
            {
                r->balance = 0;
                rLeft->balance = -1;
                rLeft->right->balance = 0;
            }
            else
            {
                r->balance = 0;
                rLeft->balance = 0;
                rLeft->right->balance = 0;
            }
            r->left = rotateLeft(r->left);
            r = rotateRight(r);
        }
    }
    return r;
}

void AVL::deleteNode (int addr)
{
    bool isShorter = false;
    this->root = removeRec(root, addr, isShorter);
}

Tree *AVL::removeRec (Tree *&r, const int &val, bool &isShorter)
{
    if (r == nullptr)
    {
        isShorter = false;
        return r;
    }
    else
    {
        if (val < r->ele->addr)
        {
            r->left = removeRec(r->left, val, isShorter);
            if (isShorter)
            {
                r = removeRightBalance(r, isShorter);
            }
            return r;
        }
        else if (val > r->ele->addr)
        {
            r->right = removeRec(r->right, val, isShorter);
            if (isShorter)
            {
                r = removeLeftBalance(r, isShorter);
            }
            return r;
        }
        else
        {
            if (r->left == nullptr)
            {
                Tree *newRoot = r->right;
                isShorter = true;
                delete r;
                return newRoot;
            }
            else if (r->right == nullptr)
            {
                Tree *newRoot = r->left;
                isShorter = true;
                delete r;
                return newRoot;
            }
            else
            {
                Tree *rightMinLeaf = r->right;
                while (rightMinLeaf->left != nullptr)
                {
                    rightMinLeaf = rightMinLeaf->left;
                }
                r->ele = rightMinLeaf->ele;
                r->right = removeRec(r->right, rightMinLeaf->ele->addr, isShorter);
                if (isShorter)
                {
                    r = removeLeftBalance(r, isShorter);
                }
            }
            return r;
        }
    }
}

Elem *AVL::search (int addr)// -1 if not found
{
    Tree *tmp = this->recursiveSearch(this->root, addr);
    if (tmp != nullptr && tmp->ele != nullptr)
        return tmp->ele;
    return nullptr;
}

Tree *AVL::recursiveSearch (Tree *node, int val)
{
    if (node == nullptr)
        return nullptr;
    if (node->ele->addr == val)
        return node;
    else if (node->left && val < node->ele->addr)
        return recursiveSearch(node->left, val);
    else if (node->right && val > node->ele->addr)
        return recursiveSearch(node->right, val);
    return nullptr;
}

void AVL::removeSubTree (Tree *Ptr)
{
    if (Ptr)
    {
        if (Ptr->left)
        {
            removeSubTree(Ptr->left);
        }
        if (Ptr->right)
        {
            removeSubTree(Ptr->right);
        }
        delete Ptr;
    }
}

void AVL::inOrderAVL (Tree *node)
{
    if (node != nullptr)
    {
        inOrderAVL(node->left);
        node->ele->print();
        inOrderAVL(node->right);
    }
}

void AVL::preOrderAVL (Tree *node)
{
    if (node != nullptr)
    {
        node->ele->print();
        preOrderAVL(node->left);
        preOrderAVL(node->right);
    }
}

void AVL::print ()
{
    cout << "Print AVL in inorder:\n";
    this->inOrderAVL(this->root);
    cout << "Print AVL in preorder:\n";
    this->preOrderAVL(this->root);

}

AVL::~AVL ()
{
    removeSubTree(this->root);
}

Cache::Cache (SearchEngine *s, ReplacementPolicy *r)
{
    this->rp = r;
    this->s_engine = s;
}

Cache::~Cache ()
{
    delete this->rp;
    delete this->s_engine;
}

Data *Cache::read (int addr)
{
    Elem *tmp = this->s_engine->search(addr);
    if (tmp != nullptr)
    {
        this->rp->access(addr);
        return tmp->data;
    }
    return nullptr;
}


Elem *Cache::put (int addr, Data *cont)
{

    if (this->rp->isFull())
    {
        int removedAddr = this->rp->remove();
        Elem *temp = this->s_engine->search(removedAddr);
        this->s_engine->deleteNode(removedAddr);

        Elem *newElem = new Elem(addr, cont, true);
        this->s_engine->insert(newElem);
        this->rp->insert(newElem);
        return temp;
    }
    Elem *newElem = new Elem(addr, cont, true);
    this->s_engine->insert(newElem);
    this->rp->insert(newElem);
    return nullptr;
}

Elem *Cache::write (int addr, Data *cont)
{

    Elem *temp = this->s_engine->search(addr);
    if (temp != nullptr)
    {
        this->rp->access(addr);
        delete temp->data;
        temp->data = cont;
        temp->sync = false;

    }

    else
    {
        if (this->rp->isFull())
        {
            int removedAddr = this->rp->remove();
            Elem *tmp = this->s_engine->search(removedAddr);
            this->s_engine->deleteNode(removedAddr);

            Elem *newElem = new Elem(addr, cont, false);
            this->s_engine->insert(newElem);
            this->rp->insert(newElem);
            return tmp;
        }
        Elem *newElem = new Elem(addr, cont, false);
        this->s_engine->insert(newElem);
        this->rp->insert(newElem);
    }
    return nullptr;
}


void Cache::printRP ()
{
    this->rp->print();
}

void Cache::printSE ()
{
    this->s_engine->print();
}