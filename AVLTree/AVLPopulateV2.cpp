#include <iostream>
#include <fstream>
#define SIZE 100
using namespace std;

struct AVLnode
{
    int val;
    int height;
    AVLnode * left;
    AVLnode * right;
};

struct Qnode
{
    AVLnode * nodeVal;
    Qnode * next;
};

Qnode * front = NULL;
Qnode * rear = NULL;

Qnode * frontCur = NULL;
Qnode * rearCur = NULL;
Qnode * frontNext = NULL;
Qnode * rearNext = NULL;

bool QisEmpty()
{
    if (front == NULL && rear == NULL)
        return true;

    else
        return false;
}

void Enqueue(Qnode * &front_alias, Qnode * &rear_alias, AVLnode * nodeValue)
{
    Qnode * nn = new Qnode;
    nn->next = NULL;
    nn->nodeVal = nodeValue;

    if (front_alias == NULL)
    {
        front_alias = nn;
        rear_alias = nn;
    }
    else
    {
        rear_alias->next = nn;
        rear_alias = nn;
    }
}

AVLnode * Dequeue(Qnode * &front_alias, Qnode * &rear_alias)
{
    AVLnode * nodeValue;
    Qnode * newFront;

    if ((front_alias == NULL) && (rear_alias == NULL))
        cout << "Queue Empty\n";

    else if (front_alias == rear_alias)
    {
        nodeValue = front_alias->nodeVal;
        delete front_alias;
        front_alias = NULL;
        rear_alias = NULL;
    }

    else
    {
        nodeValue = front_alias->nodeVal;
        newFront = front_alias;
        front_alias = front_alias->next;
        delete newFront;
    }

    return nodeValue;
}

AVLnode * makeNode(AVLnode * &newLeaf, int &value)
{
    newLeaf = new AVLnode;
    newLeaf->height = 0;
    newLeaf->val = value;
    newLeaf->left = NULL;
    newLeaf->right = NULL;

    return newLeaf;
}

int max(int left, int right)
{
    if (left > right)
        return left;

    else
        return right;
}

int updateHeight(AVLnode * &node)
{
    if (node == NULL)
    {
        return -1;
    }

    int leftHeight = updateHeight(node->left);
    int rightHeight = updateHeight(node->right);
    cout << "(LH, RH) " << leftHeight << ", " << rightHeight << endl;

    node->height = max(leftHeight, rightHeight) + 1;
    cout << "Node's Height: " << node->height << endl;

    return (max(leftHeight, rightHeight) + 1);
}

int getHeight(AVLnode * &node)
{
    if (node == NULL)
    {
        return -1;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    //cout << "(LH, RH) " << leftHeight << ", " << rightHeight << endl;
    return (max(leftHeight, rightHeight) + 1);
}

int getBalance(AVLnode * &node)
{
    int leftHeight;
    int rightHeight;
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        leftHeight = getHeight(node->left);
        rightHeight = getHeight(node->right);
        int bf = (leftHeight - rightHeight);
        //cout << "LH, RH, BF: " << leftHeight << ", " << rightHeight << ", " << bf << endl;
        return bf;
    }
}

AVLnode * rotateLeft(AVLnode * &x)
{
    // Connecting nodes before rotation
    AVLnode * y = x->right;
    AVLnode * z = y->left;
    cout << "before left rot: y->" << x->right->val << ", y val " << y->val << endl;
    cout << "and x, y heights: " << x->height << ", " << y->height << endl;
    cout << "y->right: " << y->right->val << endl;

    // Rotating by changing pointers
    x->right = z;
    y->left = x;

    updateHeight(x);
    updateHeight(y);
    cout << "after left rot: x val" << x->val << ", z->" << y->left->val << endl;
    cout << "and x, y heights: " << x->height << ", " << y->height << endl;
    cout << "y->right: " << y->right->val << endl;

    return y;
}

AVLnode * rotateRight(AVLnode * &x)
{
    // Connecting nodes before rotation
    AVLnode * y = x->left;
    AVLnode * z = y->right;
    cout << "before right rot: y->" << x->left->val << ", y val " << y->val << endl;
    cout << "and x, y heights: " << x->height << ", " << y->height << endl;
    cout << "y->left: " << y->left->val << endl;

    // Rotating by changing pointers
    x->left = z;
    y->right = x;
    updateHeight(x);
    updateHeight(y);
    cout << "after left rot: x val" << x->val << ", z->" << y->right->val << endl;
    cout << "and x, y heights: " << x->height << ", " << y->height << endl;
    cout << "y->left: " << y->left->val << endl;

    return y;
}

AVLnode * rebalance(AVLnode * &node)
{
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalance(node);

    /** Cases for Rotation
     * 
     *         /           /          \            \
     *   LO:  /      LI:  /      RO:   \      RI:   \
     *       /            \             \           /
     * 
     **/

    // Left heavy...
    if (balance == 2)
    {
        int leftBalance = getBalance(node->left);

        if (leftBalance > 0) // Outside case
        {
            return rotateRight(node);
        }
        else if (leftBalance < 0) // Inside case
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    // Right heavy...
    else if (balance == -2)
    {  
        int rightBalance = getBalance(node->right);

        if (rightBalance < 0) // Outside case
        {
            return rotateLeft(node);
        }
        else if (rightBalance > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    // No rotation
    return node;
}

AVLnode * insert(AVLnode * &root, int value)
{
    if (root == NULL) // BASE CASE
    {
        return (makeNode(root, value));
        //cout << "value inserted: " << value << endl;
    }

    if (value < root->val)
    {
        cout << "moving left to... ";
        root->left = insert(root->left, value);
        cout << root->left->val << endl;
    }
    else if (value > root->val)
    {
        cout << "moving right to... ";
        root->right = insert(root->right, value);
        cout << root->right->val << endl;
    }
    else if (value == root->val)
    {
        cout << "Duplicate Value\n";
    }

    cout << "rebalancing...\n";
    root = rebalance(root);
    return root;
}

void printIO(AVLnode * root)
{
    if (root != NULL)
    {
        printIO(root->left);
        cout << root->height << ", " << root->val << "; ";
        printIO(root->right);
    }
}

void printPO(AVLnode * root)
{
    if (root != NULL)
    {
        cout << root->height << ", " << root->val << "; ";
        printIO(root->left);
        printIO(root->right);
    }
}

AVLnode * const delimeter = NULL;
void printTree2(AVLnode * root)
{
    if (root == NULL)
        return;

    Enqueue(front, rear, root);
    Enqueue(front, rear, delimeter);
    
    while (!QisEmpty())
    {
        AVLnode * cur = Dequeue(front, rear);

        if (cur != delimeter)
        {
            cout << "(Height, Value): (" << cur->height << ", " << cur->val << "); ";
        
            if (cur->left != NULL)
                Enqueue(front, rear, cur->left);

            if (cur->right != NULL)
                Enqueue(front, rear, cur->right);
        }
        else
        {
            cout << cur->val << endl;
            Enqueue(front, rear, delimeter);
        }
    }
}

std::ifstream in("input.txt");
std::ofstream out("output.txt");

void printTree(AVLnode * root)
{
    if (root == NULL)
        return;

    Enqueue(front, rear, root);
    int prevHeight = root->height;

    while (!QisEmpty())
    {
        AVLnode * cur = Dequeue(front, rear);

        if (prevHeight != cur->height)
        {
            cout << endl;
            out << endl;
        }
        cout << " (Height, BF, Val): (" << cur->height << ", " << getBalance(cur) << ", " << cur->val << "); ";
        out << " (Height, BF, Val): (" << cur->height << ", " << getBalance(cur) << ", " << cur->val << "); ";
        prevHeight = cur->height;

        if (cur->left != NULL)
            Enqueue(front, rear, cur->left);

        if (cur->right != NULL)
            Enqueue(front, rear, cur->right);
    }
}

void printTree3(AVLnode * root)
{
    if (root == NULL)
        return;

    Enqueue(frontCur, rearCur, root);
    
    while (frontCur != NULL)
    {
        AVLnode * cur = Dequeue(frontCur, rearCur);
        cout << " (Height, BF, Val): (" << cur->height << ", " << getBalance(cur) << ", " << cur->val << "); ";
        if (cur->left != NULL)
            Enqueue(frontNext, rearNext, cur->left);

        if(cur->right !=NULL)
            Enqueue(frontNext, rearNext, cur->right);

        if (frontCur == NULL && frontNext != NULL)
        {
            Enqueue(frontCur, rearCur, Dequeue(frontNext, rearNext));
            cout << endl;
        }
    }
}

int main()
{
    int nums2[SIZE];
    int arrSize = 0;
    // accepts integers separated by comma
    for(int i = 0; in.good(); i++)
    {
        if (in.peek() == ',')
            in.ignore();
        in >> nums2[i];
        arrSize++;
    }

    in.close();

    AVLnode * root = NULL;
    //int nums[10] = {5,8,3,9,34,3,2,1,0,7};

    for (int i = 0; i < arrSize; i++)
    {
        cout << "inserting num: " << nums2[i] << endl;
        root = insert(root, nums2[i]);
        cout << "num inserted! \n";
    }

    cout << "***Tree Printed In Order***\n";
    printIO(root);
    cout << "\n***Tree Printed Pre Order***\n";
    printPO(root);
    cout << "\n***Tree Printed Level Order***\n";
    printTree(root);
}