#include <iostream>
#include <time.h>
using namespace std;
#define SIZE1 15
#define SIZE2 200

struct Node
{
    int value;
    Node * next;
};

Node *traverse(Node *head)
{
    Node *curNode = head;
    while (curNode->next)
        curNode = curNode->next;

    return curNode;
}

Node *findMid(Node *head)
{
    Node *endSeeker = head->next;
    Node *midNode = head;
    int nodeCount = 1;

    while (endSeeker)
    {
        endSeeker = endSeeker->next;
        nodeCount++;
        if((nodeCount-1) % 2 == 0)
            midNode = midNode->next;
    }
    /*
    for(int i = 0; i <= nodeCount/2; i++)
        midNode = midNode->next;
    */

    return midNode;
}

void append(Node *&head_alias, int val)
{
    Node *nn = new Node;
    nn->next = NULL;
    nn->value = val;

    if(head_alias == NULL)
    {
        head_alias = nn;
    }
    else
    {
        Node *endNode = traverse(head_alias);
        endNode->next = nn;
    }
}

void prepend(Node *&head_alias, int val)
{
    Node *nn = new Node;
    nn->next = NULL;
    nn->value = val;

    if(head_alias == NULL)
    {
        head_alias = nn;
    }
    else
    {
        nn->next = head_alias;
        head_alias = nn;
    }
}

void printList(Node *head)
{
    if(head == NULL)
        cout << "List Empty, try adding stuff maybe" << endl;

    for(int i = 0; head != NULL; i++)
    {
        cout << head->value << endl;
        head = head->next;
    }
}

void partition(Node *head, Node *&a, Node *&b)
{
    Node * midNode = findMid(head);
    a = head;
    b = midNode->next;

    // Separates the 2 lists by breaking the next connection
    midNode->next = NULL;
}

Node * merge(Node *a, Node *b)
{
    Node *merged = NULL;

    // Compares value of each node and copies it into the merged list in order
    while((a != NULL) && (b != NULL))
    {
        if(a->value <= b->value)
        {
            //cout << "a, b: " << a->value << ", " << b->value << endl;
            append(merged, a->value);
            a = a->next;
        }
        else
        {
            //cout << "b, a: " << a->value << ", " << b->value << endl;
            append(merged, b->value);
            b = b->next;
        }
    }

    // If elements remaining in a, copies them to merged sequentially
    // As any remaining elements will be sorted from previous merge call
    while(a != NULL)
    {
        append(merged, a->value);
        a = a->next;
    }

    // Remaining elements in b copied as well
    // Can be avoided by copying all elements to merged in beginning and updated. This just makes more sense to me
    while(b != NULL)
    {
        append(merged, b->value);
        b = b->next;
    }

    return merged;
}

Node *mergeSort(Node *head)
{
    Node *a = NULL;
    Node *b = NULL;
    Node *c = head;

    // LIST EMPTY
    if(head == NULL)
    {
        cout << "Head Null" << endl;
        return NULL;
    }

    // Base case where list is fully separated to 1 element
    if(head->next == NULL)
    {
        //cout << "Head->next Null" << endl;
        return head;
    }

    partition(head, a, b);
    /*
    cout << "*Partitioned*\n\nLeft List:" << endl;
    printList(a);
    cout << "Right List:" << endl;
    printList(b);
    */

    a = mergeSort(a);
    b = mergeSort(b);
    c = merge(a,b);
    //cout << "*merged*\nList:\n" << endl;
    //printList(c);

    return c;
}

int main()
{
    Node *head = NULL;
    int nums1[SIZE1] = {9,6,895,2,5,14,63,8,5,4,658,56,98,24,74};

    srand (time(0));
    for(int i = 0; i < SIZE2; i++)
    {
        append(head, rand() % 1000);
    }

    cout << "**UNsorted**" << endl;
    Node *tempCur1 = head;
    printList(tempCur1);

    Node * sortedList = mergeSort(head);
    cout << "**SORTED**" << endl;
    printList(sortedList);
}