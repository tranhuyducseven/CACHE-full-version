#include <iostream>
using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int data;
    Node() : left(NULL), right(NULL), data(0){};
    Node(int x) : left(NULL), right(NULL), data(x){};
};
int getHeight(Node *root)
{
    if (root == NULL)
        return 0;
    int a = getHeight(root->left);
    int b = getHeight(root->right);
    if (a > b)
        return a + 1;
    return b + 1;
}
class BianaryTree
{
public:
    Node *insertNode(Node *root, int val)
    {
        if (root == NULL)
            return new Node(val);
        else
        {
            Node *cur;
            if (val <= root->data)
            {
                cur = insertNode(root->left, val);
                root->left = cur;
            }
            else
            {
                cur = insertNode(root->right, val);
                root->right = cur;
            }

            return root;
        }
    }

    int JudgeComplete(Node *root)
    {
        if (root == NULL)
            return 1;
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        if (leftHeight == rightHeight)
        {
            return JudgeComplete(root->left) && JudgeComplete(root->right);
        }
        return 0;
    }
};

int main()
{
    BianaryTree myTree;
    Node *root=NULL;
    int values[6] = {1,2,3,4,5,6};
    for (int i = 0; i < 6; i++)
    {
        root = myTree.insertNode(root, values[i]);
    }
    cout << "isCompleteTree: " << myTree.JudgeComplete(root);
}