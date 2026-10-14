#include <iostream>
using namespace std;

void displayArray(int arr[], int n)
{
    cout << "[";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i];

        if (i < n - 1)
            cout << ", ";
    }

    cout << "]" << endl;
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge both subarrays in ascending order
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right)
{
    // Base case: stop when the subarray has one or zero elements
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

int main()
{
    int n;

    cout << "Enter the number of students: ";
    cin >> n;

    if (cin.fail() || n < 0)
    {
        cout << "Invalid number of students." << endl;
        return 1;
    }

    if (n == 0)
    {
        cout << "Array before sorting: []" << endl;
        cout << "Array after sorting: []" << endl;
        return 0;
    }

    int* marks = new int[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter marks of student " << i + 1 << ": ";
        cin >> marks[i];
    }

    cout << "\nArray before sorting: ";
    displayArray(marks, n);

    mergeSort(marks, 0, n - 1);

    cout << "Array after sorting: ";
    displayArray(marks, n);

    delete[] marks;

    return 0;
}