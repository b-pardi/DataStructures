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

char evaluate(char left, char right, char operate)
{
    int eval;
    //left -=48;
    //right -=48;
    if(operate == '+')
        eval = left + right;
    if(operate == '-')
        eval = left - right;
    if(operate == '*')
        eval = left * right;
    if(operate == '/')
        eval = left / right;

    return eval;
}

std::ifstream in("input.txt");

int main()
{
    const int SIZE = 20;
    char numStack[SIZE];

    while(in.good())
        {
            for(int i = 0; i < SIZE; i++)
                in >> numStack[i];
        }
    in.close();

    Node * top = NULL;
    char tempL, tempR, sign, eval;
    //int eval;
    for (int i = 0; i < SIZE; i++)
    {
        if (numStack[i] >= '0' && numStack[i] <= '9')
        {
            push(top, numStack[i]);
            cout << "num pushed" << endl;
        }
        else if (numStack[i] == '+' || numStack[i] == '-' || numStack[i] == '*' || numStack[i] == '-')
        {
            //sign = numStack[i];
            tempR = pop(top);
            tempL = pop(top);
            cout << "stuff popped" << endl;
            eval = evaluate(tempL, tempR, sign);
            push(top, eval);
            cout << "stuff evaluated" << endl;
            cout << tempR << tempL << sign << eval << endl;
        }
        else
            break;    
    }
    cout << "Answer: " << int(pop(top)) << endl;
}