#include <iostream>
#include <string>
using namespace std;

struct Song{
    int id;
    string name;
    string duration;

    Song* next;
    Song* prev;
};

Song* head = nullptr;
Song* tail = nullptr;
Song* current = nullptr;

// Add song function
void addSong(int id, string name, string duration) {
    Song *newSong = new Song{id, name, duration, nullptr, nullptr};

    if(head==nullptr){
        head=tail=current=newSong;
    }

    else{
        newSong->prev=tail;
        tail->next=newSong;
        tail=newSong;
    }

    cout<< "Song added successfully!" << endl;
}

//Delete function by song ids
void deleteSong(int id) {
    Song *temp = head;
    Song *prev = head;

    //Edge case of head being the node

    if(head != nullptr && head->id==id){
        head=head->next;     
        
        if(head!=nullptr){
            head->prev=nullptr;
        }
        delete temp;
        return;
    }


    while(temp!=nullptr && temp->id != id){
        prev=temp;
        temp=temp->next;
    }

         // Song not found
        if (temp == nullptr) {
        cout << "Song not found ";
        return;
        }

        // Delete node
        prev->next = temp->next;

        if (temp->next != nullptr) {
        temp->next->prev = prev;
        }

        delete temp;
    }

// 3. Display Playlist Forward
void displayForward()
{
    if (head == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head;

    cout << "\nPlaylist (Forward):\n";

    while (temp != nullptr)
    {
        cout << "ID: " << temp->id
             << " | Name: " << temp->name
             << " | Duration: " << temp->duration << endl;

        temp = temp->next;
    }
}

// 4. Display Playlist Backward
void displayBackward()
{
    if (tail == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = tail;

    cout << "\nPlaylist (Backward):\n";

    while (temp != nullptr)
    {
        cout << "ID: " << temp->id
             << " | Name: " << temp->name
             << " | Duration: " << temp->duration << endl;

        temp = temp->prev;
    }
}    

// 5. Search Song
void searchSong(int id)
{
    Song* temp = head;

    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << "\nSong Found:\n";
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Duration: " << temp->duration << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Song not found.\n";
}

// 6. Play Next
void playNext()
{
    if (current == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->next != nullptr)
        current = current->next;
    else
        cout << "Already at the last song.\n";

    cout << "Now Playing: " << current->name << endl;
}

// 6. Play Previous
void playPrevious()
{
    if (current == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->prev != nullptr)
        current = current->prev;
    else
        cout << "Already at the first song.\n";

    cout << "Now Playing: " << current->name << endl;
}

// 7. Reverse Playlist
void reversePlaylist()
{
    Song* curr = head;
    Song* prev = nullptr;
    Song* nextNode = nullptr;

    while (curr != nullptr)
    {
        nextNode = curr->next;

        curr->next = prev;
        curr->prev = nextNode;
        prev = curr;
        curr = nextNode;
    }
    // Swap head and tail
    Song* temp = head;
    head = tail;
    tail = temp;

    cout << "Playlist reversed successfully.\n";
}

// Free memory
void destroyPlaylist()
{
    Song* temp = head;

    while (temp != nullptr)
    {
        Song* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    head = tail = current = nullptr;
}

int main()
{
    int choice;

    do
    {
        cout << "\n===== Playlist Management System =====\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next\n";
        cout << "7. Play Previous\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id;
            string name, duration;

            cout << "Enter Song ID: ";
            cin >> id;

            cin.ignore();
            cout << "Enter Song Name: ";
            getline(cin, name);

            cout << "Enter Duration (mm:ss): ";
            cin >> duration;

            addSong(id, name, duration);
            break;
        }

        case 2:
        {
            int id;
            cout << "Enter Song ID to delete: ";
            cin >> id;

            deleteSong(id);
            break;
        }

        case 3:
            displayForward();
            break;

        case 4:
            displayBackward();
            break;

        case 5:
        {
            int id;
            cout << "Enter Song ID to search: ";
            cin >> id;

            searchSong(id);
            break;
        }

        case 6:
            playNext();
            break;

        case 7:
            playPrevious();
            break;

        case 8:
            reversePlaylist();
            break;

        case 9:
            destroyPlaylist();
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    return 0;
}




    


   