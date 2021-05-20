#include "main.h"


Node *AVL::rotateRight(Node *&node) {
    Node *leftTree = node->left;
    node->left = leftTree->right;
    leftTree->right = node;
    return leftTree;
}

Node *AVL::rotateLeft(Node *&node) {
    Node *rightTree = node->right;
    node->right = rightTree->left;
    rightTree->left = node;
    return rightTree;
}

Node *AVL::leftBalance(Node *&node, bool &taller) {
    if (node->left->balance == -1) {
        node->left->balance = 0;
        node->balance = 0;
        node = rotateRight(node);
        taller = false;
    } else {
        if (node->left->right->balance == 0) {
            node->balance = 0;
            node->left->balance = 0;
            node->left->right->balance = 0;
        } else if (node->left->right->balance == -1) {
            node->balance = 1;
            node->left->balance = 0;
            node->left->right->balance = 0;
        } else {
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

Node *AVL::rightBalance(Node *&node, bool &taller) {
    if (node->right->balance == 1) {
        node->right->balance = 0;
        node->balance = 0;
        node = rotateLeft(node);
        taller = false;
    } else {
        if (node->right->left->balance == 0) {
            node->balance = 0;
            node->right->balance = 0;
            node->right->left->balance = 0;
        } else if (node->right->left->balance == 1) {
            node->balance = -1;
            node->right->balance = 0;
            node->right->left->balance = 0;
        } else {
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

void AVL::insert(Elem *&value) {
    bool isTaller = false;
    this->root = insertRec(this->root, value, isTaller);
}

Node *AVL::insertRec(Node *&node, Elem *&newElem, bool &taller) {
    if (node == nullptr) {
        taller = true;
        node = new Node(newElem);
        return node;
    }
    if (newElem->addr < node->ele->addr) {
        node->left = insertRec(node->left, newElem, taller);
        if (taller) {
            if (node->balance == -1) {
                node = leftBalance(node, taller);
            } else if (node->balance == 0) {
                node->balance = -1;
            } else {
                node->balance = 0;
                taller = false;
            }
        }
    } else if (newElem->addr > node->ele->addr) {
        node->right = insertRec(node->right, newElem, taller);
        if (taller) {
            if (node->balance == -1) {
                node->balance = 0;
                taller = false;
            } else if (node->balance == 0) {
                node->balance = 1;
            } else {
                node = rightBalance(node, taller);
            }
        }
    }
    return node;
}

Node *AVL::removeRightBalance(Node *&r, bool &isShorter) {
    if (r->balance == -1) {
        r->balance = 0;
    } else if (r->balance == 0) {
        r->balance = 1;
        isShorter = false;
    } else {
        if (r->right->balance == 1) {
            r->balance = 0;
            r->right->balance = 0;
            r = rotateLeft(r);
        } else if (r->right->balance == 0) {
            r->balance = 1;
            r->right->balance = -1;
            isShorter = false;
            r = rotateLeft(r);
        } else {
            Node *rRight = r->right;
            if (rRight->left->balance == 1) {
                r->balance = -1;
                rRight->balance = 0;
                rRight->left->balance = 0;
            } else if (rRight->left->balance == -1) {
                r->balance = 0;
                rRight->balance = 1;
                rRight->left->balance = 0;
            } else {
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

Node *AVL::removeLeftBalance(Node *&r, bool &isShorter) {
    if (r->balance == 1) {
        r->balance = 0;
    } else if (r->balance == 0) {
        r->balance = -1;
        isShorter = false;
    } else {
        if (r->left->balance == -1) {
            r->balance = 0;
            r->left->balance = 0;
            r = rotateRight(r);
        } else if (r->left->balance == 0) {
            r->balance = -1;
            r->left->balance = 1;
            isShorter = false;
            r = rotateRight(r);
        } else {
            Node *rLeft = r->left;
            if (rLeft->right->balance == -1) {
                r->balance = 1;
                rLeft->balance = 0;
                rLeft->right->balance = 0;
            } else if (rLeft->right->balance == 1) {
                r->balance = 0;
                rLeft->balance = -1;
                rLeft->right->balance = 0;
            } else {
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


void AVL::remove(const int &value) {
    bool isShorter = false;
    this->root = removeRec(root, value, isShorter);
}

Node *AVL::removeRec(Node *&r, const int &val, bool &isShorter) {
    if (r == nullptr) {
        isShorter = false;
        return r;
    } else {
        if (val < r->ele->addr) {
            r->left = removeRec(r->left, val, isShorter);
            if (isShorter) {
                r = removeRightBalance(r, isShorter);
            }
            return r;
        } else if (val > r->ele->addr) {
            r->right = removeRec(r->right, val, isShorter);
            if (isShorter) {
                r = removeLeftBalance(r, isShorter);
            }
            return r;
        } else {
            if (r->left == nullptr) {
                Node *newRoot = r->right;
                isShorter = true;
                delete r;
                return newRoot;
            } else if (r->right == nullptr) {
                Node *newRoot = r->left;
                isShorter = true;
                delete r;
                return newRoot;
            } else {
                Node *rightMinLeaf = r->right;
                while (rightMinLeaf->left != nullptr) {
                    rightMinLeaf = rightMinLeaf->left;
                }
                r->ele = rightMinLeaf->ele;
                r->right = removeRec(r->right, rightMinLeaf->ele->addr, isShorter);
                if (isShorter) {
                    r = removeLeftBalance(r, isShorter);
                }
            }
            return r;
        }
    }
}


Node *AVL::recursiveSearch(Node *node, int val) {
    if (node == nullptr )
        return nullptr;
    if(node->ele->addr == val)
        return node;
    else if (node->left && val < node->ele->addr)
        return recursiveSearch(node->left, val);
    else if (node->right && val > node->ele->addr)
        return recursiveSearch(node->right, val);
    return nullptr;
}

void AVL::removeSubTree(Node *Ptr) {
    if (Ptr) {
        if (Ptr->left) {
            removeSubTree(Ptr->left);
        }
        if (Ptr->right) {
            removeSubTree(Ptr->right);
        }
        delete Ptr;
    }
}


Data *Cache::read(int addr) {
    Node *temp = this->obj.recursiveSearch(obj.root, addr);
    if (temp != nullptr) {
        return temp->ele->data;
    }
    return nullptr;
}

Elem *Cache::put(int addr, Data *cont) {
    //put to queue
    if (p == MAXSIZE) {
        Elem *temp = this->arr[0];
        //delete node
        this->obj.remove(temp->addr);
        for (int i = 0; i < p - 1; i++) {
            arr[i] = arr[i + 1];
        }

        Elem *newEle = new Elem(addr, cont, true);
        arr[MAXSIZE-1] = newEle;
        //add new node
        this->obj.insert(newEle);
        return temp;
    }
    arr[p++] = new Elem(addr, cont, true);
    //put to AVL

    this->obj.insert(this->arr[p - 1]);
    return nullptr;
}

Elem *Cache::write(int addr, Data *cont) {
    bool found = false;
    Node * nodeFound = this->obj.recursiveSearch(this->obj.root, addr);
    if(nodeFound && nodeFound->ele){
        delete nodeFound->ele->data;
        nodeFound->ele->data = cont;
        nodeFound->ele->sync= false;
        found = true;
    }

    // Not found
    if (!found) {
        if (p == MAXSIZE) {
            Elem *temp = this->arr[0];
            //delete node

            this->obj.remove(temp->addr);
            for (int i = 0; i < p - 1; i++) {
                arr[i] = arr[i + 1];
            }
            Elem *newEle = new Elem(addr, cont, false);
            arr[MAXSIZE-1] = newEle;
            //add new node
            this->obj.insert(newEle);
            return temp;
        }
        arr[p++] = new Elem(addr, cont, false);

        this->obj.insert(this->arr[p - 1]);

    }

    return nullptr;
}

void Cache::print() {
    for (int i = 0; i < p; i++)
        arr[i]->print();
}

void Cache::preOrder() {
    preOrderAVL(this->obj.root);
}

void Cache::preOrderAVL(Node *root) {
    if (root != nullptr) {
        root->ele->print();
        preOrderAVL(root->left);
        preOrderAVL(root->right);
    }
}

void Cache::inOrder() {
    inOrderAVL(this->obj.root);

}

void Cache::inOrderAVL(Node *root) {
    if (root != nullptr) {
        inOrderAVL(root->left);
        root->ele->print();
        inOrderAVL(root->right);
    }
}
//20:21 4/5/2021