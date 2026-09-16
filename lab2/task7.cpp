#include <iostream>
using namespace std;

int main()
{
    int n;
    // Reads and validate n (1-10)
    do {
        cout << "Enter number of students (1-10): ";
        cin >> n;
        if (n < 1 || n > 10)
            cout << "Invalid! n must be between 1 and 10.\n";
    } while (n < 1 || n > 10);

    // Allocate original block of n marks
    int *marks = new int[n];

    cout << "Enter " << n << " marks:\n";
    for (int i = 0; i < n; i++)
        cin >> *(marks + i);

    // allocate new block of n+1, copy old values, add new mark
    int *newMarks = new int[n + 1];

    for (int i = 0; i < n; i++)
        *(newMarks + i) = *(marks + i);   // copy using pointer method

    cout << "Enter new student's mark: ";
    cin >> *(newMarks + n);   

    //release and delete old block and then repointing it to new block
    delete[] marks;
    marks = newMarks;
    n = n + 1;

    cout << "\nUpdated marks (" << n << " values): ";
    for (int i = 0; i < n; i++)
        cout << *(marks + i) << " ";
    cout << endl;

    //releasing the final block once
    delete[] marks;
    marks = nullptr;

    return 0;
}