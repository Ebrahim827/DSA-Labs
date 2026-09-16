#include <iostream>
using namespace std;

int main()
{
int a=8, *pa;      // Statement 1
pa = &a;           // Statement 2
cout<<"Trying multiplication of pointer pa by 3: "<<*pa*3<<endl;  		
}



