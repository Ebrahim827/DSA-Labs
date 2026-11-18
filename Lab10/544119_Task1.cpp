#include <iostream>
#include <utility>
using namespace std;

class MaxHeap {
private:
    int* heap;
    int size;
    int capacity;

    // Restores max heap property by moving an element downward.
    // Time Complexity: O(log n)
    void siftDown(int index, int heapSize) {
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < heapSize && heap[left] > heap[largest])
                largest = left;

            if (right < heapSize && heap[right] > heap[largest])
                largest = right;

            if (largest == index)
                break;

            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

    // Doubles array capacity when it becomes full.
    // Time Complexity: O(n)
    void resize() {
        capacity *= 2;
        int* newHeap = new int[capacity];

        for (int i = 0; i < size; i++)
            newHeap[i] = heap[i];

        delete[] heap;
        heap = newHeap;
    }

public:
    // Initializes an empty heap.
    // Time Complexity: O(1)
    MaxHeap(int cap = 5) {
        size = 0;
        capacity = cap;
        heap = new int[capacity];
    }

    // Releases dynamically allocated memory.
    // Time Complexity: O(1)
    ~MaxHeap() {
        delete[] heap;
    }

    // Inserts a value and moves it upward to restore heap property.
    // Time Complexity: O(log n), amortized O(log n) with resizing.
    int insert(int value) {
        if (size == capacity)
            resize();

        int index = size;
        heap[size++] = value;
        int swaps = 0;

        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[index] <= heap[parent])
                break;

            swap(heap[index], heap[parent]);
            index = parent;
            swaps++;
        }

        return swaps;
    }

    // Displays the current heap array.
    // Time Complexity: O(n)
    void display() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";

        cout << endl;
    }

    // Sorts the heap in ascending order using heap sort.
    // Time Complexity: O(n log n)
    void heapSort() {
        for (int i = size - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            siftDown(0, i);
        }
    }

    // Displays the sorted array.
    // Time Complexity: O(n)
    void displaySorted() {
        display();
    }
};

int main() {
    MaxHeap h;

    int values[] = {25, 40, 15, 60, 35, 10, 70, 50};
    int n = sizeof(values) / sizeof(values[0]);

    cout << "Insert\tSwaps\tHeap after insertion" << endl;

    for (int i = 0; i < n; i++) {
        int swaps = h.insert(values[i]);

        cout << values[i] << "\t"
             << swaps << "\t";

        h.display();
    }

    cout << "\nFinal Max Heap: ";
    h.display();

    h.heapSort();

    cout << "Sorted output: ";
    h.displaySorted();

    return 0;
}

/*     COMMENTS:

Q1. What is the worst-case number of swaps for one insertion
    into a heap of n elements?

    Answer: O(log n), because an inserted element can move
    from the last level to the root, crossing at most
    O(log n) levels.

Q2. What is the time complexity of building the heap by
    n insertions, and of heap sort?

    Answer:
    Building through n individual insertions: O(n log n).
    Heap sort: O(n log n).
*/
