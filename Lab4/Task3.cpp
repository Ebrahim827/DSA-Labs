#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int bit;
    Node* next;
    Node* prev;
};

Node* head = nullptr;
Node* tail = nullptr;


// Insert bit at end
void insertBit(Node*& head, Node*& tail, int bit)
{
    Node* newNode = new Node{bit, nullptr, nullptr};

    if (head == nullptr)
        head = tail = newNode;
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}


// Delete complete DLL
void deleteList(Node*& head, Node*& tail)
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
}


// Store binary number in 8-bit groups
void storeBinary(string binary)
{
    deleteList(head, tail);

    int remainder = binary.length() % 8;

    if (remainder != 0)
    {
        int zeros = 8 - remainder;

        while (zeros--)
            insertBit(head, tail, 0);
    }

    for (char c : binary)
    {
        if (c == '0' || c == '1')
            insertBit(head, tail, c - '0');
    }
}


// Display binary number in 8-bit groups
void displayBinary(Node* head)
{
    if (head == nullptr)
    {
        cout << "No binary number stored.\n";
        return;
    }

    Node* temp = head;
    int count = 0;

    while (temp != nullptr)
    {
        cout << temp->bit;
        count++;

        if (count % 8 == 0 && temp->next != nullptr)
            cout << " ";

        temp = temp->next;
    }

    cout << endl;
}


// 1's Complement
void onesComplement()
{
    Node* temp = head;

    while (temp != nullptr)
    {
        temp->bit = 1 - temp->bit;
        temp = temp->next;
    }
}


// Add 1 to binary number
void addOne()
{
    Node* temp = tail;
    int carry = 1;

    while (temp != nullptr && carry)
    {
        if (temp->bit == 0)
        {
            temp->bit = 1;
            carry = 0;
        }
        else
        {
            temp->bit = 0;
        }

        temp = temp->prev;
    }

    if (carry)
        insertBit(head, tail, 1);
}


// 2's Complement
void twosComplement()
{
    onesComplement();
    addOne();
}


// Create a separate DLL
void createList(string binary, Node*& newHead, Node*& newTail)
{
    newHead = newTail = nullptr;

    for (char c : binary)
    {
        if (c == '0' || c == '1')
            insertBit(newHead, newTail, c - '0');
    }
}


// Binary Addition
Node* addLists(Node* first, Node* second, Node*& resultTail)
{
    Node* p = first;
    Node* q = second;

    while (p->next != nullptr)
        p = p->next;

    while (q->next != nullptr)
        q = q->next;

    Node* resultHead = nullptr;
    resultTail = nullptr;

    int carry = 0;

    while (p != nullptr || q != nullptr || carry)
    {
        int sum = carry;

        if (p != nullptr)
        {
            sum += p->bit;
            p = p->prev;
        }

        if (q != nullptr)
        {
            sum += q->bit;
            q = q->prev;
        }

        Node* newNode = new Node{sum % 2, nullptr, nullptr};

        if (resultHead == nullptr)
            resultHead = resultTail = newNode;
        else
        {
            newNode->next = resultHead;
            resultHead->prev = newNode;
            resultHead = newNode;
        }

        carry = sum / 2;
    }

    return resultHead;
}


// Left shift
void shiftLeft(Node*& head, Node*& tail)
{
    insertBit(head, tail, 0);
}


// Copy a DLL
void copyList(Node* source, Node*& newHead, Node*& newTail)
{
    newHead = newTail = nullptr;

    while (source != nullptr)
    {
        insertBit(newHead, newTail, source->bit);
        source = source->next;
    }
}


// Binary Multiplication
Node* multiplyLists(Node* first, Node* second, Node*& resultTail)
{
    Node* resultHead = nullptr;
    resultTail = nullptr;

    insertBit(resultHead, resultTail, 0);

    Node* currentHead = nullptr;
    Node* currentTail = nullptr;

    copyList(first, currentHead, currentTail);

    Node* bit = second;

    while (bit->next != nullptr)
        bit = bit->next;

    while (bit != nullptr)
    {
        if (bit->bit == 1)
        {
            Node* newTail = nullptr;

            Node* newResult =
                addLists(resultHead, currentHead, newTail);

            deleteList(resultHead, resultTail);

            resultHead = newResult;
            resultTail = newTail;
        }

        shiftLeft(currentHead, currentTail);
        bit = bit->prev;
    }

    deleteList(currentHead, currentTail);

    return resultHead;
}


// Convert binary to decimal
long long binaryToDecimal()
{
    long long decimal = 0;
    Node* temp = head;

    while (temp != nullptr)
    {
        decimal = decimal * 2 + temp->bit;
        temp = temp->next;
    }

    return decimal;
}


// Binary Addition Menu
void additionMenu()
{
    string binary1, binary2;

    cout << "Enter first binary number: ";
    cin >> binary1;

    cout << "Enter second binary number: ";
    cin >> binary2;

    Node* firstHead = nullptr;
    Node* firstTail = nullptr;
    Node* secondHead = nullptr;
    Node* secondTail = nullptr;

    createList(binary1, firstHead, firstTail);
    createList(binary2, secondHead, secondTail);

    Node* resultTail = nullptr;
    Node* resultHead =
        addLists(firstHead, secondHead, resultTail);

    cout << "Sum: ";
    displayBinary(resultHead);

    deleteList(firstHead, firstTail);
    deleteList(secondHead, secondTail);
    deleteList(resultHead, resultTail);
}


// Binary Multiplication Menu
void multiplicationMenu()
{
    string binary1, binary2;

    cout << "Enter first binary number: ";
    cin >> binary1;

    cout << "Enter second binary number: ";
    cin >> binary2;

    Node* firstHead = nullptr;
    Node* firstTail = nullptr;
    Node* secondHead = nullptr;
    Node* secondTail = nullptr;

    createList(binary1, firstHead, firstTail);
    createList(binary2, secondHead, secondTail);

    Node* resultTail = nullptr;
    Node* resultHead =
        multiplyLists(firstHead, secondHead, resultTail);

    cout << "Product: ";
    displayBinary(resultHead);

    deleteList(firstHead, firstTail);
    deleteList(secondHead, secondTail);
    deleteList(resultHead, resultTail);
}


int main()
{
    int choice;

    do
    {
        cout << "\n===== Binary Arithmetic Using DLL =====\n";
        cout << "1. Store Binary Number\n";
        cout << "2. Display Binary Number\n";
        cout << "3. 1's Complement\n";
        cout << "4. 2's Complement\n";
        cout << "5. Binary Addition\n";
        cout << "6. Binary Multiplication\n";
        cout << "7. Convert to Decimal\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string binary;

            cout << "Enter binary number: ";
            cin >> binary;

            storeBinary(binary);

            cout << "Binary number stored successfully.\n";
        }
        else if (choice == 2)
        {
            displayBinary(head);
        }
        else if (choice == 3)
        {
            if (head == nullptr)
                cout << "No binary number stored.\n";
            else
            {
                onesComplement();

                cout << "1's Complement: ";
                displayBinary(head);
            }
        }
        else if (choice == 4)
        {
            if (head == nullptr)
                cout << "No binary number stored.\n";
            else
            {
                twosComplement();

                cout << "2's Complement: ";
                displayBinary(head);
            }
        }
        else if (choice == 5)
        {
            additionMenu();
        }
        else if (choice == 6)
        {
            multiplicationMenu();
        }
        else if (choice == 7)
        {
            if (head == nullptr)
                cout << "No binary number stored.\n";
            else
                cout << "Decimal: "
                     << binaryToDecimal() << endl;
        }
        else if (choice == 8)
        {
            deleteList(head, tail);
            cout << "Program ended.\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}
