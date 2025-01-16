#include <iostream>
using std::string;
using namespace std;
#include <ctime>
#include <bits/stdc++.h>

class Admin {
private:
    static const string adminUser; // Static credentials for the admin
    static const string adminPass;

public:
    Admin() = default; // Default constructor

    static bool isAdmin(const string &inputUser, const string &inputPass) {
        if (inputUser == adminUser && inputPass == adminPass) {
            return true;
        } else {
            cout << "Invalid username or password.\n";
            return false;
        }
    }

};

void readUsers() {
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cerr << "Unable to open users.txt" << endl;
        return;
    }
    string line;
    while (getline(usersFile, line)) {
        cout << line << endl;
    }
    usersFile.close();
}

void readItems() {
    ifstream itemsFile("item.txt");
    if (!itemsFile) {
        cerr << "Unable to open items.txt" << endl;
        return;
    }
    string line;
    while (getline(itemsFile, line)) {
        cout << line << endl;
    }
    itemsFile.close();
}


const string Admin::adminUser = "admin";
const string Admin::adminPass = "admin";

void adminView() {
    string inputUser, inputPass;
    cout << "Enter Admin Username: ";
    cin >> inputUser;
    cout << "Enter Admin Password: ";
    cin >> inputPass;

    if (Admin::isAdmin(inputUser, inputPass)) {
        cout << "Welcome, Admin!\n";

        // Admin Menu
        int choice;
        do {
            cout << "\nAdmin Menu:\n";
            cout << "1. View Users\n2. View Items\n0. Exit\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    readUsers();
                    break;
                case 2:
                    readItems();
                    break;
                case 0:
                    cout << "Exiting admin menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 0);

    } else {
        cout << "Access Denied.\n";
    }
}

// int main(){
//     adminView();
// }
