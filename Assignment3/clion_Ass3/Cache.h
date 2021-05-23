#ifndef CACHE_H
#define CACHE_H

#include "main.h"

enum STATUS_TYPE {
    NIL,
    NON_EMPTY,
    DELETED
};

class Node {
public:
    Node *next;
    Node *prev;
    Elem *elem;

    Node() : next(nullptr), prev(nullptr), elem(nullptr) {};

    explicit Node(Elem *e) : next(nullptr), prev(nullptr), elem(e) {};
};

class OpenAddressingHash {
private:
    STATUS_TYPE *status;
    Node **data;
    int size;
public:
    OpenAddressingHash(int size) {
        this->size = size;
        this->data = new Node *[size];
        this->status = new STATUS_TYPE[size];
        for (int i = 0; i < size; i++) {
            this->status[i] = NIL;
        }
    }


    int hashFunction(int, int) const;

    int insertKey(Node *);

    int searchKey(int);

    void removeKey(int);

    Node *getNodeContainKey(int);

    ~OpenAddressingHash() {
        for (int i = 0; i < this->size; i++) {
            delete this->data[i]->elem;
            delete this->data[i];
        }
        delete[] this->data;
        delete[] this->status;
    }

};


class ReplacementPolicy {
protected:
    int count;
public:
    virtual void insert(Elem *) = 0;

    virtual Elem *get(int) = 0;

    virtual void remove() = 0;

    virtual void print() = 0;

    virtual void replace(Elem *e, int key) = 0;
};

class SearchEngine {
public:
    virtual int search(int key) = 0; // -1 if not found
    virtual void insert(int key, int idx) = 0;

    virtual void deleteNode(int key) = 0;

    virtual void print(ReplacementPolicy *r) = 0;
};

class FIFO : public ReplacementPolicy {
private:
    Elem **arr;
public:
    FIFO() {
        this->count = 0;
        this->arr = new Elem *[MAXSIZE];
    }

    ~FIFO() {
        for (int i = 0; i < MAXSIZE; i++) {
            delete arr[i];
        }
        delete[] arr;
    }

    int insert(Elem *e, int idx) { return 0; }

    void access(int idx) {}

    void print() {}
};

class MRU : public ReplacementPolicy {
protected:
    Node *head;
    Node *tail;
    OpenAddressingHash *hash;
public:
    MRU() {
        this->count = 0;
        this->head = nullptr;
        this->tail = nullptr;
        this->hash = new OpenAddressingHash(MAXSIZE);
    };

    ~MRU() {
        delete this->hash;
    };

    void putOnTop(Node *);

    void removeNode(Node *);

    void insert(Elem *);

    void remove() {
        this->removeNode(this->head);
    }

    Elem *get(int);

    void replace(int, Elem *);

    void print();


};

class LRU : public MRU {
public:
    void remove() override;
};

class LFU : public ReplacementPolicy {
public:
    LFU() {}

    ~LFU() {}

    int insert(Elem *e);

    void access(int idx) {}

    int remove() { return 0; }

    void print() {}
};

class DBHashing : public SearchEngine {
public:
    DBHashing(int (*h1)(int), int (*h2)(int), int s) {}

    ~DBHashing() {}

    void insert(int key, int i) {}

    void deleteNode(int key) {}

    void print(ReplacementPolicy *q) {}

    int search(int key) { return 0; }
};

class AVL : public SearchEngine {
public:
    AVL() {}

    ~AVL() {}

    void insert(int key, int i) {}

    void deleteNode(int key) {}

    void print(ReplacementPolicy *q) {}

    int search(int key) { return 0; }
};

#endif