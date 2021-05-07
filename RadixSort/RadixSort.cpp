#include <iostream>
#include <time.h>

using namespace std;
#define SIZE 100

struct Node
{
    int value;
    Node * next;
};

struct Queue
{
    Node * front;
    Node * rear;
};

Queue Q[10];

bool isEmpty(Queue &Q)
{
    if(Q.front == NULL && Q.rear == NULL)
        return true;
    else
        return false;
}

void Enqueue(Queue &Q, int val)
{
    Node * nn = new Node;
    nn->next = NULL;
    nn->value = val;

    // if front is null, then this will be the first item in queue
    if(Q.front == NULL)
    {
        Q.front = nn;
        Q.rear = nn;
    }

    // else there are items in the queue already
    // only rear needs to be adjusted because of the nature of a queue
    else
    {
        Q.rear->next = nn;
        Q.rear = nn;
    }

}

int Dequeue(Queue &Q)
{
    int val;
    Node * tempFront;

    // Case where queue is already empty
    if(isEmpty(Q))
    {
        cout << "Queue empty" << endl;
        val = -1;
    }

    // Case where queue only has 1 item
    // Delete item after getting its value and set front/rear to Null (now empty again)
    else if(Q.front == Q.rear)
    {
        val = Q.front->value;
        delete Q.front;
        Q.front = NULL;
        Q.rear = NULL;
    }

    // Case where there is more than 1 element in queue
    // Retrieve value, adjust 'next' pointer, delete front
    else
    {
        val = Q.front->value;
        tempFront = Q.front;
        Q.front = Q.front->next;
        delete(tempFront);
    }

    return val;
}

int PeekQ(Queue &Q)
{
    if(!isEmpty(Q))
        return Q.front->value;

    else
    {
        cout << "Queue Empty" << endl;
        return -1;
    }
}

int LengthQ(Queue &Q)
{
    Node * curQ = Q.front;
    int countQ;
    if(isEmpty(Q))
        countQ = 0;

    else
        countQ = 1;
        while(curQ->next != NULL)
        {
            curQ = curQ->next;
            countQ++;
        }

    return countQ;
}

int RadixLen(int val)
{
    if(val == 0)
        return 1;

    int digits = 0;
    while(val != 0)
    {
        digits += 1;
        val = val / 10;
    }

    return digits;
}

int RadixMaxLen(int numArr[], int arrSize)
{
    int maxDigits = 0;
    int digitCount;
    for(int i = 0; i < arrSize; i++)
    {
        digitCount = RadixLen(numArr[i]);
        if(digitCount > maxDigits)
            maxDigits = digitCount;
    }

    return maxDigits;
}

void RadixSort(int numArr[], int arrSize)
{
    int maxDigits = RadixMaxLen(numArr, arrSize);
    int power = 1;
    int bucketIndex, arrIndex, deq;

    for(int digitIndex = 0; digitIndex < maxDigits; digitIndex++)//test num arr with something like 1000 to determine if < or <=
    {
        for(int i = 0; i < arrSize; i++)
        {
            bucketIndex = (numArr[i] / power) % 10;
            Enqueue(Q[bucketIndex], numArr[i]);
            //cout << "Loop " << digitIndex << ", " << i <<  " has bucket index: " << bucketIndex << " with: " << numArr[i] << endl;
        }

        arrIndex = 0;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; !isEmpty(Q[i]); j++)
            {
                deq = Dequeue(Q[i]);
                numArr[arrIndex++] = deq;
            }
        }

        power = power * 10;
        /*
        cout << "*****AFTER PASS " << digitIndex+1 << ": " << endl;
        for(int i = 0; i < SIZE; i++)
            cout << numArr[i] << endl;
        cout << "------------------------" << endl;
        */
    }
}

bool verifySorted(int numArr[], int arrSize)
{
    int unsortedCount = 0;
    for(int i = 0; i < SIZE-1; i++)
    {
        if(numArr[i] >= numArr[i+1])
        {
            cout << "Indexes: " << i << ", " << i+1 << "Out of order" << endl;
            unsortedCount++;
        }
    }

    if(unsortedCount = 0)
        return true;

    else
        return false;

}

int main()
{
    //int nums[SIZE] = {508,80,9,3,77,10241,21,69,4,1000};

    int nums[SIZE];
    srand (time(0));
    cout << "***Randomized Numbers***" << endl;
    for(int i = 0; i < SIZE; i++)
    {
        nums[i] = rand() % 1000;
        cout << nums[i] << endl;
    }

    RadixSort(nums, SIZE);
    if(verifySorted)
    {
        cout << endl << "***Nums Sorted In ASCENDING Order***" << endl;
        for(int i = 0; i < SIZE; i++)
            cout << nums[i] << endl;

        cout << endl << "***Nums Sorted In DESCENDING Order***" << endl;
        for(int i = SIZE-1; i >= 0; i--)
            cout << nums[i] << endl;
    }
    
    else
        cout << "Nums aren't sorted!" << endl;
}