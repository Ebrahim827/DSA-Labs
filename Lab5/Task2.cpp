#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int jobID;
    string documentName;
    int pages;
    Node* next;
};

class Queue
{
private:
    Node* front;
    Node* rear;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    // Check if queue is empty
    bool isEmpty()
    {
        return front == nullptr;
    }

    // Add a new job at the rear
    void addJob(int id, string name, int pages)
    {
        Node* newNode = new Node();

        newNode->jobID = id;
        newNode->documentName = name;
        newNode->pages = pages;
        newNode->next = nullptr;

        // If queue is empty
        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        cout << "Job added successfully.\n";
    }

    // Process and remove the job at the front
    void processJob()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No job to process.\n";
            return;
        }

        Node* temp = front;

        cout << "Processing Job ID: " << temp->jobID << endl;
        cout << "Document: " << temp->documentName << endl;
        cout << "Pages: " << temp->pages << endl;

        front = front->next;

        // If last job was removed
        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
    }

    // Display the next job without removing it
    void viewNextJob()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No next job.\n";
            return;
        }

        cout << "Next Job:\n";
        cout << "Job ID: " << front->jobID << endl;
        cout << "Document: " << front->documentName << endl;
        cout << "Pages: " << front->pages << endl;
    }

    // Display all jobs
    void displayQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty.\n";
            return;
        }

        Node* temp = front;

        cout << "\nWaiting Jobs:\n";

        while (temp != nullptr)
        {
            cout << "Job ID: " << temp->jobID
                 << " | Document: " << temp->documentName
                 << " | Pages: " << temp->pages << endl;

            temp = temp->next;
        }
    }

    // Count number of jobs
    int countJobs()
    {
        int count = 0;
        Node* temp = front;

        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }

        return count;
    }

    // Remove all jobs
    void clearQueue()
    {
        while (!isEmpty())
        {
            Node* temp = front;

            front = front->next;

            delete temp;
        }

        rear = nullptr;

        cout << "Queue cleared.\n";
    }

    ~Queue()
    {
        clearQueue();
    }
};

int main()
{
    Queue printerQueue;

    // Add jobs given in the lab
    printerQueue.addJob(101, "Assignment1.pdf", 10);
    printerQueue.addJob(102, "Report.docx", 25);
    printerQueue.addJob(103, "Notes.pdf", 5);
    printerQueue.addJob(104, "LabTask.docx", 15);

    // 1. Display all jobs
    printerQueue.displayQueue();

    // 2. Process two jobs
    cout << "\n--- Processing Two Jobs ---\n";
    printerQueue.processJob();
    printerQueue.processJob();

    // 3. Display remaining jobs
    cout << "\n--- Remaining Jobs ---\n";
    printerQueue.displayQueue();

    // 4. Add a new job
    cout << "\n--- Adding New Job ---\n";
    printerQueue.addJob(105, "Final.pdf", 20);

    // 5. Display the next job
    cout << "\n--- Next Job ---\n";
    printerQueue.viewNextJob();

    // Display count
    cout << "\nNumber of waiting jobs: "
         << printerQueue.countJobs() << endl;

    // 6. Process all remaining jobs
    cout << "\n--- Processing Remaining Jobs ---\n";

    while (!printerQueue.isEmpty())
    {
        printerQueue.processJob();
    }

    // 7. Attempt to process from empty queue
    cout << "\n--- Processing Empty Queue ---\n";
    printerQueue.processJob();

    return 0;
}