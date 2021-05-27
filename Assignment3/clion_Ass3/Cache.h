#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class ReplacementPolicy
{
protected:
    int count = 0;
public:

    virtual void access (int) = 0;

    virtual void insert (Elem *) = 0;

    virtual void remove () = 0;

    virtual void print () = 0;

    virtual ~ReplacementPolicy () = 0;
};


class FIFO : public ReplacementPolicy
{
private:
    Elem **arr;
public:
    FIFO ()
    {
        this->arr = new Elem *[MAXSIZE];
        for (int i = 0; i < MAXSIZE; i++)
            this->arr[i] = nullptr;
    }

    ~FIFO ()
    {
        for (int i = 0; i < MAXSIZE; i++)
        {
            if (this->arr[i] != nullptr)
                delete arr[i];
        }
        delete[] arr;
        this->count = 0;
    }

    void access (int);

    void insert (Elem *e);

    Elem *get (int);

    void remove ();


    void print ();

};

enum STATUS_TYPE
{
    NIL, NON_EMPTY, DELETED
};

class Node
{
public:
    Node *next;
    Node *prev;
    Elem *elem;

    Node ()
    {
        this->next = nullptr;
        this->prev = nullptr;
        this->elem = nullptr;
    }

    explicit Node (Elem *e)
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
    OpenAddressingHash (int size)
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

    int hashFunction (int, int) const;

    int insertKey (Node *);

    int searchKey (int);

    void removeKey (int);

    Node *getNodeContainKey (int);

    ~OpenAddressingHash ()
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
    MRU ()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->hash = new OpenAddressingHash(MAXSIZE);
    };

    ~MRU ()
    {
        delete this->hash;
        this->count = 0;
    };

    void putOnTop (Node *);

    void removeNode (Node *);

    void access(int);

    void insert (Elem *);

    void remove ();

    void print ();
};

class LRU : public MRU
{
public:
    void remove () override;
};

class ElementHeap
{
public:
    Elem *elem;
    int freq;

    ElementHeap ()
    {
        this->freq = 1;
        this->elem = nullptr;
    }

     ElementHeap (Elem *e)
    {
        this->freq = 1;
        this->elem = e;
    }

};

class MinHeap
{

private:
    ElementHeap **data;
    int size;
public:
    MinHeap (int size)
    {
        this->data = new ElementHeap *[MAXSIZE];
        for (int i = 0; i < MAXSIZE; i++)
        {
            this->data[i] = nullptr;
        }
        this->size = size;
    }

    ~MinHeap ()
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

    void reHeapUp (int index);

    void reHeapDown (int index);

    void insertHeap (ElementHeap *ele);

    Elem *get (int);

    void remove ();

    void print ();
};

class LFU : public ReplacementPolicy
{
private:
    MinHeap *heap;
public:
    LFU ()
    {
        this->heap = new MinHeap(this->count);
    }

    ~LFU ()
    {
        delete this->heap;
    }

    void insert (Elem *);

    void access (int);

    void remove ();

    void print ();

};

class SearchEngine
{
public:
    virtual Elem *search (int) = 0; // -1 if not found

    virtual void insert (Elem *) = 0;

    virtual void deleteNode (int) = 0;

    virtual void print () = 0;

    virtual ~SearchEngine () = 0;
};

class DBHashing : public SearchEngine
{
private:
    int (*h1) (int);

    int (*h2) (int);

    int size;

    STATUS_TYPE *status;

    Elem **arr;

public:
    DBHashing (int (*h1) (int), int (*h2) (int), int s)
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

    ~DBHashing ()
    {
        for (int i = 0; i < this->size; i++)
        {
            delete this->arr[i];
        }
        delete[] this->arr;
        delete this->status;
    };

    int searchHashing (int);

    void insert (Elem *);

    void deleteNode (int);

    void print ();

    Elem *search (int);
};

class Tree
{
public:
    Elem *ele;
    Tree *left;
    Tree *right;
    int balance;

    Tree () : ele(nullptr), left(nullptr), right(nullptr), balance(0)
    {};

    Tree (Elem *&val) : ele(val), left(nullptr), right(nullptr), balance(0)
    {};
};

class AVL : public SearchEngine
{
public:
    Tree *root;

    AVL () : root(nullptr)
    {};

    Tree *rotateRight (Tree *&);

    Tree *rotateLeft (Tree *&);

    Tree *leftBalance (Tree *&, bool &);

    Tree *rightBalance (Tree *&Tree, bool &taller);

    Tree *removeLeftBalance (Tree *&, bool &);

    Tree *removeRightBalance (Tree *&, bool &);

    void removeSubTree (Tree *);

    Tree *recursiveSearch (Tree *root, int val);

    Tree *insertRec (Tree *&, Elem *&, bool &);

    Tree *removeRec (Tree *&, const int &, bool &);

    void inOrderAVL (Tree *);

    void preOrderAVL (Tree *);

    Elem *search (int);

    void insert (Elem *);

    void deleteNode (int);

    void print ();

    ~AVL ()
    { removeSubTree(this->root); };

};


#endif