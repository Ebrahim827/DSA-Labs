#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = nullptr;
void insertAtHead(int value){
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void insertAtThird(int value)
{
    if (head == nullptr || head->next == nullptr)
    {
        cout << "Not enough nodes to insert at the 3rd position." << endl;
        return;
    }

    Node* newNode = new Node;
    newNode->data = value;

    Node* temp = head;

    // Moves to the second node
    temp = temp->next;

    // Insert the new node after the second node
    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteLastNode()
{
    //CASE 1: If the list is empty
    if(head == nullptr)
    {
        cout << "List is empty. No node to delete." << endl;
        return;
    }
    //CASE 2: If the list has only one node

    if(head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    //CASE 3: If the list has more than one node
    Node* temp = head;
    while(temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

void countNodes(){
    int count = 0;
    Node* temp = head;

    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    cout << "Number of nodes in the linked list: " << count << endl;
}

void reverseList()
{
    //we reverse pointers of the linked list which reverses direction 
    Node* prev = nullptr;
    Node* current = head;

    while (current != nullptr)
    {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}

void searchValue(int value)
{
    Node* temp = head;

    while (temp != nullptr)
    {
        if (temp->data == value)
        {
            cout << "Value found." << endl;
            return;
        }

        temp = temp->next;
    }
    cout << "Value not found." << endl;
}
void displayList()
{
    Node* temp = head;
    cout << "Linked List: "<<endl;
    cout<<" "<<endl;

    while (temp != nullptr)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;
}
int main()
{
    int choice;
    int value;

    do
    {
        cout << "\n--- Linked List Menu ---" << endl;
        cout << "1. Insert at Head" << endl;
        cout << "2. Insert at Third Position" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Delete Last" << endl;
        cout << "5. Count Nodes" << endl;
        cout << "6. Reverse List" << endl;
        cout << "7. Search Value" << endl;
        cout << "8. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                insertAtHead(value);
                break;

            case 2:
                cout << "Enter value: ";
                cin >> value;
                insertAtThird(value);
                break;

            case 3:
                displayList();
                break;

            case 4:
                deleteLastNode();
                break;

            case 5:
                countNodes();
                break;

            case 6:
                reverseList();
                cout << "List reversed." << endl;
                break;

            case 7:
                cout << "Enter value to search: ";
                cin >> value;
                searchValue(value);
                break;

            case 8:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 8);

    return 0;
}