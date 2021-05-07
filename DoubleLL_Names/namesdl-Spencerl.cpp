#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define SIZE 1000

struct Node
{
    string name; //names pushed onto stack
    Node *next;
    Node *prev;
};

ifstream in("longlistnames.txt");
ofstream out("output.txt");

Node *traverse(Node *head)
{
    Node *curNode = head;
    while (curNode->next)
        curNode = curNode->next;

    return curNode;
}

Node *search(Node *head, string key)
{
    Node *curNode = head;
    Node *temp = NULL;

    while (curNode)
    {
        if (curNode->name == key)
		{
            temp = curNode;
			break; // SBC this way you exit when you find your key
		}

        curNode = curNode->next;
    }

    return temp;
}

bool nodeExist(Node *head, string key)
{
    Node *temp = search(head, key);
    if (!temp)
        return false;
    else
        return true;
}

// CASE 1: Insert at head
void insertFront(Node *&head_alias, string newName)
{
    Node *nn = new Node;
    if (nodeExist(head_alias, newName))
        cout << "Node Already Exists, this node will not be added" << endl;

    else
    {
        nn->name = newName;
        nn->next = NULL;
        nn->prev = NULL;

        // case 1.1 list empty (head is null)
        if (head_alias == NULL)
            head_alias = nn;

        else // case 1.2 list NOT empty
        {
            nn->next = head_alias;
            head_alias->prev = nn;
            head_alias = nn;
        }
    }
}

// CASE 2: Insert at some location inbetween head and tail
void insert(Node *&head_alias, string newName, string keyName)
{
    Node *nn = new Node;
    Node *curNode = search(head_alias, keyName);
	// SBC - check to make sure curNode isn't null - you'll blow chunks
    
	Node *sucNode = curNode->next;

    if (nodeExist(head_alias, newName))
    {
        cout << "Node Already Exists, this node will not be added" << endl;
    }

    else if (!nodeExist(head_alias, keyName))
    {
        cout << "Key Node does not exist" << endl;
    }

    else
    {
        nn->name = newName;
        nn->next = NULL;
        nn->prev = NULL;

        // case 2.1 list empty (head is null)
        if (head_alias == NULL)
            head_alias = nn;

        // case 2.2 list NOT empty AND inserted at the end
        else if (curNode->next == NULL)
        {
            curNode->next = nn;
            nn->prev = curNode;
            curNode = nn;
        }

        // case 2.3 list NOT empty AND inserted at after key node, BUT before tail node
        else
        {
            nn->next = sucNode;
            nn->prev = curNode;
            curNode->next = nn;
            sucNode->prev = nn;
        }
    }
}

void insertEnd(Node *&head_alias, string newName)
{
    Node *nn = new Node;
    Node *curNode;
    if (nodeExist(head_alias, newName))
        cout << "Node Already Exists, this node will not be added" << endl;

    else
    {
        nn->name = newName;
        nn->next = NULL;
        nn->prev = NULL;

        // case 3.1 list empty (head is null)
        if (head_alias == NULL)
            head_alias = nn;

        else // case 3.2 list NOT empty
        {
            curNode = traverse(head_alias);

            curNode->next = nn;
            nn->prev = curNode;
        }
    }
}

void sortedInsert(Node *&head_alias, string newName)
{
    Node * nn = new Node;
    Node * curNode;
    // list empty case
    if (head_alias == NULL)
    {
        nn->name = newName;
        nn->next = NULL;
        nn->prev = NULL;

        head_alias = nn;
    }

    else
    {
        curNode = head_alias;
        bool inserted = false;
        int i = 0;

        // traverse nodes
        while (curNode != NULL)
        {
			 // SBC - consider converting each name to uppercase before compare.  This is good with users input where Tom is too tired to his the shift key.
			 // The alternative is compareignorecase and that will work fine on something small like this
			 // now that's if case isn't important.  If it is imporant, leave it as is.  A != a  Passwords are an example of that.
			 // Passwords are hashed and stored encrypted.  So I type "Password" for my password, the code hashes it, fetches the stored values and cmpares the two hashed values.  IOW, the password is never unhashed.  Never in clear text.
            cout << "Comparing Strings " << curNode -> name << " and " << newName << endl; 
			if (curNode -> name.compare(newName) > 0)
            {
				cout << "Result was 1.  so " << curNode -> name << " is greater" << endl;
                // insert to replace head
                if (curNode -> prev == NULL)
				{
					cout << "curnode -> Prev is null so we're replacing head " << endl;
                    insertFront(head_alias, newName);
				}
                    
                else // inserting nn before curnode
                {
					cout << "inserting before cur node " << endl;
                    nn->name = newName;

                    nn->next = curNode;
                    nn->prev = curNode->prev;

                    curNode->prev->next = nn;
                    curNode->prev = nn;
                }
                inserted = true;
                break;
            }
            else if (nodeExist(head_alias, newName))
            {
                inserted = true;
                break;
            }

            if (curNode -> next)
                curNode = curNode->next;

            else if (curNode -> next == NULL)
                break;
        }
        
        if (!inserted)
        {
			cout << "Not here - crank to the next node " << endl;
            nn->name = newName;
            curNode->next = nn;
            nn->prev = curNode;
            nn->next = NULL;
        }
    }
}

// CASE 3: Insert at tail

void deleteNode(Node *&head_alias, string keyName)
{
    Node *curNode = search(head_alias, keyName);
    Node *tail = traverse(head_alias);
    Node *tempDel = curNode;

    if (!nodeExist(head_alias, keyName))
        cout << "That node does not exist" << endl;

    else
    {
        if (curNode->prev)                       // mid or tail node
            curNode->prev->next = curNode->next; // in either case, connect predeccor node to successor node

        else // head node
        {
            curNode->next->prev = curNode->prev; // point mid node's prev to head node's prev (which is null)
            head_alias = curNode->next;          // set the head node to be successor node (mid node)
        }

        if (curNode->next)                       // mid or head node
            curNode->next->prev = curNode->prev; // in either case, connect successor node to predecessor node

        else // tail node
        {
            curNode->prev->next = curNode->next; // point mid node's next to tail node's next (which is null)
            tail = curNode->prev;
        }
    }
    delete tempDel;
}

void printList(Node *head_alias)
{

    Node *cur = head_alias;

    cout << "[ ";

    while (cur != NULL)
    {

        cout << cur->name << " ";
        cur = cur->next;
    }

    cout << "]" << endl;
}

int main()
{
    string nameArr[SIZE];
    for (int i = 0; in.good(); i++)
    {
        in >> nameArr[i];
    }

    Node *head = NULL;
    Node *tail;
    Node *cur;

    for (int i = 0; nameArr[i] != ""; i++)
    {
        if (nameArr[i] == "delete")
        {
            cout << "delete detected: " << nameArr[i + 1] << endl;
            deleteNode(head, nameArr[i + 1]);
            i+=1;
        }
        else
        {
            cout << "inserting " << nameArr[i] << endl;

            sortedInsert(head, nameArr[i]);

            printList(head);
        }
    }

    Node *tempCur = head;
    for (int i = 0; tempCur != NULL; i++)
    {
        cout << tempCur->name << endl;
        out << tempCur->name << endl;
        tempCur = tempCur->next;
    }

    // some test code

    in.close();
    out.close();
}