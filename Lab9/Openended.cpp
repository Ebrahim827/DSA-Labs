#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    Student* next;
};

struct Request {
    int rollNo;
    Request* next;
};

Student* head = NULL;
Student* tail = NULL;

Request* front = NULL;
Request* rear = NULL;

void addStudent() {
    int roll;
    string studentName;

    cout << "Enter Roll Number: ";
    cin >> roll;

    Student* temp = head;

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            cout << "Student already exists!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Enter Student Name: ";
    cin >> studentName;

    Student* newNode = new Student;

    newNode->rollNo = roll;
    newNode->name = studentName;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    cout << "Student added successfully!\n";
}

void searchStudent() {
    int roll;

    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    Student* temp = head;

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            cout << "Student Found!\n";
            cout << "Roll Number: " << temp->rollNo << endl;
            cout << "Name: " << temp->name << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Student not found!\n";
}

void displayStudents() {
    if (head == NULL) {
        cout << "No student records available!\n";
        return;
    }

    Student* temp = head;

    cout << "\nStudent Records:\n";

    while (temp != NULL) {
        cout << "Roll Number: " << temp->rollNo
             << " | Name: " << temp->name << endl;

        temp = temp->next;
    }
}

void enqueueRequest() {
    int roll;

    cout << "Enter Student Roll Number: ";
    cin >> roll;

    Student* temp = head;

    while (temp != NULL && temp->rollNo != roll) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Student does not exist!\n";
        return;
    }

    Request* newNode = new Request;

    newNode->rollNo = roll;
    newNode->next = NULL;

    if (front == NULL) {
        front = newNode;
        rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }

    cout << "Help request added successfully!\n";
}

void dequeueRequest() {
    if (front == NULL) {
        cout << "No pending help requests!\n";
        return;
    }

    Request* temp = front;

    cout << "Serving request for Roll Number: "
         << temp->rollNo << endl;

    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    delete temp;
}

void displayRequests() {
    if (front == NULL) {
        cout << "No pending requests!\n";
        return;
    }

    Request* temp = front;

    cout << "\nPending Help Requests:\n";

    while (temp != NULL) {
        cout << "Roll Number: " << temp->rollNo << endl;
        temp = temp->next;
    }
}

void clearStudents() {
    Student* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }

    tail = NULL;
}

void clearRequests() {
    Request* temp;

    while (front != NULL) {
        temp = front;
        front = front->next;
        delete temp;
    }

    rear = NULL;
}

int main() {
    int choice;

    do {
        cout << "\n===== STUDENT HELP DESK =====\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Add Help Request\n";
        cout << "5. Serve Help Request\n";
        cout << "6. Display Pending Requests\n";
        cout << "7. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                searchStudent();
                break;

            case 3:
                displayStudents();
                break;

            case 4:
                enqueueRequest();
                break;

            case 5:
                dequeueRequest();
                break;

            case 6:
                displayRequests();
                break;

            case 7:
                clearStudents();
                clearRequests();
                cout << "Exiting Student Help Desk...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}