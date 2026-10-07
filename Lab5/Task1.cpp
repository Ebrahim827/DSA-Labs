#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* next;
};

class Stack {
    private:
        Node* top;

    public:
    Stack() {
        top = nullptr;
    }

    void push(char ch){
        Node* newNode = new Node();
        newNode->data = ch;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        Node* temp = top;
        char poppedData = top->data;
        top = top->next;
        delete temp;
        return poppedData;
    }

    char peek() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        return top->data;
    }

    bool isempty(){
        return top == nullptr;
    }

    void display() {
        if (isempty()) {
            cout << "Stack is empty!" << endl;
            return;
        }

        Node* current = top;
        cout << "Stack elements: ";

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void clear() {
        while (!isempty()){
            pop();
        }
    }

    ~Stack() {
        clear();
    }

};

// Check whether two brackets match
bool isMatching(char opening, char closing)
{
    if (opening == '(' && closing == ')')
        return true;

    if (opening == '[' && closing == ']')
        return true;

    if (opening == '{' && closing == '}')
        return true;

    return false;
}

// Check whether brackets in expression are balanced
bool checkBalance(string expression)
{
    Stack stack;

    for (int i = 0; i < expression.length(); i++)
    {
        char ch = expression[i];

        // Opening brackets are pushed
        if (ch == '(' || ch == '[' || ch == '{')
        {
            stack.push(ch);
        }

        // Closing brackets are checked
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            // Extra closing bracket
            if (stack.isempty())
            {
                return false;
            }

            char opening = stack.pop();

            // Mismatched brackets
            if (!isMatching(opening, ch))
            {
                return false;
            }
        }
    }

    // If stack is empty, all brackets were matched
    return stack.isempty();
}

int main()
{
    string expression;

    cout << "Enter an expression: ";
    getline(cin, expression);

    if (checkBalance(expression))
    {
        cout << "Balanced" << endl;
    }
    else
    {
        cout << "Not Balanced" << endl;
    }

    return 0;
}