#include "main.h"

int AVLTree::getHeight(TreeNode *r) {
    if (r == nullptr)
        return -1;
    else {
        int leftHeight = getHeight(r->left);
        int rightHeight = getHeight(r->right);
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

int AVLTree::getBalanceFactor(TreeNode *r) {
    if (r == nullptr)
        return -1;
    return getHeight(r->left) - getHeight(r->right);
}

TreeNode *AVLTree::rightRotate(TreeNode *r) {
    TreeNode *child = r->left;
    TreeNode *temp = child->right;
    child->right = r;
    r->left = temp;
    return child;
}

TreeNode *AVLTree::leftRotate(TreeNode *r) {
    TreeNode *child = r->right;
    TreeNode *temp = child->left;
    child->left = r;
    r->right = temp;
    return child;
}

TreeNode *AVLTree::insert(TreeNode *root, Elem *temp) {
    // insert nodes like BST
    if (root == nullptr) {
        root = new TreeNode(temp);
        return root;
    }
    if (temp->addr < root->ele->addr)
        root->left = insert(root->left, temp);
    else if (temp->addr > root->ele->addr)
        root->right = insert(root->right, temp);
    else
        return root;
    //get balanceFactor
    int bf = getBalanceFactor(root);
    // left of left
    if (bf > 1 && temp->addr < root->left->ele->addr)
        return rightRotate(root);
    // right of right
    if (bf < -1 && temp->addr > root->right->ele->addr)
        return leftRotate(root);
    // left of right
    if (bf < -1 && temp->addr < root->right->ele->addr) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    // right of left
    if (bf > 1 && temp->addr > root->left->ele->addr) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
}

TreeNode *AVLTree::recursiveSearch(TreeNode *root, int val) {
    if (root == nullptr || root->ele->addr == val)
        return root;
    else if (val < root->ele->addr)
        return recursiveSearch(root->left, val);
    else
        return recursiveSearch(root->right, val);
}

void AVLTree::removeSubTree(TreeNode *Ptr) {
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

TreeNode *AVLTree::deleteNode(TreeNode *root, int val) {
    if (root == nullptr) //base case
        return root;
    else if (val < root->ele->addr) // val smaller
        root->left = deleteNode(root->left, val);
    else if (val > root->ele->addr) // val larger
        root->right = deleteNode(root->right, val);
    else // if val matches address
    {
        // one child or no child
        if (root->left == nullptr) {
            TreeNode *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode *temp = root->left;
            delete root;
            return temp;
        } else //  two children
        {
            TreeNode *temp = root->left;
            while (temp->right != nullptr)
                temp = temp->right;
            root->ele->addr = temp->ele->addr;
            root->left = deleteNode(root->left, temp->ele->addr);
        }
    }
    int bf = getBalanceFactor(root);
    if (bf == 2 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);
    else if (bf == 2 && getBalanceFactor(root->left) == -1) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (bf == -2 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);
    else if (bf == -2 && getBalanceFactor(root->right) == 1) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Data *Cache::read(int addr) {
    TreeNode *temp = this->obj.recursiveSearch(obj.ROOT, addr);
    return (temp != nullptr) ? temp->ele->data : nullptr;
}

Elem *Cache::put(int addr, Data *cont) {
    //put to queue
    if (p == 15) {
        Elem *temp = this->arr[0];
        for (int i = 0; i < p - 1; i++) {
            arr[i] = arr[i + 1];
        }

        arr[14] = new Elem(addr, cont, true);


        //delete node
        this->obj.ROOT = this->obj.deleteNode(this->obj.ROOT, temp->addr);

        //add new node
        this->obj.ROOT = this->obj.insert(obj.ROOT, this->arr[14]);
        return temp;
    }
    arr[p++] = new Elem(addr, cont, true);
       //put to AVLTree
    this->obj.ROOT = this->obj.insert(obj.ROOT, this->arr[p - 1]);
    return nullptr;
}

Elem *Cache::write(int addr, Data *cont) {
    bool found = false;
    //write to queue;
    for (int i = 0; i < p; i++)
        if (arr[i]->addr == addr) {

            arr[i]->data = cont;
            arr[i]->sync = false;
            found = true;
            //write to  AVL
            TreeNode *nodeFound = this->obj.recursiveSearch(obj.ROOT, addr);
            if (nodeFound) {
                nodeFound->ele->data = cont;
                nodeFound->ele->sync = false;
            }
            break;
        }

    // Not found
    if (!found) {
        if (p == 15) {
            Elem *temp = this->arr[0];
            //store attributes of temp;
            int tempAddr = temp->addr;
            Data *tempData = temp->data;
            //delete first element
            for (int i = 0; i < p - 1; i++)
                arr[i] = arr[i + 1];

            //add last element
            arr[14] = new Elem(addr, cont, false);

            //delete from AVL
            this->obj.ROOT = this->obj.deleteNode(this->obj.ROOT, temp->addr);

            //add new node
            this->obj.ROOT = this->obj.insert(obj.ROOT, this->arr[14]);

            temp->addr = tempAddr;
            temp->data = tempData;
            return temp;
        }
        arr[p++] = new Elem(addr, cont, false);
        this->obj.ROOT = this->obj.insert(obj.ROOT, this->arr[p - 1]);
    }

    return nullptr;
}

void Cache::print() {
    for (int i = 0; i < p; i++)
        arr[i]->print();
}

void Cache::preOrder() {
    preOrderAVL(this->obj.ROOT);
}

void Cache::preOrderAVL(TreeNode *root) {
    if (root != nullptr) {
        root->ele->print();
        preOrderAVL(root->left);
        preOrderAVL(root->right);
    }
}

void Cache::inOrder() {
    inOrderAVL(this->obj.ROOT);
}

void Cache::inOrderAVL(TreeNode *root) {
    if (root != nullptr) {
        inOrderAVL(root->left);
        root->ele->print();
        inOrderAVL(root->right);
    }
}