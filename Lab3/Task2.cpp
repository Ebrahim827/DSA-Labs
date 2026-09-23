#include <iostream>
#include <string>
using namespace std;

class StringPool {

    private:
    string* stringPool;
    int currentSize;
    int maxSize;

    public:
    //constructor
    StringPool(){
        maxSize=5;
        currentSize=0;
        stringPool=new string[maxSize];
    };

    //Adds string
    void addString(string str){
        if(currentSize < maxSize){
            stringPool[currentSize]=str;
            currentSize++;
            cout<<"String "<<str<<" is added successfully ;)."<<endl;
        }

        else{
            cout<<"OOPS SORRY! String pool is full."<<endl;
        }
    }

    void removeString(string str){
        int index=-1;
        for(int i=0;i<currentSize;i++){
            if(stringPool[i]==str){
                index=i;
                break;
            }
        }

        if(index == -1){
            cout << "String " << str << " is not found in the pool." << endl;
            return;
        }

        // Shift remaining strings to the left
        for (int i = index; i < currentSize - 1; i++) { 
            stringPool[i] = stringPool[i + 1]; 
        }
         currentSize--; 
         cout << "String " << str << " removed from the pool." << endl;     
        
    }

 void displayPool() { 
    cout << "\nCurrent Pool:" << endl; 
    for (int i = 0; i < currentSize; i++) { 
        cout << i + 1 << "-- " << stringPool[i] << endl;
     } 
     cout << "Current size: " << currentSize << endl;
     cout << "Maximum size: " << maxSize << endl;
 }

 //Calling destructor to free memory
    ~StringPool(){
        delete[] stringPool;
        stringPool=nullptr;

        cout << "Memory successfully released." << endl;
    }

};

int main() {
    StringPool pool;

    pool.addString("Hello");
    pool.addString("My name");
    pool.addString("is");
    pool.addString("Ebrahim");
    pool.displayPool();
    
    pool.removeString("Hello");
    pool.displayPool();

    return 0;
}