#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Node
{
    string data;
    Node* next;
};

class Stack
{
private:
    Node* top;

public:
    Stack()
    {
        top = nullptr;
    }

    void push(string value)
    {
        Node* newNode = new Node();

        newNode->data = value;
        newNode->next = top;

        top = newNode;
    }

    string pop()
    {
        if (isEmpty())
        {
            return "";
        }

        Node* temp = top;
        string value = top->data;

        top = top->next;

        delete temp;

        return value;
    }

    string peek()
    {
        if (isEmpty())
        {
            return "";
        }

        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    ~Stack()
    {
        clear();
    }
};

bool isOperator(char ch)
{
    return ch == '+' ||
           ch == '-' ||
           ch == '*' ||
           ch == '/' ||
           ch == '%';
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/' || op == '%')
        return 2;

    return 0;
}

bool infixToPostfix(string infix, string& postfix)
{
    Stack stack;
    postfix = "";

    if (infix.empty())
    {
        return false;
    }

    bool hasOperand = false;

    for (int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];

        if (ch == ' ')
        {
            continue;
        }

        // Read complete number
        if (isdigit(ch))
        {
            string number = "";

            while (i < infix.length() && isdigit(infix[i]))
            {
                number += infix[i];
                i++;
            }

            i--;

            postfix += number + " ";
            hasOperand = true;
        }

        // Opening parenthesis
        else if (ch == '(')
        {
            stack.push("(");
        }

        // Closing parenthesis
        else if (ch == ')')
        {
            bool foundOpening = false;

            while (!stack.isEmpty())
            {
                string top = stack.pop();

                if (top == "(")
                {
                    foundOpening = true;
                    break;
                }

                postfix += top + " ";
            }

            if (!foundOpening)
            {
                return false;
            }
        }

        // Operator
        else if (isOperator(ch))
        {
            while (!stack.isEmpty() &&
                   stack.peek() != "(" &&
                   precedence(stack.peek()[0]) >= precedence(ch))
            {
                postfix += stack.pop() + " ";
            }

            stack.push(string(1, ch));
        }

        // Invalid character
        else
        {
            return false;
        }
    }

    // Remove remaining operators
    while (!stack.isEmpty())
    {
        string top = stack.pop();

        if (top == "(")
        {
            return false;
        }

        postfix += top + " ";
    }

    return hasOperand;
}

bool evaluatePostfix(string postfix, int& result)
{
    Stack stack;

    for (int i = 0; i < postfix.length(); i++)
    {
        // Skip spaces
        if (postfix[i] == ' ')
        {
            continue;
        }

        // Number
        if (isdigit(postfix[i]))
        {
            string number = "";

            while (i < postfix.length() &&
                   isdigit(postfix[i]))
            {
                number += postfix[i];
                i++;
            }

            i--;

            stack.push(number);
        }

        // Operator
        else if (isOperator(postfix[i]))
        {
            if (stack.isEmpty())
            {
                return false;
            }

            int right = stoi(stack.pop());

            if (stack.isEmpty())
            {
                return false;
            }

            int left = stoi(stack.pop());

            int value;

            if (postfix[i] == '+')
            {
                value = left + right;
            }
            else if (postfix[i] == '-')
            {
                value = left - right;
            }
            else if (postfix[i] == '*')
            {
                value = left * right;
            }
            else if (postfix[i] == '/')
            {
                if (right == 0)
                {
                    return false;
                }

                value = left / right;
            }
            else
            {
                if (right == 0)
                {
                    return false;
                }

                value = left % right;
            }

            stack.push(to_string(value));
        }
        else
        {
            return false;
        }
    }

    if (stack.isEmpty())
    {
        return false;
    }

    result = stoi(stack.pop());

    // More than one value means invalid expression
    if (!stack.isEmpty())
    {
        return false;
    }

    return true;
}

int main()
{
    string expression;
    string postfix;
    int result;

    cout << "Enter an infix expression: ";
    getline(cin, expression);

    if (!infixToPostfix(expression, postfix))
    {
        cout << "Invalid expression or mismatched parentheses." << endl;
        return 0;
    }

    cout << "Postfix Expression: " << postfix << endl;

    if (!evaluatePostfix(postfix, result))
    {
        cout << "Invalid expression or division by zero." << endl;
        return 0;
    }

    cout << "Result: " << result << endl;

    return 0;
}