#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

struct Node {
	char data;
	Node* left;
	Node* right;

	Node(char value) {
		data = value;
		left = nullptr;
		right = nullptr;
	}
};

Node* buildTree(const string& str, int& index) {
	if (index >= (int)str.length() ||
		str[index] == ',' || str[index] == ')') {
		return nullptr;
	} 

	Node* root = new Node(str[index]);
	index++;

	if (index < (int)str.length() && str[index] == '(') {
		index++;

		if (index < (int)str.length() && str[index] != ',') {
			root->left = buildTree(str, index);
		}

		if (index < (int)str.length() && str[index] == ',') {
			index++;
		}

		if (index < (int)str.length() && str[index] != ')') {
			root->right = buildTree(str, index);
		}

		if (index < (int)str.length() && str[index] == ')') {
			index++;
		}
	}

	return root;
}

Node* constructTree(const string& str) {
	int index = 0;
	return buildTree(str, index);
}

//preorder first goes to left , if its left is nullptr traverses back and starts roots right part recursively

void preorderRecursive(Node* root) {
	if (root == nullptr) {
		return;
	}

	cout << root->data << " ";
	preorderRecursive(root->left);
	preorderRecursive(root->right);
}

void inorderIterative(Node* root) {
	stack<Node*> s;
	Node* current = root;

	while (current != nullptr || !s.empty()) {
		while (current != nullptr) {
			s.push(current);
			current = current->left;
		}

		current = s.top();
		s.pop();

		cout << current->data << " ";
		current = current->right;
	}
}

void postorderIterative(Node* root) {
	stack<Node*> s;
	Node* current = root;
	Node* lastVisited = nullptr;

	while (current != nullptr || !s.empty()) {
		if (current != nullptr) {
			s.push(current);
			current = current->left;
		}
		else {
			Node* topNode = s.top();

			if (topNode->right != nullptr &&
				lastVisited != topNode->right) {
				current = topNode->right;
			}
			else {
				cout << topNode->data << " ";
				lastVisited = topNode;
				s.pop();
			}
		}
	}
}

bool validateNode(const string& str, int& index) {
	if (index >= (int)str.length() ||
		str[index] == '(' ||
		str[index] == ')' ||
		str[index] == ',' ||
		isspace(static_cast<unsigned char>(str[index]))) {
		return false;
	}

	index++;

	if (index >= (int)str.length() || str[index] != '(') {
		return true;
	}

	index++;

	if (index < (int)str.length() && str[index] != ',') {
		if (!validateNode(str, index)) {
			return false;
		}
	}

	if (index >= (int)str.length() || str[index] != ',') {
		return false;
	}

	index++;

	if (index < (int)str.length() && str[index] != ')') {
		if (!validateNode(str, index)) {
			return false;
		}
	}

	if (index >= (int)str.length() || str[index] != ')') {
		return false;
	}

	index++;
	return true;
}

bool validateTreeString(const string& str) {
	if (str.empty()) {
		return false;
	}

	int index = 0;

	if (!validateNode(str, index)) {
		return false;
	}

	return index == (int)str.length();
}

int treeHeight(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	int leftHeight = treeHeight(root->left);
	int rightHeight = treeHeight(root->right);

	return 1 + max(leftHeight, rightHeight);
}

void displayNodeDepths(Node* root, int depth = 0) {
	if (root == nullptr) {
		return;
	}

	cout << "Node " << root->data
		<< " -> Depth: " << depth << endl;

	displayNodeDepths(root->left, depth + 1);
	displayNodeDepths(root->right, depth + 1);
}

struct BSTNode {
	int data;
	BSTNode* left;
	BSTNode* right;

	BSTNode(int value) {
		data = value;
		left = nullptr;
		right = nullptr;
	}
};

BSTNode* insertBST(BSTNode* root, int value) {
	if (root == nullptr) {
		return new BSTNode(value);
	}

	if (value < root->data) {
		root->left = insertBST(root->left, value);
	}
	else if (value > root->data) {
		root->right = insertBST(root->right, value);
	}

	return root;
}

BSTNode* constructBST(const vector<int>& values) {
	BSTNode* root = nullptr;

	for (int value : values) {
		root = insertBST(root, value);
	}

	return root;
}

void inorderBST(BSTNode* root) {
	if (root == nullptr) {
		return;
	}

	inorderBST(root->left);
	cout << root->data << " ";
	inorderBST(root->right);
}

void deleteTree(Node* root) {
	if (root == nullptr) {
		return;
	}

	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

void deleteBST(BSTNode* root) {
	if (root == nullptr) {
		return;
	}

	deleteBST(root->left);
	deleteBST(root->right);
	delete root;
}

int main() {
	// Task 1: Generate binary tree from the given string
	string treeString = "a(b(d,e),c(,f(g,)))";
	cout << "========== TASK 1 ==========" << endl;
	cout << "Tree String: " << treeString << endl;

	Node* root = constructTree(treeString);
	cout << "Binary tree constructed successfully." << endl;

	// Task 2: Generate preorder form recursively
	cout << "\n========== TASK 2 ==========" << endl;
	cout << "Preorder (Recursive): ";
	preorderRecursive(root);
	cout << endl;

	// Task 3: Generate inorder form iteratively using a stack
	cout << "\n========== TASK 3 ==========" << endl;
	cout << "Inorder (Iterative): ";
	inorderIterative(root);
	cout << endl;

	// Task 4: Generate postorder form iteratively using a stack
	cout << "\n========== TASK 4 ==========" << endl;
	cout << "Postorder (Iterative): ";
	postorderIterative(root);
	cout << endl;

	// Task 5: Validate the tree string without building a tree
	cout << "\n========== TASK 5 ==========" << endl;
	if (validateTreeString(treeString)) {
		cout << "The tree string is valid." << endl;
	}
	else {
		cout << "The tree string is invalid." << endl;
	}

	// Task 6: Calculate tree height and depth of each node
	cout << "\n========== TASK 6 ==========" << endl;
	cout << "Tree Height (in nodes): "
		<< treeHeight(root) << endl;

	cout << "\nDepth of Each Node:" << endl;
	displayNodeDepths(root);

	// Task 7: Generate a BST from a sequence of integers
	cout << "\n========== TASK 7 ==========" << endl;
	vector<int> values = { 50, 30, 70, 20, 40, 60, 80 };

	BSTNode* bstRoot = constructBST(values);

	cout << "Input Sequence: ";
	for (int value : values) {
		cout << value << " ";
	}

	cout << "\nBST Inorder Traversal: ";
	inorderBST(bstRoot);
	cout << endl;

	// Free dynamically allocated memory
	deleteTree(root);
	deleteBST(bstRoot);

	return 0;
}