
// C program to merge two sorted linked lists
// in-place.
#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int data;
    Node *next;

    Node(int x) : data(x), next(NULL) {};
};

void deleteNode(Node *cur) {
    while (cur != NULL) {
        Node *temp = cur;
        cur = cur->next;
        delete temp;
    }
}

// A utility function to print linked list
void printList(Node *node) {
    while (node != NULL) {
        printf("%d  ", node->data);
        node = node->next;
    }
}

// Merges two given lists in-place. This function
// mainly compares head nodes and calls mergeUtil()


Node *merge(Node *h1, Node *h2) {
    if (!h1)
        return h2;
    if (!h2)
        return h1;

    // start with the linked list
    // whose head data is the least
    if (h1->data < h2->data) {
        h1->next = merge(h1->next, h2);
        return h1;
    } else if (h1->data > h2->data) {
        h2->next = merge(h1, h2->next);
        return h2;
    } else {
        Node *temp = h2;
        h2 = h2->next;
        delete temp;
        h2 = merge(h1, h2);
        return h2;
    }
}


// Driver program
int main() {
    Node *head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(7);

    // 1->3->5 LinkedList created

    Node *head2 = new Node(3);
    head2->next = new Node(4);
    head2->next->next = new Node(5);
    head2->next->next->next = new Node(6);
    // 0->2->4 LinkedList created

    Node *mergedhead = merge(head1, head2);
    printList(mergedhead);
    deleteNode(head1);
    deleteNode(head2);
    deleteNode(mergedhead);


    return 0;
}