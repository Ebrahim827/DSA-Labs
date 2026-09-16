#include <iostream>
using namespace std;

int main()
{
    int rows, cols;

    // Reads and validates ALL rows and cols with the help of do-while loops unless user enters 0 or negative numbers
    do {
        cout << "Enter number of students (rows): ";
        cin >> rows;
        if (rows <= 0)
            cout << "Invalid! Please enter positive number."<<endl;
    } while (rows <= 0);

    do {
        cout << "Enter number of subjects (columns): ";
        cin >> cols;
        if (cols <= 0)
            cout << "Invalid! Please enter positive number."<<endl;
    } while (cols <= 0);

    // Allocated array of row pointers, then allocated each row.Another pointer points to old pointer.
    int **marks = new int*[rows];
    for (int r = 0; r < rows; r++){
        marks[r] = new int[cols];
    }

    // Reads marks using *(*(marks + r) + c). This is equivalent to the value at an array marks[r][c] but uses pointers.
    cout << "Enter marks (0-100) for each subject: "<<endl;
    for (int r = 0; r < rows; r++)
    {
        cout << "Student " << (r + 1) << ":\n";
        for (int c = 0; c < cols; c++)
        {
            cout << "  Subject " << (c + 1) << ": ";
            cin >> *(*(marks + r) + c);
        }
    }

    // Displays the matrix
    cout << "Marks Matrix:"<<endl;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
            cout << *(*(marks + r) + c) << "    ";
        cout << endl;
    }

    // Calculate totals, find highest (first student wins ties)
    int maxMarks = 0, topper = 1;

    for (int r = 0; r < rows; r++)
    {
        int total = 0;
        for (int c = 0; c < cols; c++)
            total += marks[r][c];

        cout << "Student " << (r + 1) << " total = " << total << endl;

        if (r == 0) {
            maxMarks = total;
            topper = 1;
        }
        // Check if current student has higher total than maxMarks. Accordingly it replaces maxMarks and topper based on row number for student. 
        // If equal, first student wins.
        else if (total > maxMarks) {
            maxMarks = total;
            topper = r + 1;
        }
    }

    cout << "\nTop student: Student " << topper << " with total = " << maxMarks << endl;

    // Deallocating now: rows first, then row-pointer array
    //I set it to nullptr to avoid dangling pointer after deallocation.
    for (int r = 0; r < rows; r++)
        delete[] marks[r];
    delete[] marks;
    marks = nullptr;

    return 0;
}