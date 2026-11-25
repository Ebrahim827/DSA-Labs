#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long comparisons = 0;
bool showTrace = false;
int traceSize = 0;

// Prints the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Lomuto partition using last element as pivot
int partition(int arr[], int low, int high) {

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        comparisons++;

        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    int pi = i + 1;

    // Display partition details
    if (showTrace) {
        cout << "Pivot: " << pivot
             << ", pi: " << pi
             << ", Array: ";

        printArray(arr, traceSize);
    }

    return pi;
}

// Recursive Quick Sort
void quickSort(int arr[], int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Runs test cases with partition tracing
void runTraceTest(vector<int> arr, string name) {

    cout << "\n" << name << endl;

    comparisons = 0;
    showTrace = true;
    traceSize = arr.size();

    if (!arr.empty())
        quickSort(arr.data(), 0, traceSize - 1);

    cout << "Sorted Array: ";
    printArray(arr.data(), traceSize);
}

// Runs tests and counts comparisons
void runCountTest(vector<int> arr, string name) {

    comparisons = 0;
    showTrace = false;

    int n = arr.size();

    if (n > 1)
        quickSort(arr.data(), 0, n - 1);

    cout << name
         << " | Comparisons: " << comparisons
         << " | Sorted: ";

    printArray(arr.data(), n);
}

int main() {

    // Required tracing tests
    runTraceTest({2, 1, 5, 4, 6, 3}, "Trace Test 1");

    runTraceTest({35, 12, 43, 8, 51, 27, 19},
                 "Trace Test 2");

    // Comparison counting tests
    cout << "\nComparison Count Tests" << endl;

    runCountTest({5, 1, 4, 2, 8}, "Random Order");

    runCountTest({1, 2, 4, 5, 8}, "Already Sorted");

    runCountTest({8, 5, 4, 2, 1}, "Reverse Sorted");

    runCountTest({7, 7, 7, 7, 7}, "Repeated Values");

    runCountTest({10}, "Single Element");

    runCountTest({}, "Empty Array");

    return 0;
}
