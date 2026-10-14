#include <iostream>
using namespace std;

// Function to input student IDs into the array
void inputIDs(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Enter student ID " << i + 1 << ": ";
		cin >> arr[i];
	}
}

int linearSearch(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }

    return -1;
}

void displayResult(int index)
{
	if (index != -1)
	{
		cout << "Student ID found at index " << index << endl;
	}
	else
	{
		cout << "Student ID is not registered." << endl;
	}
}

int main()
{
	int n;

	cout << " Student ID Search Using Linear Search "
		<< endl;

	cout << "Enter the number of students: ";
	cin >> n;

	// Validate the number of students
	if (cin.fail() || n < 0)
	{
		cout << "Invalid number of students." << endl;
		return 1;
	}

	// Handle an empty array
	if (n == 0)
	{
		cout << "The array is empty." << endl;

		int target;
		cout << "Enter the target student ID: ";
		cin >> target;

		displayResult(-1);
		return 0;
	}

	int* arr = new int[n];

	inputIDs(arr, n);

	int target;
	cout << "Enter the student ID to search for: ";
	cin >> target;

	int index = linearSearch(arr, n, target);

	displayResult(index);

	delete[] arr;

	return 0;
}