#include <iostream>
#include <vector>
using namespace std;

// Controls whether merge operations are displayed
bool showTrace = false;

// Prints the complete array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
void merge(int arr[], int low, int mid, int high) {

    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    // Copy elements into temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    // Merge using two pointers
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    // Display merge operation
    if (showTrace) {
        cout << "Merged [" << low << ".." << high << "]: ";
        printArray(arr, 7);
    }

    delete[] L;
    delete[] R;
}

// Recursive Merge Sort
void mergeSort(int arr[], int low, int high) {

    if (low >= high)
        return;

    int mid = low + (high - low) / 2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}

// Runs and displays a test case
void runTest(vector<int> arr, string name, bool trace = false) {

    cout << "\n" << name << endl;

    int n = arr.size();
    showTrace = trace;

    if (n == 0) {
        mergeSort(nullptr, 0, -1);
    }
    else {
        mergeSort(arr.data(), 0, n - 1);
    }

    cout << "Sorted Array: ";
    printArray(arr.data(), n);
}

int main() {

    // Main test with merge tracing
    vector<int> arr = {35, 12, 43, 8, 51, 27, 19};

    runTest(arr, "Main Test", true);

    // Boundary test cases
    runTest({1, 2, 4, 5, 8}, "Already Sorted");
    runTest({8, 5, 4, 2, 1}, "Reverse Sorted");
    runTest({5, 2, 5, 1, 2}, "Repeated Values");
    runTest({10}, "Single Element");
    runTest({}, "Empty Array");

    return 0;
}
