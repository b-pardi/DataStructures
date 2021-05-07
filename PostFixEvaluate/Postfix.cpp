#include <iostream>
#include <fstream>
using namespace std;

#define EMPTY INT_MIN

struct Node
{
    int value; //nums pushed onto stack
    Node * next;
};

void push(Node * &top_alias, char val)
{
    Node * nn = new Node;
    nn -> value = val;
    nn -> next = top_alias;
    top_alias = nn; //beginning address of stack
}

int pop(Node * &top_alias)
{
    if (top_alias == NULL) return EMPTY;

    Node * temp;
    int tempVal;

    temp = top_alias;
    tempVal = temp -> value;
    top_alias = top_alias -> next;
    delete temp;

    return tempVal;
}

int peek(Node * top)
{
    return top -> value;
}

void evaluate(Node * &top, int left, int right, char operate)
{
    int answer;
    if(operate == '+')
        answer = left + right;
    if(operate == '-')
        answer = left - right;
    if(operate == '*')
        answer = left * right;
    if(operate == '/')
        answer = left / right;
    
    //cout << left << " " << right << " " << operate <<  ": " << answer << endl;
    push(top, answer);
}

ifstream in("input.txt");

int main()
{
    const int SIZE = 50;
    char postExp[SIZE];

    for(int i = 0; in.good(); i++)
        in >> postExp[i];

    in.close();
    
    Node * top = NULL;
    //char postExpTEST[] = {"223*+4+2-6+3-82/-96*2/+"};
    int arrSize = sizeof(postExp)/sizeof(postExp[0]);

    int tempR, tempL;
    for (int i = 0; i < arrSize; i++)
    {
        if(postExp[i] >= '0' && postExp[i] <='9')
        {
            push(top, postExp[i]-48);
            //cout << "num pushed" << endl;
        }
        else if(postExp[i] == '+' || postExp[i] == '-' || postExp[i] == '*' || postExp[i] == '/')
        {
            tempR = pop(top);
            tempL = pop(top);
            evaluate(top, tempL, tempR, postExp[i]);
            //cout << "evaluated" << endl;
        }
        else if(postExp[i] == '\0')
        {
            cout << "***Your Answer***   " << peek(top) << endl;
            break;
        }
    }
}