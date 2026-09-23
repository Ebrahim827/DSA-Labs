#include <iostream>
using namespace std;

// it checks each character in the string 1st and last index if they are same.
// If true it moves to 2nd and 2nd last index and checks again. If all characters are same its a palindrome.
bool isPalindrome(string str){
    int left=0;
    int right=str.length()-1;

    while(left<right){
        if(str[left] !=str[right] )
            return false;
        left++;
        right--;
    }
    return true;
}

int main(){
    string str;
    cout<<"Enter a string: ";
    cin>>str;

    if(isPalindrome(str)){
        cout<<str<<" is a palindrome."<<endl;
    } else {
        cout<<str<<" is not a palindrome."<<endl;
    }
    return 0;
}