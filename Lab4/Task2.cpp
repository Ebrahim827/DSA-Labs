#include <iostream>
using namespace std;

struct Node
{
    int id;
    Node* next;
};

Node* createCircle(int n)
{
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 1; i <= n; i++)
    {
        Node* newNode = new Node{i, nullptr};

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    tail->next = head;

    return head;
}

void josephus(Node* head, int n, int k)
{
    Node* current = head;
    Node* previous = head;

    // Find the last node
    while (previous->next != head)
    {
        previous = previous->next;
    }

    cout << "\nEliminated Order: ";

    while (n > 1)
    {
        // Move k-1 times
        for (int i = 1; i < k; i++)
        {
            previous = current;
            current = current->next;
        }

        // Display eliminated person
        cout << current->id << " ";

        // Remove current node
        previous->next = current->next;

        Node* temp = current;
        current = current->next;

        delete temp;

        n--;
    }

    cout << "\nSurvivor: " << current->id << endl;

    delete current;
}

int main()
{
    int n, k;

    cout << "Enter number of people: ";
    cin >> n;

    cout << "Enter step count: ";
    cin >> k;

    if (n <= 0 || k <= 0)
    {
        cout << "Invalid input." << endl;
        return 0;
    }

    Node* head = createCircle(n);

    josephus(head, n, k);

    return 0;
}
