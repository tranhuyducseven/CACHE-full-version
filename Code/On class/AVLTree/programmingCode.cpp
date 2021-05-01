#include <bits/stdc++.h>
#define SPACE 5
using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}
void printInteger(int &n)
{
    cout << n << " ";
}

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    BalanceValue balance;
    Node(const int &val)
    {
        data = val;
        left = right = NULL;
        balance = EH;
    }
};

class AVL
{
public:
    Node *root;

protected:
    Node *rotateRight(Node *&node);
    Node *rotateLeft(Node *&node);
    Node *leftBalance(Node *&node, bool &taller);
    Node *rightBalance(Node *&node, bool &taller);
    //TODO Methods
    Node *insertRec(Node *&node, const int &value, bool &taller);

public:
    AVL()
    {
        this->root = NULL;
    }

    // TODO Methods
    void insert(const int &value);
    void remove(const int &value);
    void print2D(Node*root, int space);
};
Node *AVL::rotateRight(Node *&node)
{
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}
Node *AVL::rotateLeft(Node *&node)
{
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = temp;
    return temp;
}
Node *AVL::leftBalance(Node *&node, bool &taller)
{
    Node *leftTree = node->left;
    // LOL
    if (leftTree->balance == LH)
    {
        node = rotateRight(node);
        node->balance = EH;
        leftTree->balance = EH;
        taller = false;
    }
    else
    {
        Node *rightTree = leftTree->right;
        if (rightTree)
        {
            if (rightTree->balance == LH)
            {
                node->balance = RH;
                leftTree->balance = EH;
            }
            else if (rightTree->balance == EH)
                leftTree->balance = EH;
            else
            {
                node->balance = EH;
                leftTree->balance = LH;
            }
            rightTree->balance = EH;
            root->left = rotateLeft(leftTree);
            node = rotateRight(node);
            taller = false;
        }
    }
    return node;
}
Node *AVL::rightBalance(Node *&node, bool &taller)
{
    Node *rightTree = node->right;
    if (rightTree->balance == RH)
    {
        node = rotateLeft(node);
        node->balance = EH;
        rightTree->balance = EH;
        taller = false;
    }
    else
    {
        Node *leftTree = rightTree->left;
        if (leftTree)
        {
            if (leftTree->balance == RH)
            {
                node->balance = LH;
                rightTree->balance = EH;
            }
            else if (leftTree->balance == EH)
            {
                rightTree->balance = EH;
            }
            else
            {
                node->balance = EH;
                rightTree->balance = RH;
            }
            leftTree->balance = EH;
            node->right = rotateRight(rightTree);
            node = rotateLeft(node);
            taller = false;
        }
    }
    return node;
}

void AVL::insert(const int &value)
{
    bool taller = false;
    this->root = insertRec(this->root, value, taller);
}
Node *AVL::insertRec(Node *&node, const int &value, bool &taller)
{
    if (node == NULL)
    {
        taller = true;
        node = new Node(value);
        return node;
    }
    if (value < node->data)
    {
        node->left = insertRec(node->left, value, taller);
        if (taller)
        {
            if (node->balance == LH)
                node = leftBalance(node, taller);
            else if (node->balance == EH)
                root->balance = LH;
            else
            {
                root->balance = EH;
                taller = false;
            }
        }
    }
    else
    {
        node->right = insertRec(node->right, value, taller);
        if (taller)
        {
            if (node->balance == LH)
            {
                node->balance = EH;
                taller = false;
            }
            else if (root->balance == EH)
                root->balance = RH;
            else
                node = rightBalance(node, taller);
        }
    }
    return node;    
}
void AVL::print2D(Node *root, int space)
	{
		if (root == NULL)
			return;
		space += SPACE;
		print2D(root->right, space);
		cout << endl;
		for (int i = SPACE; i < space; i++)
			cout << " ";
		cout << root->data << endl;
		print2D(root->left, space);
	}
int main()
{
    AVL obj;
    obj.insert(3);
    obj.insert(5);
    obj.insert(4);
    obj.print2D(obj.root,2);

    return 0;
}