#include <bits/stdc++.h>
using namespace std;
template <class T>
class DLinkedList 
{
public:
    class Node;     //forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList(): head(NULL), tail(NULL), count(0) {};
    ~DLinkedList() {};
    void add(const T& e);
    void add(int index, const T& e);
    T removeAt(int index);
    bool removeItem(const T& removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T& e);
    int indexOf(const T& item);
    bool contains(const T& item);
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;
    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
        
        void Print()
        {
            cout << data << endl;
        }
    };
};

template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node *temp = new Node(e);
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp -> previous = tail;
        tail -> next = temp;
        tail = temp;
    }
    this -> count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    if (index < 0 || index > this -> count)
        throw out_of_range("...");
    Node *temp = new Node(e);
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else if (index == 0)
    {
        temp -> next = head;
        head -> previous = temp;
        head = temp;
    }
    else if (index == this -> count)
    {
        temp -> previous = tail;
        tail -> next = temp;
        tail = temp;
    }
    else
    {
        Node *node = head;
        for (int i = 0; i < index - 1; i++)
            node = node -> next;
        Node *nextNode = node -> next;
        node -> next = temp;
        temp -> previous = node;
        temp -> next = nextNode;
        nextNode -> previous = temp;
    }
    this -> count++;
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return this -> count;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this -> count || this -> count == 0)
        throw out_of_range("...");
    Node *temp = head;
    if (index == 0)
        return temp -> data;
    for (int i = 0; i < index; i++)
        temp = temp -> next;
    return temp -> data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this -> count || this -> count == 0)
        throw out_of_range("...");
    Node *temp = head;
    if (index == 0)
        temp -> data = e;
    else
    {
        for (int i = 0; i < index; i++)
            temp = temp -> next;
        temp -> data = e;
    }
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (this -> count == 0);
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    if (head -> data == item)
        return 0;
    else
    {
        Node *temp = head;
        for (int i = 1; i < this -> count; i++)
        {
            temp = temp -> next;
            if (temp -> data == item)
                return i;
        }
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    if (head -> data == item)
        return true;
    else
    {
        Node *temp = head;
        for (int i = 0; i < this -> count - 1; i++)
        {
            temp = temp -> next;
            if (temp -> data == item)
                return true;
        }
    }
    return false;
}


template <class T>
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index < 0 || index >= this -> count)
        throw out_of_range("...");
    T value;
    if (this -> count == 1) 
    {               
        Node* del = head;           
        value = del->data;         
        delete del;
        head = NULL;
        tail = NULL;
    }
    else 
    {
        if (index == 0) 
        {                   
            Node* del = head;               
            head = head->next;              
            head->previous = NULL;      
            value = del->data;
            delete del;
        }
        else if (index == count - 1) 
        {
            Node* del = tail;
            tail = tail->previous;
            tail->next = NULL;
            value = del->data;
            delete del;
        }
        else 
        {
            if (index < count / 2) 
            {
                Node* del = head;
                for (int i = 0; i < index; i++) 
                    del = del->next;
                del->previous->next = del->next;
                del->next->previous = del->previous;
                value = del->data;
                delete del;
            }
            else 
            {
                Node* del = tail;
                for (int i = count - 1; i > index; i--)
                    del = del->previous;
                del->previous->next = del->next;
                del->next->previous = del->previous;
                value = del->data;
                delete del;
            }
        }
    }
    this -> count--;
    return value;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node* scan = head;
    for (int i = 0; i < count; i++) 
    {
        if (scan->data == item) 
        {
            this->removeAt(i);
            return true;
        }
        scan = scan->next;
    }
    return false;
}

template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
    while (this->head != NULL)
        removeAt(0);
    tail = NULL;
}

template<class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack() {}
    void push(T item) ;
    T pop() ;
    T top() ;
    bool empty() ;
    int size() ;
    void clear() ;
};

template<class T>
void Stack<T>::push(T item)
{
    this->list.add(item);
}

template<class T>
T Stack<T>::pop()
{
    int size = this->list.size();
    return this->list.removeAt(size - 1);
}

template<class T>
T Stack<T>::top()
{
    int size = this->list.size();
    return this->list.get(size - 1);
}

template<class T>
bool Stack<T>::empty()
{
    return this->list.empty();
}

template<class T>
int Stack<T>::size()
{
    return this->list.size();
}

template<class T>
void Stack<T>::clear()
{
    this->list.clear();
}

// Using stack library to removeDuplicates
string removeDuplicates(string S)
{
    stack<char> sepS;
    for (int i = 0; i < (int)(S.length()); i++)
    {
        char letter = S[i];
        if (!sepS.empty() && letter == sepS.top())
            sepS.pop();
        else
            sepS.push(letter);
    }
    string reverseString = "";
    while (!sepS.empty())
    {
        reverseString += sepS.top();
        sepS.pop();
    }
    for (int i = 0; i <(int)(reverseString.size()); i++)
        sepS.push(reverseString[i]);
    string res = "";
    while (!sepS.empty())
    {
        res += sepS.top();
        sepS.pop();
    }
    return res;
}

// Using stack library to check ValidParentheses
bool isValidParentheses(string s)
{
    stack<char> str;
    char x;
    for (int i = 0; i < (int)(s.length()); i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            str.push(s[i]);
            continue;
        }
        if (str.empty())
            return false;
        if (s[i] == ')')
        {
            char u = str.top();
            str.pop();
            if (u == '{' || u == '[')
                return false;
        }
        else if (s[i] == '}')
        {
            char u = str.top();
            str.pop();
            if (u == '(' || u == '[')
                return false;
        }
        else if (s[i] == ']')
        {
            char u = str.top();
            str.pop();
            if (u == '(' || u == '{')
                return false;
        }
    }
    return (str.empty());
}

// Using stack library to solve baseballScore
int baseballScore(string ops){
    stack <int> listPoint;
    int sumPoint = 0;
    for (int i = 0; i < (int) ops.size(); i++)
    {
        if (ops[i] >= '0' && ops[i] <= '9')
            listPoint.push(ops[i] - '0');
        else if (ops[i] == 'C')
            listPoint.pop();
        else if (ops[i] == 'D')
            listPoint.push(2 * listPoint.top());
        else if (ops[i] == '+')
        {
            int first = listPoint.top(); 
            listPoint.pop();
            int second = listPoint.top(); 
            int sum = first + second;
            listPoint.push(first);
            listPoint.push(sum);
        }
    }
    while (!listPoint.empty())
    {
        sumPoint += listPoint.top();
        listPoint.pop();
    }
    return sumPoint;
}

// Using stack library to solve trap water
int trap(vector<int>& height) {
    if ((int) height.size() == 0)
        return 0;
    vector <int> tempHeight = height;
    for (int i = 0; i < (int) tempHeight.size() - 1; i++)
    {
        for (int j = i + 1; j < (int) tempHeight.size(); j++)
        {
            if (tempHeight[i] < tempHeight[j])
            {
                int tempVal = tempHeight[j];
                tempHeight[j] = tempHeight[i];
                tempHeight[i] = tempVal;
            }
        }
    }
    stack <int> listHeight;
    for (int i = 0; i < (int) tempHeight.size(); i++)
    {
        if (listHeight.empty() && tempHeight[i] > 0)
            listHeight.push(tempHeight[i]);
        else if (!listHeight.empty() && tempHeight[i] < listHeight.top() && tempHeight[i] != 0)
            listHeight.push(tempHeight[i]);
    }
    if ((int) listHeight.size() == 0)
        return 0;
    int sum = 0, beginCount = -1, k = listHeight.top();
    int sizeInitStack = (int) listHeight.size();
    while (!listHeight.empty())
    {
        beginCount = -1;
        int u = listHeight.top();
        k = ((int) listHeight.size() == sizeInitStack)? k: u - k;
        for (int i = 0; i < (int) height.size(); i++)
        {
            if (height[i] >= u && beginCount == -1)
                beginCount = i;
            else if (height[i] >= u && beginCount != -1)
            {
                sum += (k * (i - beginCount - 1));
                beginCount = i;
            }
        }
        k = u;
        listHeight.pop();
    }
    return sum;
}

template<class T>
class Queue {
protected:
    DLinkedList<T> list;
public:
    Queue() {}
    void push(T item) ;
    T pop() ;
    T top() ;
    bool empty() ;
    int size() ;
    void clear() ;
};

template<class T>
void Queue<T>::push(T item) {
    // TODO: Push new element into the end of the queue
    this->list.add(0, item);
}

template<class T>
T Queue<T>::pop() {
    // TODO: Remove an element in the head of the queue
    return this->list.removeAt(0);    
}

template<class T>
T Queue<T>::top() {
    // TODO: Get value of the element in the head of the queue
    return this->list.get(0);    
}

template<class T>
bool Queue<T>::empty() {
    // TODO: Determine if the queue is empty
    return this->list.empty();     
}

template<class T>
int Queue<T>::size() {
    // TODO: Get the size of the queue
    return this->list.size();    
}

template<class T>
void Queue<T>::clear() {
    // TODO: Clear all elements of the queue
    this->list.clear();
}

bool isBipartite(vector<vector<int>> graph) {
    if ((int)graph.size() == 0) 
        return true;
    int n = graph.size();
    vector <int> colorAssignment(n, 0);
    queue <int> colorVertex;
    for(int i = 0; i < (int) graph.size(); i++)
    {
        if (colorAssignment[i] == 0)
        {
            colorVertex.push(i);
            colorAssignment[i] = 1;
        }
        while (!colorVertex.empty())
        {
            int verTex = colorVertex.front();
            colorVertex.pop();
            for (int i = 0; i < (int) graph[verTex].size(); i++)
            {
                int a = graph[verTex][i];
                if (colorAssignment[a] == 0)
                {
                    colorVertex.push(a);
                    colorAssignment[a] = (colorAssignment[verTex] == 2)? 1: 2;
                }
                else if (colorAssignment[verTex] == colorAssignment[a])
                    return false;
            }
        }
    }
    return true;
}

vector<int> topologicalSorting(vector<vector<int>> graph) {
	vector <int> degPlus ((int) graph.size(), 0);
	for (int i = 0; i < (int) graph.size(); i++)
	{
	    for (int j = 0; j < (int) graph[i].size(); j++)
	        degPlus[graph[i][j]]++;
	}
	
	queue <int> listVertex;
	for (int i = 0; i < (int) graph.size(); i++)
	{
	    if (degPlus[i] == 0)
	        listVertex.push(i);
	}
	vector <int> storeValue;
	int verTexVisited = 0;
	while (!listVertex.empty())
	{
	    int u = listVertex.front();
	    listVertex.pop();
	    storeValue.push_back(u);
	    for (int i = 0; i < (int) graph[u].size(); i++)
	    {
	        if (--degPlus[graph[u][i]] == 0)
	            listVertex.push(graph[u][i]);
	    }
	    verTexVisited++;
	}
	if (verTexVisited != (int) graph.size())
	    return vector<int>{};
    return storeValue;
}

int main()
{
    int n = 6;
    int G[6][6] = { {0, 1, 0, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1},
                    {0, 1, 0, 0, 0, 0} };
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == 1) graph[i].push_back(j);
        }
    }

    vector<int> res = topologicalSorting(graph);
    if (res.empty()) printf("-1");
    else {
        for (int e : res) printf("%d ", e);
    }
}