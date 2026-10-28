#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
    int data, height;
    Node *left, *right;

    Node(int value) {
        data = value;
        height = 1;
        left = right = nullptr;
    }
};

int height(Node* root) {
    return root == nullptr ? 0 : root->height;
}

int balanceFactor(Node* root) {
    return root == nullptr ? 0 :
           height(root->left) - height(root->right);
}

void updateHeight(Node* root) {
    root->height = 1 + max(height(root->left),
                           height(root->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* balance(Node* root) {
    if (root == nullptr)
        return root;

    updateHeight(root);
    int bf = balanceFactor(root);

    // Left-Left case
    if (bf > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left-Right case
    if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right-Right case
    if (bf < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right-Left case
    if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* search(Node* root, int value) {
    if (root == nullptr || root->data == value)
        return root;

    if (value < root->data)
        return search(root->left, value);

    return search(root->right, value);
}

Node* insert(Node* root, int value) {
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        return root;

    return balance(root);
}

Node* minNode(Node* root) {
    while (root->left != nullptr)
        root = root->left;

    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr)
        return nullptr;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* child = root->left != nullptr ?
                          root->left : root->right;

            delete root;
            return child;
        }

        Node* successor = minNode(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right,
                                 successor->data);
    }

    return balance(root);
}

void inorder(Node* root, vector<int>& values) {
    if (root == nullptr)
        return;

    inorder(root->left, values);
    values.push_back(root->data);
    inorder(root->right, values);
}

void printTree(Node* root, int space = 0) {
    if (root == nullptr)
        return;

    space += 5;

    printTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";

    cout << root->data << endl;

    printTree(root->left, space);
}

void deleteTree(Node* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int choice, value, k;
    char criterion;

    cout << "Choose criterion: M for Maximum, "
         << "m for Minimum: ";
    cin >> criterion;

    if (criterion != 'M' && criterion != 'm') {
        cout << "Invalid criterion.\n";
        return 0;
    }

    do {
        cout << "\n1. Insert element(s)\n";
        cout << "2. Query top k elements\n";
        cout << "3. Delete top k elements\n";
        cout << "4. Print tree\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << "How many elements? ";
            cin >> n;

            if (n < 0) {
                cout << "Invalid number of elements.\n";
                continue;
            }

            for (int i = 0; i < n; i++) {
                cout << "Enter value: ";
                cin >> value;

                if (search(root, value) != nullptr) {
                    cout << "Duplicate value ignored.\n";
                    continue;
                }

                root = insert(root, value);

                cout << "Tree after insertion:\n";
                printTree(root);
                cout << endl;
            }
        }
        else if (choice == 2 || choice == 3) {
            vector<int> values;
            inorder(root, values);

            if (values.empty()) {
                cout << "Tree is empty.\n";
                continue;
            }

            cout << "Enter k: ";
            cin >> k;

            if (k <= 0 || k > (int)values.size()) {
                cout << "Invalid k.\n";
                continue;
            }

            cout << (choice == 2 ?
                     "Top k elements: " :
                     "Deleting top k elements: ");

            if (criterion == 'M') {
                for (int i = (int)values.size() - 1;
                     i >= (int)values.size() - k; i--)
                    cout << values[i] << " ";
            }
            else {
                for (int i = 0; i < k; i++)
                    cout << values[i] << " ";
            }

            cout << endl;

            if (choice == 3) {
                for (int i = 0; i < k; i++) {
                    int index = (criterion == 'M') ?
                        (int)values.size() - 1 - i : i;

                    int target = values[index];
                    root = deleteNode(root, target);

                    cout << "Tree after deleting "
                         << target << ":\n";

                    printTree(root);
                    cout << endl;
                }
            }
        }
        else if (choice == 4) {
            if (root == nullptr)
                cout << "Tree is empty.\n";
            else
                printTree(root);
        }
        else if (choice != 5) {
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    deleteTree(root);
    return 0;
}
