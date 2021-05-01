#include <iostream>

#define SPACE 10
using namespace std;

class TreeNode
{
public:
    int key;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : key(0), left(NULL), right(NULL){};
    TreeNode(int val) : key(val), left(NULL), right(NULL){};
    ~TreeNode(){};
};

class AVLTREE
{
public:
    TreeNode *ROOT;
    AVLTREE() : ROOT(NULL){};
    bool isEmpty()
    {
        return (this->ROOT) ? false : true;
    }

    int getHeight(TreeNode *r)
    {
        if (r == NULL)
            return -1;
        else
        {
            int leftHeight = getHeight(r->left);
            int rightHeight = getHeight(r->right);
            return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
        }
    }

    int getBalanceFactor(TreeNode *r)
    {
        if (r == NULL)
            return -1;
        return getHeight(r->left) - getHeight(r->right);
    }

    TreeNode *rightRotate(TreeNode *r)
    {
        TreeNode *child = r->left;
        TreeNode *temp = child->right;
        child->right = r;
        r->left = temp;
        return child;
    }

    TreeNode *leftRotate(TreeNode *r)
    {
        TreeNode *child = r->right;
        TreeNode *temp = child->left;
        child->left = r;
        r->right = temp;
        return child;
    }

    TreeNode *insert(TreeNode *root, int value)
    {
        // insert nodes like BST
        if (root == NULL)
        {
            root = new TreeNode(value);
            return root;
        }
        if (value < root->key)
            root->left = insert(root->left, value);
        else if (value > root->key)
            root->right = insert(root->right, value);
        else
            return root;
        //get balanceFactor
        int bf = getBalanceFactor(root);
        // left of left
        if (bf > 1 && value < root->left->key)
            return rightRotate(root);
        // right of right
        if (bf < -1 && value > root->right->key)
            return leftRotate(root);
        // left of right
        if (bf < -1 && value < root->right->key)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        // right of left
        if (bf > 1 && value > root->left->key)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        return root;
    }

    void print2D(TreeNode *root, int space)
    {
        if (root == NULL)
            return;
        space += SPACE;
        print2D(root->right, space);
        cout << endl;
        for (int i = SPACE; i < space; i++)
            cout << " ";
        cout << root->key << endl;
        print2D(root->left, space);
    }

    void removeSubTree(TreeNode *Ptr)
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

    TreeNode *recursiveSearch(TreeNode *root, int val)
    {
        if (root == NULL || root->key == val)
        {
            cout << "Found" << endl;
            return root;
        }
        else if (val < root->key)
            return recursiveSearch(root->left, val);
        else
            return recursiveSearch(root->right, val);
    }

    ~AVLTREE()
    {
        removeSubTree(this->ROOT);
    };
};

int main()
{
    AVLTREE obj;
    int arr[12] = {3, 4, 5, 11, 9, 2, 4, 10, 5, 7, 8, 6};
    for (int i = 0; i < 12; i++)
    {
        obj.ROOT = obj.insert(obj.ROOT, arr[i]);
    }
    obj.print2D(obj.ROOT, 5);
    TreeNode *temp = obj.recursiveSearch(obj.ROOT, 7);
    temp->key=999;
    obj.print2D(obj.ROOT,5);
    return 0;
}