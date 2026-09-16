#include <iostream>
using namespace std;

int main()
{
    int list[5] = {3, 6, 9, 12, 15};
    int *pArr = list;

    for (int i = 0; i < 5; i++)
    {
        cout << *pArr << " ";   // I dereferenced pointer to print current value each time
        pArr++;                 // moves pointer to next int
    }
    cout << endl;

    return 0;
}