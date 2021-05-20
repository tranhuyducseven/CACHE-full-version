#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class Node {
public:
    Elem *ele;
    Node *left;
    Node *right;
    int balance;

    Node() : ele(nullptr), left(nullptr), right(nullptr), balance(0) {};

    Node(Elem *&val) : ele(val), left(nullptr), right(nullptr), balance(0) {};
};

class AVL {
public:
    AVL() : root(nullptr) {};
    Node *root;

    Node *rotateRight(Node *&);

    Node *rotateLeft(Node *&);

    Node *leftBalance(Node *&, bool &);

    Node *rightBalance(Node *&node, bool &taller);

    Node *removeLeftBalance(Node *&, bool &);

    Node *removeRightBalance(Node *&, bool &);

    void removeSubTree(Node *);

    Node *recursiveSearch(Node *root, int val);

    ~AVL() { removeSubTree(this->root); };

    Node *insertRec(Node *&, Elem *&, bool &);

    Node *removeRec(Node *&, const int &, bool &);

    void insert(Elem *&);

    void remove(const int &);


};

class Cache {
    Elem **arr;
    int p;
    AVL obj;

public:
    Cache(int s) {
        arr = new Elem *[(unsigned long) s];
        p = 0;
        for (int i = 0; i < MAXSIZE; i++)
            arr[i] = nullptr;
    }

    ~Cache() {
        for (int i = 0; i < MAXSIZE; i++) {
            delete arr[i];
        }
        delete[] arr;
    }

    Data *read(int addr);

    Elem *put(int addr, Data *cont);

    Elem *write(int addr, Data *cont);

    void print();

    void preOrder();

    void inOrder();

    void preOrderAVL(Node *);

    void inOrderAVL(Node *);



};
#endif
//20:21 4/5/2021