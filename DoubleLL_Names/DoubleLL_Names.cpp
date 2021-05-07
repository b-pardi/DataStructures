#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define SIZE 5000

struct Node
{
    string name; //names pushed onto stack
    Node * next;
    Node * prev;
};

ifstream in("longlistnames.txt");
ofstream out("output.txt");

Node * traverse(Node * head)
{
    Node * curNode = head;
    while(curNode -> next)
        curNode = curNode -> next;

    return curNode;
}

Node * search(Node * head, string key)
{
    Node * curNode = head;
    Node * temp = NULL;
    
    while(curNode)
    {
        if(curNode -> name == key)
            temp = curNode;

        curNode = curNode -> next;
    }

    return temp;
}

bool nodeExist(Node * head, string key)
{
    Node * temp = search(head, key);
    if(!temp)
        return false;
    else
        return true;
}

// CASE 1: Insert at head
void insertFront(Node * &head_alias, string newName)
{
    Node * nn = new Node;
    if(nodeExist(head_alias, newName))
        cout << "Node Already Exists, this node will not be added" << endl;

    else
    {
        nn -> name = newName;
        nn -> next = NULL;
        nn -> prev = NULL;

        // case 1.1 list empty (head is null)
        if(head_alias == NULL)
            head_alias = nn;

        else // case 1.2 list NOT empty
        {
            nn -> next = head_alias;
            head_alias -> prev = nn;
            head_alias = nn;
        }
    }
}

// CASE 2: Insert at some location inbetween head and tail
void insert(Node * &head_alias, string newName, string keyName)
{
    Node * nn = new Node;
    Node * curNode = search(head_alias, keyName);
    Node * sucNode = curNode -> next;
    if(nodeExist(head_alias, newName))
        cout << "Node Already Exists, this node will not be added" << endl;
    
    else if (!nodeExist(head_alias, keyName))
        cout << "Key Node does not exist" << endl;
    
    else
    {
        nn -> name = newName;
        nn -> next = NULL;
        nn -> prev = NULL;

        // case 2.1 list empty (head is null)
        if(head_alias == NULL)
            head_alias = nn;

        // case 2.2 list NOT empty AND inserted at the end
        else if (curNode -> next == NULL)
        {
            curNode -> next = nn;
            nn -> prev = curNode;
            curNode = nn;
        }

        // case 2.3 list NOT empty AND inserted at after key node, BUT before tail node
        else
        {
            nn -> next = sucNode;
            nn -> prev = curNode;
            curNode -> next = nn;
            sucNode -> prev = nn;
        }
    }
}

// CASE 3: Insert at tail
void insertEnd(Node * &head_alias, string newName)
{
    Node * nn = new Node;
    Node * curNode;
    if(nodeExist(head_alias, newName))
        cout << "Node Already Exists, this node will not be added" << endl;

    else
    {
        nn -> name = newName;
        nn -> next = NULL;
        nn -> prev = NULL;

        // case 3.1 list empty (head is null)
        if(head_alias == NULL)
            head_alias = nn;

        else // case 3.2 list NOT empty
        {
            curNode = traverse(head_alias);
            
            curNode -> next = nn;
            nn -> prev = curNode;
        }
    }
}

void insertSorted(Node * &head_alias, string newName)
{
    
}

void deleteNode(Node * &head_alias, string keyName)
{
    Node * curNode = search(head_alias, keyName);
    Node * tail = traverse(head_alias);
    Node * tempDel = curNode;
    if(!nodeExist(head_alias, keyName))
        cout << "That node does not exist" << endl;
    
    else
    {
        if(curNode -> prev) // mid or tail node
            curNode -> prev -> next = curNode -> next; // in either case, connect predeccor node to successor node

        else // head node
        {
            curNode -> next -> prev = curNode -> prev; // point mid node's prev to head node's prev (which is null)
            head_alias = curNode -> next; // set the head node to be successor node (mid node)
        }

        if(curNode -> next) // mid or head node
            curNode -> next -> prev = curNode -> prev; // in either case, connect successor node to predecessor node

        else // tail node
        {
            curNode -> prev -> next = curNode -> next; // point mid node's next to tail node's next (which is null)
            tail = curNode -> prev;
        }
    }
    delete tempDel;
}

int main()
{
    string nameArr [SIZE];
    for(int i = 0; in.good(); i++)
    {
        in >> nameArr[i];
    }

    Node * head = NULL;
    Node * tail;
    Node * cur;

    for (int i = 0; nameArr[i] != ""; i++)
    {
        if(nameArr[i] == "delete")
        {
            cout << "delete detected: " << nameArr[i+1] << endl;
            deleteNode(head, nameArr[i+1]);
        }
        else
        {
            if(head!=NULL)
                tail = traverse(head);

            // list empty case
            if(head == NULL)
                insertFront(head, nameArr[i]);

            // new name is smaller than head node's name
            else if(nameArr[i].compare(head -> name) < 0)
                insertFront(head, nameArr[i]);

            // new name is larger than tail node's name
            else if(nameArr[i].compare(tail -> name) > 0)
                insertEnd(head, nameArr[i]);

            else // somewhere inbetween
            {
                cur = head;
                while(nameArr[i].compare(cur -> name) < 0)
                    cur = cur -> next;

                insert(head, nameArr[i], cur -> name);
            }
        }
    }

    Node * tempCur = head;
    for(int i = 0; tempCur != NULL; i++)
    {
        cout << tempCur -> name << endl;
        out << tempCur -> name << endl;
        tempCur = tempCur -> next;
    }

    // some test code
    Node * testnode = search(head, "Brandon");
    Node * testnode2 = traverse(head);
    insert(head, "Zulu", "Zachary");
    Node * testnode3 = traverse(head);
    deleteNode(head, "Zulu");
    Node * testnode4 = traverse(head);
    cout << testnode -> name << ", " << testnode2 -> name << ", " << testnode3 ->name;


    in.close();
    out.close();
}