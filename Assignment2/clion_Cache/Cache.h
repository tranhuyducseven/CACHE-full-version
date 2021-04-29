#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class TreeNode {
public:
    Elem *ele;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : ele(nullptr), left(nullptr), right(nullptr) {};

    TreeNode(Elem *val) : ele(val), left(nullptr), right(nullptr) {};
};

class AVLTree {
public:
    TreeNode *ROOT;
public:
    AVLTree() : ROOT(nullptr) {};

    int getHeight(TreeNode *r);

    int getBalanceFactor(TreeNode *r);

    TreeNode *rightRotate(TreeNode *r);

    TreeNode *leftRotate(TreeNode *r);

    TreeNode *insert(TreeNode *root, Elem *temp);

    void removeSubTree(TreeNode *Ptr);

    TreeNode *recursiveSearch(TreeNode *root, int val);

    TreeNode *deleteNode(TreeNode *, int);

    ~AVLTree() { removeSubTree(this->ROOT); };
};

class Cache {
    Elem **arr;
    int p;
    AVLTree obj;

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

    void preOrderAVL(TreeNode *);

    void inOrderAVL(TreeNode *);

};
//12:53 AM
#endif