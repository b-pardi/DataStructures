#include <iostream>
#include <fstream>
using namespace std;
#define SIZE 20

struct Node
{
    int value;
    Node * next;
};

Node * frontCur = NULL;
Node * rearCur = NULL;
Node * frontNext = NULL;
Node * rearNext = NULL;


bool isEmpty(Node * &front_alias, Node * &rear_alias)
{
    if(front_alias == NULL && rear_alias == NULL)
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
    if(isEmpty(front_alias, rear_alias))
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

void printLOnoQ(int HS, int (&heapArr)[SIZE*2])
{
    int pow = 0;
    int nlVal = 1;

    for (int i = 0; i < HS; i++)
    {
        if (i == nlVal)
        {
            cout << endl;
            pow ++;
            nlVal += (1 << pow);
        }
        cout << heapArr[i] << ", ";
    }
    cout << endl;
}

void SU(int nodeIndex, int (&heapArr)[SIZE*2])
{
    int parentIndex;
    int tempVal;

    while (nodeIndex > 0)
    {
        parentIndex = (nodeIndex - 1) / 2;

        if (heapArr[nodeIndex] >= heapArr[parentIndex])
            return;

        else
        {
            tempVal = heapArr[nodeIndex];
            heapArr[nodeIndex] = heapArr[parentIndex];
            heapArr[parentIndex] = tempVal;
            nodeIndex = parentIndex;
        }
    }
}

void SD(int nodeIndex, int arrSize, int (&heapArr)[SIZE*2])
{
    int Lchild = 2 * nodeIndex + 1;
    int Rchild = 2 * nodeIndex + 2;
    int parent = 0;
    if (nodeIndex != 0)
        parent = (nodeIndex - 1) / 2;
        
    int minChild = 0;
    int tempVal;
    cout << "(index, Lc, Rc, par) = (" << nodeIndex << ", " << heapArr[Lchild] << ", " << heapArr[Rchild] << ", " << heapArr[parent] << ")\n";

    if (Lchild <= arrSize)
    {
        if (Lchild == arrSize || heapArr[Lchild] < heapArr[Rchild])
        {
            minChild = Lchild;
            cout << "left child min index: " << minChild << endl;
        }
        else
        {
            minChild = Rchild;
            cout << "right child min index: " << minChild << endl;
        }
    }

    if (heapArr[parent] > heapArr[minChild])
    {
        tempVal = heapArr[parent];
        heapArr[parent] = heapArr[minChild];
        heapArr[minChild] = tempVal;
        printLOnoQ(arrSize, heapArr);
        SD(minChild, arrSize, heapArr);
    }
}

void Insert(int val, int nodeIndex, int (&heapArr)[SIZE*2])
{
    heapArr[nodeIndex] = val;
    SU(nodeIndex, heapArr);
}

void Remove(int nodeIndex, int &arrSize, int (&heapArr)[SIZE*2])
{
    cout << "Removing: " << heapArr[0] << "... and replacing with: " << heapArr[arrSize-1] << endl;
    heapArr[0] = heapArr[arrSize-1];
    arrSize--;
    SD(0, arrSize, heapArr);
    cout << "Removed! New top item: " << heapArr[0] << " with " << arrSize << " nums" << endl;
}

void printIO(int size, int (&heapArr)[SIZE*2])
{
    for (int i = 0; i < size; i++)
        cout << "index: " << i << ", element: " << heapArr[i] << endl;
}

void printLO(int size, int (&heapArr)[SIZE*2])
{
    int curVal;
    int i = 0;
    int limit1;
    int limit2;
    int level = 0;

    cout << size << " nums\nLevel " << level << ": ";
    Enqueue(frontCur, rearCur, heapArr[i]);

    while (frontCur != NULL)
    {
        curVal = Dequeue(frontCur, rearCur);
        cout << curVal << ", ";

        if (limit1 < size-1)
        {
            Enqueue(frontNext, rearNext, heapArr[(2 * i) + 1]);
            limit1 = (2 * i) + 1;
            //cout << "Queueing left child " <<  heapArr[2*i +1] << ", at index " << 2*i+1 << ", ";
        }
        if (limit2 < size-2)
        {
            Enqueue(frontNext, rearNext, heapArr[(2 * i) + 2]);
            limit2 = (2 * i) + 2;
            //cout << "Queueing right child " <<  heapArr[2*i +2] << ", at index " << limit2 << ", ";
        }
        i++;

        if (frontCur == NULL)
        {
            frontCur = frontNext;
            rearCur = rearNext;
            frontNext = NULL;
            rearNext = NULL;
            level++;

            if (frontCur != NULL)
                cout << endl << "Level " << level << ": ";
            else
                cout << endl;
        }
    }
}

std::ifstream in("input.txt");

int main()
{
    int numArr[SIZE];
    int heapArr[SIZE*2];
    int numOfnums = 0;

    for(int i = 0; in.good(); i++)
    {
        if (in.peek() == ',')
            in.ignore();
        in >> numArr[i];
        numOfnums++;
    }

    in.close();

    // inserting items
    for (int i = 0; i < numOfnums; i++)
    {
        cout << "inserting num: " << numArr[i] << endl;
        Insert(numArr[i], i, heapArr);
        cout << "num inserted! \n";
    }

    cout << "***Printing items IN Order***" << endl;
    printIO(numOfnums, heapArr);
    cout << endl << "***Printing items LEVEL Order***" << endl;
    printLOnoQ(numOfnums, heapArr);
    cout << endl;

    // removing items
    for (int i = 0; i < 5; i++)
    {
        Remove(0, numOfnums, heapArr);
        printLOnoQ(numOfnums, heapArr);
    }
}