#include <iostream>
using namespace std;

class Heap {
private:
    int* arr;
    int size;
    int capacity;
    bool isMax;

    // Restores heap property by moving an element upward.
    // Time Complexity: O(log n)
    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            bool shouldSwap = isMax
                ? arr[index] > arr[parent]
                : arr[index] < arr[parent];

            if (!shouldSwap)
                break;

            swap(arr[index], arr[parent]);
            index = parent;
        }
    }

    // Restores heap property by moving an element downward.
    // Time Complexity: O(log n)
    void siftDown(int index) {
        while (true) {
            int best = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size) {
                bool condition = isMax
                    ? arr[left] > arr[best]
                    : arr[left] < arr[best];

                if (condition)
                    best = left;
            }

            if (right < size) {
                bool condition = isMax
                    ? arr[right] > arr[best]
                    : arr[right] < arr[best];

                if (condition)
                    best = right;
            }

            if (best == index)
                break;

            swap(arr[index], arr[best]);
            index = best;
        }
    }

    // Doubles the array capacity when full.
    // Time Complexity: O(n)
    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];

        for (int i = 0; i < size; i++)
            newArr[i] = arr[i];

        delete[] arr;
        arr = newArr;
    }

public:

    // Initializes either a max heap or a min heap.
    // Time Complexity: O(1)
    Heap(bool maxHeap, int cap = 5) {
        size = 0;
        capacity = cap;
        isMax = maxHeap;
        arr = new int[capacity];
    }

    // Releases dynamically allocated memory.
    // Time Complexity: O(1)
    ~Heap() {
        delete[] arr;
    }

    // Returns the number of elements in the heap.
    // Time Complexity: O(1)
    int getSize() {
        return size;
    }

    // Checks whether the heap is empty.
    // Time Complexity: O(1)
    bool isEmpty() {
        return size == 0;
    }
     // Returns the root element without removing it.
    // Time Complexity: O(1)
    int peek() {
        return arr[0];
    }

    // Inserts an element and restores the heap property.
    // Time Complexity: O(log n), amortized with resizing.
    void push(int value) {
        if (size == capacity)
            resize();

        arr[size] = value;
        siftUp(size);
        size++;
    }
    // Removes and returns the root element.
    // Time Complexity: O(log n)
    int pop() {
        if (isEmpty())
            return -1;

        int root = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size > 0)
            siftDown(0);

        return root;
    }
};

class MedianMonitor {
private:
    Heap maxHeap;
    Heap minHeap;

public:

    // Initializes the smaller-half max heap and larger-half min heap.
    // Time Complexity: O(1)
    MedianMonitor() : maxHeap(true), minHeap(false) {
    }

    // Inserts a waiting time into the correct heap and rebalances them.
    // Time Complexity: O(log n)
    void addWait(int x) {

        if (maxHeap.isEmpty() || x <= maxHeap.peek())
            maxHeap.push(x);
        else
            minHeap.push(x);

        // Max heap can contain at most one extra element.
        if (maxHeap.getSize() > minHeap.getSize() + 1) {
            minHeap.push(maxHeap.pop());
        }
        else if (minHeap.getSize() > maxHeap.getSize()) {
            maxHeap.push(minHeap.pop());
        }
    }

    // Calculates the median using the roots of both heaps.
    // Time Complexity: O(1)
    double getMedian() {

        if (maxHeap.getSize() > minHeap.getSize())
            return maxHeap.peek();

        return (maxHeap.peek() + minHeap.peek()) / 2.0;
    }

    // Displays both heap roots, median and alert status.
    // Time Complexity: O(1)
    void display(int arrival, int wait) {

        cout << arrival << "\t"
             << wait << "\t"
             << maxHeap.peek() << "\t\t";

        if (minHeap.isEmpty())
            cout << "none\t\t";
        else
            cout << minHeap.peek() << "\t\t";

        double median = getMedian();

        cout << median << "\t\t";

        if (median > 35)
            cout << "ALERT: call extra staff";
        else
            cout << "Normal";

        cout << endl;
    }
};

int main() {

    MedianMonitor hospital;

    int waits[] = {45, 20, 60, 15, 30, 90, 10, 55};
    int n = sizeof(waits) / sizeof(waits[0]);

    cout << "Arrival\tWait\tMax Heap Root\tMin Heap Root\tMedian\t\tStatus" << endl;

    for (int i = 0; i < n; i++) {

        hospital.addWait(waits[i]);

        hospital.display(i + 1, waits[i]);
    }

    return 0;
}
