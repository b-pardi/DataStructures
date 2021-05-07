#include <iostream>
#include <fstream>
using namespace std;

struct Node
{
    char op; //operator or operand
    Node * next;
};

void push(Node * &top_alias, char op)
{
    Node * nn = new Node;
    nn -> op = op;
    nn -> next = top_alias;
    top_alias = nn; //beginning address of stack
}

char pop(Node * &top)
{
    Node * temp;
    char tempVal;
    if(top) //if top exists, stack not empty
    {
        temp = top;
        tempVal = temp -> op;
        top = top -> next;
        delete temp;
    }
    return top -> op;
}

char peek(Node * top)
{
    return top -> op;
}

int main()
{
    Node * top = NULL;
    char postExp[] = {"12+"};
    int arrSize = sizeof(postExp)/sizeof(postExp[0]);
    for (int i = 0; i < arrSize; i++)
    {
        cout << postExp[i] << endl;
        push(top, postExp[i]);
        cout << peek(top) << endl;
    }
    char c1, c2;
    c1 = pop(top);
    pop(top);
    c2 = pop(top);
    cout << "c's: "<< c1 << c2 << endl;

}