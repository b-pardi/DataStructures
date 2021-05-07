#include <iostream>
#include <time.h>

using namespace std;
#define SIZE 50

struct TreeNode
{
    int key;
    TreeNode * left;
    TreeNode * right;
};

TreeNode * newNode(int key)
{
    TreeNode * node = new TreeNode;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void addNode(TreeNode * &leaf, int key)
{
    leaf = new TreeNode;
    leaf->key = key;
    leaf->left = NULL;
    leaf->right = NULL;
}

void insert(TreeNode * &root, int key)
{
    bool done = false;
    TreeNode * leaf = root;
    
    if(!root)
        addNode(root, key);

    else
    {
        while (!done)
        {
            if (key == leaf->key)
                done = true;
            
            else if (key < leaf->key)
            {
                if (leaf->left != NULL)
                    leaf = leaf->left;
                else
                {
                    addNode(leaf->left, key);
                    done = true;
                }
            }

            else if (key > leaf->key)
            {
                if (leaf->right != NULL)
                    leaf = leaf->right;
                else
                {
                    addNode(leaf->right, key);
                    done = true;
                }
            }
        }
    }     
}

TreeNode * search(TreeNode * leaf, int key)
{
    TreeNode * found = NULL;
    cout << "Entering while...\n";
    while(!leaf)
    {
        cout << "Entered while\n";
        if (key == leaf->key)
            found = leaf;

        else if (key < leaf->key)
        {
            cout << "moving left...\n";
            leaf = leaf->left;
            cout << "moved left\n";
        }

        else if (key > leaf->key)
        {
            cout << "moving right...\n";
            leaf = leaf->right;
            cout << "moved right\n";
        }
    }

    return found;
}

bool doesNodeExist(TreeNode * root, int key)
{
    if (search(root, key) != NULL)
        return true;

    else
        return false;
}

void printIO(TreeNode * root)
{
    if (root != NULL)
    {
        printIO(root->left);
        cout << root->key << ", ";
        printIO(root->right);
    }
}

int main()
{
    TreeNode * root;
    int tempnum;

    srand (time(0));
    cout << "LIST of random nums: \n";
    for (int i = 0; i < SIZE; i++)
    {
        tempnum = rand() % 1000;
        if (i == 5)
            tempnum = 2;
        insert(root, tempnum);
        cout << tempnum << ", ";
    }

    cout << "\nTREE printed: \n";
    printIO(root);

    cout << "beginning search\n";
    TreeNode * foundNode = search(root, 2);
    bool nodeExist = doesNodeExist(root, 2);
    if (doesNodeExist)
        cout << endl << foundNode->key << endl;
    else
        cout << endl << "Node DNE.\n";
}