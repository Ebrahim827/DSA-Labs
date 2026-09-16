#include <iostream>
using namespace std;

void doubleSwap(int **ppa, int **ppb)
{
    int temp = **ppa;
    **ppa = **ppb;
    **ppb = temp;
}

int main()
{
    int a = 10, b = 20000;
    int *pa = &a;
    int *pb = &b;
    int **ppa = &pa;
    int **ppb = &pb;

    cout << "Before swapping: a = " << a << ", b = " << b << endl;
    doubleSwap(ppa, ppb);
    cout << "After swapping: a = " << a << ", b = " << b << endl;

    return 0;
}