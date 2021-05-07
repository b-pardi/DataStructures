#include <iostream>
#include <fstream>
#include <time.h>
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

// Function prints the heap array using math instead of a Queue to determine new lines
void printLOnoQ(int HS, int (&heapArr)[SIZE*2])
{
    int pow = 0;
    int nlVal = 1;
    cout << "Level " << pow << ": ";
    for (int i = 0; i < HS; i++)
    {
        if (i == nlVal)
        {
            pow ++;
            cout << endl << "Level " << pow << ": ";
            nlVal += (1 << pow);
        }
        cout << heapArr[i] << ", ";
    }
    cout << endl;
}

/**
 * Sift Up is called by Insert()
 * Function compares the indexed node to its parent and swaps as needed
 * swap occurs iff parent node is greater than the indexed node
 * Maintaining the order property of Min-heap when new values are inserted
 */
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

/**
 * Sift Down is called by Remove()
 * First, compares the indexed node's children to find which is smaller
 * Then, the node swaps with minChild iff the child node is lesser
 * This maintains the order property of a Min-heap such that each parent node is less than its child
 */
void SD(int nodeIndex, int arrSize, int (&heapArr)[SIZE*2])
{
    int Lchild = 2 * nodeIndex + 1;
    int Rchild = Lchild + 1;
    int minChild = nodeIndex;
    int tempVal;
    if (Lchild <= arrSize)
    {
        if(Lchild == arrSize)
        {
            minChild = Lchild;
            //cout << "left child min index: " << minChild << endl;
        }
        else
        {
            Rchild = Lchild + 1;
            if (heapArr[Lchild] < heapArr[Rchild])
            {
                minChild = Lchild;
                //cout << "left child min index: " << minChild << endl;
            }
            else
            {
                minChild = Rchild;
                //cout << "right child min index: " << minChild << endl;
            }
        }
    }
    /*
    int parent = 0;
    if (nodeIndex != 0)
    {
        parent = (nodeIndex - 1) / 2;
    }*/
    //cout << "(index, Lc, Rc, par) = (" << nodeIndex << ", " << heapArr[Lchild] << ", " << heapArr[Rchild] << ", " << heapArr[parent] << ")\n";

    if (heapArr[nodeIndex] > heapArr[minChild])
    {
        tempVal = heapArr[nodeIndex];
        heapArr[nodeIndex] = heapArr[minChild];
        heapArr[minChild] = tempVal;
        SD(minChild, arrSize, heapArr);
    }
}

/**
 * Inserts new items into the Min-heap
 * Items always appended to the end of the heap
 * After appending, SU() is called to percolate the item up to maintain order property
 */
void Insert(int val, int nodeIndex, int (&heapArr)[SIZE*2])
{
    heapArr[nodeIndex] = val;
    SU(nodeIndex, heapArr);
}

/**
 * Removes Items from Min-heap and calls SD() to maintain heap order property
 * Indicative of a Min-heap, removes ALWAYS occur at the root node
 * This is because Min-heaps only care about what node is next
 * This allows us to maintain a priority queue (where lower nums have higher prority) without having to fully sort a list
 */
void Remove(int nodeIndex, int &arrSize, int (&heapArr)[SIZE*2])
{
    cout << "Removing: " << heapArr[0] << "... and replacing with: " << heapArr[arrSize-1] << endl;
    heapArr[0] = heapArr[arrSize-1];
    arrSize--;
    SD(0, arrSize, heapArr);
    cout << "Removed! New top item: " << heapArr[0] << " with " << arrSize << " nums" << endl;
}

// Prints Min-heap in indexed order
void printIO(int size, int (&heapArr)[SIZE*2])
{
    for (int i = 0; i < size; i++)
        cout << "index: " << i << ", element: " << heapArr[i] << endl;
}

// Prints Level Order Using a Cur and Next Queue, if I could've gotten it to work
// (See printLOnoQ for working alternative)
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

void generateRandomNums(int &numOfnums, int (&randNumArr)[SIZE])
{
    int tempnum;
    srand (time(0));
    for (int i = 0; i < SIZE; i++)
    {
        tempnum = rand() % 100;
        randNumArr[i] = tempnum;
        numOfnums++;
    }
}

void generateNumsFromFile(int &numOfnums, int (&numArr)[SIZE])
{
    for(int i = 0; in.good(); i++)
    {
        if (in.peek() == ',')
            in.ignore();
        in >> numArr[i];
        numOfnums++;
    }
    cout << numOfnums << " nums!!!\n";
    in.close();
}

int main()
{
    int numArr[SIZE];
    int randNumArr[SIZE];
    int heapArr[SIZE*2];
    int numOfnums = 0;

    /**
     * generateRandomNums() generates numbers randomly to insert into the Min-heap
     *      numbers vary between 0 and 100 and the list will be of length SIZE
     * generateNumsFromFile() grabs the numbers from the file 'input.txt'
     *      supports num lists separated by commas and integers of any size
     * Make sure to use one or the other and see comment above the for loop for more details
     */

    generateRandomNums(numOfnums, randNumArr);
    //generateNumsFromFile(numOfnums, numArr);

    // inserting items
    // Change numArr to randNumArr for random numbers
    for (int i = 0; i < numOfnums; i++)
    {
        cout << "inserting num: " << randNumArr[i] << endl;
        Insert(randNumArr[i], i, heapArr);
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