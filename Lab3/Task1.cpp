#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Checks whether the string is a palindrome
bool isPalindrome(string str)
{
    string cleaned;

    // Keep only letters and numbers and convert them to lowercase
    // isalnum is an inbuilt function in cctype that checks whether a character is alphanumeric or not.
    for (char ch : str)
    {
        if (isalnum(ch))
        {
            cleaned += tolower(ch);
        }
    }

    int left = 0;
    int right = cleaned.length() - 1;

    // Compare characters from both ends
    while (left < right)
    {
        if (cleaned[left] != cleaned[right])
            return false;

        left++;
        right--;
    }

    return true;
}

int main()
{
    string str;

    cout << "Enter a string: ";
    getline(cin, str);

    if (isPalindrome(str))
    {
        cout << str << " is a palindrome." << endl;
    }
    else
    {
        cout << str << " is not a palindrome." << endl;
    }

    return 0;
}