#include <iostream>
using namespace std;
#define SIZE 10

struct Node
{
    int value;
    Node * next;
};

Node * front = NULL;
Node * rear = NULL;

bool isEmpty()
{
    if(front == NULL && rear == NULL)
        return true;
    else
        return false;
}

void Enqueue(Node * &front_alias, Node * &rear_alias, int val)
{
    Node * nn = new Node;
    nn->next = NULL;
    nn->value = val;

    // if front is null, then this will be the first item in queue
    if(front_alias == NULL)
    {
        front_alias = nn;
        rear_alias = nn;
    }
    else // else there are items in the queue already
    {
        rear_alias->next = nn;
        rear_alias = nn;
    }
}

int Dequeue(Node * &front_alias, Node * &rear_alias)
{
    int val;
    Node * newFront;

    // Case where queue is already empty
    if(isEmpty())
        cout << "Queue Empty" << endl;
    
    // Case where queue only has 1 item
    else if(front_alias == rear_alias)
    {
        val = front_alias->value;
        delete front_alias;
        front_alias = NULL;
        rear_alias = NULL;
    }

    // Case where there is more than 1 element in queue
    else
    {
        val = front_alias->value;
        newFront = front_alias;
        front_alias = front_alias->next;
        delete(newFront);
    }

    return val;
}

int Peek(Node * &front_alias)
{
    if(isEmpty())
    {
        cout << "Queue is empty" << endl;
        return -1;
    }

    else
        return front_alias->value;
}

int main()
{
    for(int i = 10; i > 0; i--)
    {
        Enqueue(front, rear, i);
    }
    
    cout << Peek(front) << endl;
    int test = Dequeue(front, rear);
    cout << test << ", " << Peek(front) << endl;
}