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

    virtual int remove() = 0;

    virtual void print() = 0;

    bool isFull() const
    {
        return count == MAXSIZE;
    }
    

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

    int remove() override;

    void print() override;
};

class Node
{
public:
    Node *next;
    Node *prev;
    Elem *elem;

    Node() : next(nullptr), prev(nullptr), elem(nullptr){};

    explicit Node(Elem *e) : next(nullptr), prev(nullptr), elem(e){};
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

    int hashFunction(int, int) const;

    void insertKey(Node *);

    int searchKey(int);

    void removeKey(int);

    void print()
    {
        cout << endl
             << endl
             << endl
             << "Print in hash MRU:" << endl;
        for (int i = 0; i < this->size; i++)
        {
            if (this->data[i] != nullptr)
                this->data[i]->elem->print();
            else
                cout << "nullptr at index: " << i << endl;
        }
    }

    Node *getNodeContainKey(int);

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
};

class MRU : public ReplacementPolicy
{
protected:
    Node *head;
    Node *tail;
    OpenAddressingHash *hash;

public:
    MRU();

    ~MRU() override;

    void putOnTop(Node *);

    void removeNode(Node *);

    void access(int) override;

    void insert(Elem *) override;

    int remove() override;

    void print() override;

    void printCache()
    {
        this->hash->print();
        cout <<endl<< "Print list Cache:" << endl;
        Node *temp = this->head;
        while (temp != nullptr)
        {
            temp->elem->print();
            temp = temp->next;
        }
    }
};

class LRU : public MRU
{
public:
    int remove() override;
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

    int remove();

    void print();
};

class LFU : public ReplacementPolicy
{
private:
    MinHeap *heap;

public:
    LFU();

    ~LFU() override;

    void insert(Elem *) override;

    void access(int) override;

    int remove() override;

    void print() override;
};

class SearchEngine
{
public:
    virtual Elem *search(int) = 0;

    virtual void insert(Elem *) = 0;

    virtual void deleteNode(int) = 0;

    virtual void print() = 0;

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
    DBHashing(int (*)(int), int (*)(int), int);

    ~DBHashing() override;

    int searchHashing(int);

    void insert(Elem *) override;

    void deleteNode(int) override;

    void print() override;

    Elem *search(int) override;
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
    AVL();
    ~AVL() override;

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

    Elem *search(int) override;

    void insert(Elem *) override;

    void deleteNode(int) override;

    void print() override;
};

#endif