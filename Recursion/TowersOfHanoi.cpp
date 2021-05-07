#include <iostream>
#include <time.h>

using namespace std;



void tower (int discs, char src, char dest, char aux)
{
    if (discs == 1)
    {
        cout << "move plate: " << src << " to: " << dest << endl;
    }

    else
    {
        tower(discs-1, src, aux, dest);
        cout << "move plate from: " << src << " to: " << dest << endl;
        tower(discs-1, aux, dest, src);
    }
}

int main()
{
    char a = 'a';
    char b = 'b';
    char c = 'c';
    int discs = 6;

    // Runtime O(2^n)
    tower(discs, c, a, b);
}