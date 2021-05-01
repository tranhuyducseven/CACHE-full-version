int BinaryTree::getHeightRec(Node *node)
{
    if(node==NULL) return 0;
    int a = getHeightRec(node->left);
    int b = getHeightRec(node->right);
    if(a<b) return b+1;
    return a+1;
	
}

int BinaryTree::getHeight()
{
	return getHeightRec(this->root);
}

//2
int BinaryTree::countTwoChildrenNodesRec(Node *node)
{
    if(node==NULL) return 0;
    if(node->left&&node->right){
    return 1+ countTwoChildrenNodesRec(node->left)+countTwoChildrenNodesRec(node->right);
    }
    return countTwoChildrenNodesRec(node->left)+countTwoChildrenNodesRec(node->right);

}


int BinaryTree::countTwoChildrenNodes()
{
    return countTwoChildrenNodesRec(this->root);
}
//3
void BinaryTree::levelOrderTraverse()
{
	if(!this->root) return;
	queue<Node *> q;
	q.push(root);
	while(!q.empty())
	{
	  Node *node = q.front();
	  cout<< node -> data<<" ";
	  q.pop();
	  if(node->left)
	  {
	   q.push(node->left);
	  }
	  if(node->right)
	  {
	   q.push(node->right);
	  }
	}
}
//4
bool BinarySearchTree::addRec(Node *&node, const int &value)
{
    if(node==NULL)
    {
        Node *newNode = new Node(value);
        node = newNode;
        return true;
    }
    if(node -> data == value) return false;
    if(value < node -> data)
        return addRec(node->left, value);
    return addRec(node->right, value);
	
}

bool BinarySearchTree::add(const int &value)
{
	return addRec(this->root, value);
}
//5
Node* BinaryTree::maxNodeRec(Node *&node)
{
    if(node == NULL) return NULL;
    Node *maxNode = node;
    Node *leftMax = maxNodeRec(node->left);
    Node *rightMax = maxNodeRec(node->right);
    if(leftMax && maxNode->data < leftMax -> data)
        maxNode = leftMax;
    if(rightMax && maxNode->data < rightMax-> data)
        maxNode = rightMax;
    return maxNode;
}


Node* BinaryTree::maxNode()
{
 return maxNodeRec(this->root);
}
//6
bool BinarySearchTree :: removeRec(Node *& node, const int &value)
{
    if(node == NULL) return false;
    if(value < node -> data)
        return removeRec(node->left, value);
    else if (value> node ->data)
        return removeRec(node->right, value);
    else 
    {
        if(node->left == NULL)
            {
                Node *del = node;
                node = node ->right;
                delete del;
                return true;
            }
         else if(node->right == NULL)
            {
                Node *del = node;
                node = node ->left;
                delete del;
                return true;
            }
        else
        {
            
                Node *dltPtr = node->left;
                while (dltPtr->right != NULL)
                    dltPtr = dltPtr->right;
                node->data = dltPtr->data;
                return removeRec(node->left, dltPtr->data);
            
        }       
        
    }
    

}
bool BinarySearchTree :: remove(const int &value){
    return removeRec(this->root, value);
}
