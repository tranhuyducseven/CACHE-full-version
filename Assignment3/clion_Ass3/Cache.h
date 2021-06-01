#ifndef CACHE_H
#define CACHE_H

#include "main.h"
enum STATUS_TYPE
{
    NIL,
    NON_EMPTY,
    DELETED
};

class ReplacementPolicy
{
protected:
    int count = 0;

public:
    virtual void access(int) = 0;

    virtual void insert(Elem *) = 0;

    virtual void remove() = 0;

    virtual void print() = 0;

    bool isFull() const
    {
        return count == MAXSIZE;
    }

    virtual int getAddressReplacement() = 0;

    virtual ~ReplacementPolicy() = default;
};

class FIFO : public ReplacementPolicy
{
private:
    Elem **arr;

public:
    FIFO();

    ~FIFO() override;

    void access(int) override;

    void insert(Elem *e) override;

    int getAddressReplacement() override;

    void remove() override;

    void print() override;
};

class Node
{
public:
    Node *next;
    Node *prev;
    Elem *elem;

    Node() : next(nullptr), prev(nullptr), elem(nullptr){};

    explicit Node(Elem *e)
    {
        this->next = nullptr;
        this->prev = nullptr;
        this->elem = e;
    }
};

class OpenAddressingHash
{
private:
    STATUS_TYPE *status;
    Node **data;
    int size;

public:
    explicit OpenAddressingHash(int size)
    {
        this->size = size;
        this->data = new Node *[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = nullptr;
        }
        this->status = new STATUS_TYPE[size];
        for (int i = 0; i < size; i++)
        {
            this->status[i] = NIL;
        }
    }

    ~OpenAddressingHash()
    {
        for (int i = 0; i < this->size; i++)
        {
            delete this->data[i]->elem;
            delete this->data[i];
        }
        delete[] this->data;
        delete[] this->status;
    }

    int hashFunction(int, int) const;

    void insertKey(Node *);

    int searchKey(int);

    void removeKey(int);

    Node *getNodeContainKey(int);
};

class MRU : public ReplacementPolicy
{
protected:
    Node *head;
    Node *tail;
    OpenAddressingHash *hash;

public:
    MRU()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->hash = new OpenAddressingHash(MAXSIZE);
    }

    ~MRU() override
    {
        delete this->hash;
        this->count = 0;
    }

    void putOnTop(Node *);

    void removeNode(Node *);

    void access(int) override;

    void insert(Elem *) override;

    void remove() override;

    int getAddressReplacement() override;

    void print() override;
};

class LRU : public MRU
{
public:
    void remove() override;
    int getAddressReplacement() override;
};

class ElementHeap
{
public:
    Elem *elem;
    int freq;

public:
    ElementHeap() : elem(nullptr), freq(1){};
    explicit ElementHeap(Elem *e) : elem(e), freq(1){};
};

class MinHeap
{

private:
    ElementHeap **data;
    int size;

public:
    explicit MinHeap(int size)
    {
        this->data = new ElementHeap *[MAXSIZE];
        for (int i = 0; i < MAXSIZE; i++)
        {
            this->data[i] = nullptr;
        }
        this->size = size;
    }

    ~MinHeap()
    {
        for (int i = 0; i < MAXSIZE; i++)
        {
            if (data[i] != nullptr)
            {
                delete this->data[i]->elem;
                delete this->data[i];
            }
        }
        delete[] this->data;
        this->size = 0;
    }

    void reHeapUp(int index);

    void reHeapDown(int index);

    void insertHeap(ElementHeap *ele);

    void access(int);

    int getAddrMin();

    void remove();

    void print();
};

class LFU : public ReplacementPolicy
{
private:
    MinHeap *heap;

public:
    LFU()
    {
        this->heap = new MinHeap(this->count);
    }

    ~LFU() override
    {
        delete this->heap;
    }

    void insert(Elem *) override;

    void access(int) override;

    int getAddressReplacement() override;

    void remove() override;

    void print() override;
};

class SearchEngine
{
public:
    virtual Elem *search(int, int &) = 0;

    virtual void insert(Elem *) = 0;

    virtual void deleteNode(int, int &) = 0;

    virtual void print() = 0;

    virtual int searchIndex(int) = 0;

    virtual ~SearchEngine() = default;
};

class DBHashing : public SearchEngine
{
private:
    int (*h1)(int);

    int (*h2)(int);

    int size;

    STATUS_TYPE *status;

    Elem **arr;

public:
    DBHashing(int (*h1)(int), int (*h2)(int), int s)
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

    ~DBHashing() override
    {
        for (int i = 0; i < this->size; i++)
            if (this->arr[i] != nullptr)
                delete this->arr[i];
        delete[] this->arr;
        delete this->status;
    }

    int searchIndex(int);

    void insert(Elem *) override;

    void deleteNode(int, int &) override;

    void print() override;

    Elem *search(int, int &) override;
};

class Tree
{
public:
    Elem *ele;
    Tree *left;
    Tree *right;
    int balance;

    Tree() : ele(nullptr), left(nullptr), right(nullptr), balance(0){};

    explicit Tree(Elem *&val) : ele(val), left(nullptr), right(nullptr), balance(0){};
};

class AVL : public SearchEngine
{
private:
    Tree *root;

public:
    AVL()
    {
        this->root = nullptr;
    }
    ~AVL() override
    {
        removeSubTree(this->root);
    }

    static Tree *rotateRight(Tree *&);

    static Tree *rotateLeft(Tree *&);

    static Tree *leftBalance(Tree *&, bool &);

    static Tree *rightBalance(Tree *&, bool &taller);

    static Tree *removeLeftBalance(Tree *&, bool &);

    static Tree *removeRightBalance(Tree *&, bool &);

    void removeSubTree(Tree *);

    Tree *recursiveSearch(Tree *, int val);

    Tree *insertRec(Tree *&, Elem *&, bool &);

    Tree *removeRec(Tree *&, const int &, bool &);

    void inOrderAVL(Tree *);

    void preOrderAVL(Tree *);

    Elem *search(int, int &) override;

    int searchIndex(int) override;

    void insert(Elem *) override;

    void deleteNode(int, int &) override;

    void print() override;
};

#endif