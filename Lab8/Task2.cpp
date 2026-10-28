
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }
};

Node* mergeKLists(vector<Node*>& lists) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (Node* head : lists) {
        if (head != nullptr)
            minHeap.push(head);
    }

    Node dummy(0);
    Node* tail = &dummy;

    while (!minHeap.empty()) {
        Node* smallest = minHeap.top();
        minHeap.pop();

        Node* nextNode = smallest->next;

        tail->next = smallest;
        tail = smallest;

        if (nextNode != nullptr)
            minHeap.push(nextNode);
    }

    tail->next = nullptr;
    return dummy.next;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data;
        if (head->next != nullptr)
            cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int k;
    cout << "Enter number of linked lists: ";
    cin >> k;

    if (k <= 0) {
        cout << "Invalid number of lists.\n";
        return 0;
    }

    vector<Node*> lists(k, nullptr);

    for (int i = 0; i < k; i++) {
        int n;
        cout << "Enter number of elements in list "
             << i + 1 << ": ";
        cin >> n;

        if (n < 0) {
            cout << "Invalid list size.\n";
            deleteList(mergeKLists(lists));
            return 0;
        }

        Node* tail = nullptr;

        cout << "Enter sorted elements: ";

        for (int j = 0; j < n; j++) {
            int value;
            cin >> value;

            Node* newNode = new Node(value);

            if (lists[i] == nullptr)
                lists[i] = newNode;
            else
                tail->next = newNode;

            tail = newNode;
        }
    }

    Node* merged = mergeKLists(lists);

    cout << "\nMerged Sorted List:\n";
    printList(merged);

    deleteList(merged);
    return 0;
}
