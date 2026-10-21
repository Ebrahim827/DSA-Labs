#include <iostream>
#include <string>
using namespace std;

struct Student {
	int studentID;
	string name;
	float GPA;
	Student* left;
	Student* right;
};

// Create a new student node
Student* createStudent(int id, string name, float gpa) {
	Student* newStudent = new Student;

	newStudent->studentID = id;
	newStudent->name = name;
	newStudent->GPA = gpa;
	newStudent->left = nullptr;
	newStudent->right = nullptr;

	return newStudent;
}

// 1. Insert a student into BST
Student* Insert(Student* root, int id, string name, float gpa) {
	if (root == nullptr) {
		return createStudent(id, name, gpa);
	}

	if (id < root->studentID) {
		root->left = Insert(root->left, id, name, gpa);
	}
	else if (id > root->studentID) {
		root->right = Insert(root->right, id, name, gpa);
	}
	else {
		cout << "Student ID already exists!\n";
	}

	return root;
}

// Display student details
void displayStudent(Student* student) {
	cout << "ID: " << student->studentID
		<< " | Name: " << student->name
		<< " | GPA: " << student->GPA << endl;
}

Student* Search(Student* root, int id) {
	if (root == nullptr || root->studentID == id) {
		return root;
	}

	if (id < root->studentID) {
		return Search(root->left, id);
	}

	return Search(root->right, id);
}

Student* findMin(Student* root) {
	while (root != nullptr && root->left != nullptr) {
		root = root->left;
	}
	return root;
}

Student* Delete(Student* root, int id) {
	if (root == nullptr) {
		return nullptr;
	}

	if (id < root->studentID) {
		root->left = Delete(root->left, id);
	}
	else if (id > root->studentID) {
		root->right = Delete(root->right, id);
	}
	else {
		// Case 1: No left child
		if (root->left == nullptr) {
			Student* temp = root->right;
			delete root;
			return temp;
		}

		// Case 2: No right child
		if (root->right == nullptr) {
			Student* temp = root->left;
			delete root;
			return temp;
		}

		// Case 3: Two children
		Student* temp = findMin(root->right);

		root->studentID = temp->studentID;
		root->name = temp->name;
		root->GPA = temp->GPA;

		root->right = Delete(root->right, temp->studentID);
	}

	return root;
}

// 4. Inorder traversal: sorted by student ID
void Inorder(Student* root) {
	if (root == nullptr) {
		return;
	}

	Inorder(root->left);
	displayStudent(root);
	Inorder(root->right);
}

// 5. Count total students
int CountStudents(Student* root) {
	if (root == nullptr) {
		return 0;
	}

	return 1 + CountStudents(root->left)
		+ CountStudents(root->right);
}
Student* LowestGPA(Student* root, Student* best = nullptr) {
	if (root == nullptr) {
		return best;
	}

	if (best == nullptr || root->GPA < best->GPA) {
		best = root;
	}

	best = LowestGPA(root->left, best);
	best = LowestGPA(root->right, best);

	return best;
}

Student* HighestGPA(Student* root, Student* best = nullptr) {
	if (root == nullptr) {
		return best;
	}

	if (best == nullptr || root->GPA > best->GPA) {
		best = root;
	}

	best = HighestGPA(root->left, best);
	best = HighestGPA(root->right, best);

	return best;
}

// Display students above a given GPA
void DisplayAboveGPA(Student* root, float threshold) {
	if (root == nullptr) {
		return;
	}

	DisplayAboveGPA(root->left, threshold);

	if (root->GPA > threshold) {
		displayStudent(root);
	}

	DisplayAboveGPA(root->right, threshold);
}

// Free memory
void DeleteAll(Student* root) {
	if (root == nullptr) {
		return;
	}

	DeleteAll(root->left);
	DeleteAll(root->right);
	delete root;
}

int main() {
	Student* root = nullptr;
	int choice, id;
	string name;
	float gpa, threshold;

	do {
		cout << "\n===== Student Record Management =====\n";
		cout << "1. Insert Student\n";
		cout << "2. Search Student\n";
		cout << "3. Delete Student\n";
		cout << "4. Display Students (Inorder)\n";
		cout << "5. Count Total Students\n";
		cout << "6. Highest GPA\n";
		cout << "7. Lowest GPA\n";
		cout << "8. Display Students Above GPA\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter Student ID: ";
			cin >> id;

			cout << "Enter Name: ";
			getline(cin >> ws, name);

			cout << "Enter GPA: ";
			cin >> gpa;

			if (gpa < 0.0 || gpa > 4.0) {
				cout << "Invalid GPA! Enter GPA from 0 to 4.\n";
				break;
			}

			root = Insert(root, id, name, gpa);
			break;

		case 2: {
					cout << "Enter Student ID to search: ";
					cin >> id;

					Student* result = Search(root, id);

					if (result != nullptr) {
						cout << "Student Found:\n";
						displayStudent(result);
					}
					else {
						cout << "Student not found!\n";
					}
					break;
		}

		case 3:
			cout << "Enter Student ID to delete: ";
			cin >> id;

			if (Search(root, id) == nullptr) {
				cout << "Student not found!\n";
			}
			else {
				root = Delete(root, id);
				cout << "Student deleted successfully.\n";
			}
			break;

		case 4:
			cout << "\nStudent Records (Sorted by ID):\n";
			Inorder(root);
			break;

		case 5:
			cout << "Total Students: "
				<< CountStudents(root) << endl;
			break;

		case 6: {
					Student* best = HighestGPA(root);

					if (best != nullptr) {
						cout << "Student with Highest GPA:\n";
						displayStudent(best);
					}
					else {
						cout << "No student records available.\n";
					}
					break;
		}

		case 7: {
					Student* best = LowestGPA(root);

					if (best != nullptr) {
						cout << "Student with Lowest GPA:\n";
						displayStudent(best);
					}
					else {
						cout << "No student records available.\n";
					}
					break;
		}

		case 8:
			cout << "Enter GPA threshold: ";
			cin >> threshold;

			cout << "Students with GPA above "
				<< threshold << ":\n";
			DisplayAboveGPA(root, threshold);
			break;

		case 0:
			cout << "Exiting program...\n";
			break;

		default:
			cout << "Invalid choice! Try again.\n";
		}

	} while (choice != 0);

	DeleteAll(root);
	return 0;
}