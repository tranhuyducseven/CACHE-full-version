#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(const int &data) { this->data = data; }
};
class BinaryTree
{
private:
    Node *root;

protected:
    int getHeightRec(Node *);
    int countTwoChildrenNodesRec(Node *);
    Node *maxNodeRec(Node *&);

public:
    BinaryTree()
    {
        this->root = NULL;
    }
    int getHeight();
    int countTwoChildrenNodes();
    Node *maxNode();
};
int BinaryTree::getHeightRec(Node *node)
{
    if (node == NULL)
        return 0;
    int maxL = getHeightRec(node->left);
    int maxR = getHeightRec(node->right);
    return 1 + (maxL > maxR ? maxL : maxR);
}

int BinaryTree::getHeight()
{
    return getHeightRec(this->root);
}

int BinaryTree::countTwoChildrenNodesRec(Node *node)
{
    if (node == NULL)
        return 0;
    if (node->left && node->right)
    {
        return 1 + countTwoChildrenNodesRec(node->left) + countTwoChildrenNodesRec(node->right);
    }
    return countTwoChildrenNodesRec(node->left) + countTwoChildrenNodesRec(node->right);
}

int BinaryTree::countTwoChildrenNodes()
{
    return countTwoChildrenNodesRec(this->root);
}
Node *BinaryTree::maxNodeRec(Node *&node)
{
    if (node == NULL)
        return NULL;
    Node *maxNode = node;
    Node *maxL = maxNodeRec(node->left);
    Node *maxR = maxNodeRec(node->right);
    if (maxL && maxNode->data < maxL->data)
    {
        maxNode = maxL;
    }
    if (maxR && maxNode->data < maxR->data)
    {
        maxNode = maxR;
    }
    return maxNode;
}
int main()
{
    cout << "sasdsadsads";
    return 0;
}