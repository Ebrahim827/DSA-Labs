#include <iostream>
using namespace std;

void inputSortedIDs(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Enter registration ID " << i + 1 << ": ";
		cin >> arr[i];
	}
}

// Function to check whether the array is sorted
bool isSorted(int arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			return false;
		}
	}

	return true;
}

// binary search

int binarySearch(int arr[], int low, int high, int target)
{
	while (low <= high)
	{
		int mid = low + (high - low) / 2;

		if (arr[mid] == target)
		{
			return mid;
		}
		else if (target < arr[mid])
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	return -1;
}

int main()
{
	int n;

	cout << " Binary Search on Registration IDs "
		<< endl;

	cout << "Enter the number of students: ";
	cin >> n;

	// Validate 
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
		cout << "Enter the registration ID to search for: ";
		cin >> target;

		cout << "Registration ID not found." << endl;
		return 0;
	}

	int* arr = new int[n];

	inputSortedIDs(arr, n);

	if (!isSorted(arr, n))
	{
		cout << "Error: Registration IDs must be in "
			<< "ascending order." << endl;

		delete[] arr;
		return 1;
	}

	// Input the target registration ID
	int target;
	cout << "Enter the registration ID to search for: ";
	cin >> target;

	// Perform binary search
	int index = binarySearch(arr, 0, n - 1, target);

	if (index != -1)
	{
		cout << "Registration ID found at index "
			<< index << endl;
	}
	else
	{
		cout << "Registration ID not found." << endl;
	}

	delete[] arr;

	return 0;
}