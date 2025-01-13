#include <iostream>
// #include "user.cpp" 
#include "membertest.cpp" 

using namespace std;

int main() {
    Member currentMember;
    bool isLoggedIn = false;

    while (true) {
        cout << "\n--- Main Menu ---\n";
        if (!isLoggedIn) {
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "0. Exit\n";
        } else {
            cout << "1. View Dashboard\n";
            cout << "2. Create Item Listing\n";
            cout << "3. Top-Up Credit Points\n";
            cout << "4. Logout\n";
            cout << "0. Exit\n";
        }

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!isLoggedIn) {
                    
                    cout << "\n--- Register ---\n";
                    currentMember.registerUser(); // Inherited from User class
                } else {
                    // View Dashboard
                    currentMember.viewDashboard(); // Member-specific method
                }
                break;

            case 2:
                if (!isLoggedIn) {
                    // Login
                    cout << "\n--- Login ---\n";
                    string inputUsername, inputPassword;
                    cout << "Enter Username: ";
                    cin >> inputUsername;
                    cout << "Enter Password: ";
                    cin >> inputPassword;

                    if (currentMember.isLoggedIn(inputUsername, inputPassword)) {
                        cout << "Login successful!\n";
                        isLoggedIn = true;
                    } else {
                        cout << "Invalid username or password. Please try again.\n";
                    }
                } else {
                    cout << "\n--- Create Item Listing ---\n";
                    int id, startingBid;
                    string name, category, description;

                    cout << "Enter Item ID: ";
                    cin >> id;
                    cin.ignore(); // Ignore newline character
                    cout << "Enter Item Name: ";
                    getline(cin, name);
                    cout << "Enter Category: ";
                    getline(cin, category);
                    cout << "Enter Description: ";
                    getline(cin, description);
                    cout << "Enter Starting Bid: ";
                    cin >> startingBid;

                    currentMember.createItemListing(id, name, category, description, startingBid);
                }
                break;

            case 3:
                if (isLoggedIn) {
                    cout << "\n--- Top-Up Credit Points ---\n";
                    int amount;
                    cout << "Enter amount to top-up: ";
                    cin >> amount;
                    currentMember.topUpCredits(amount); // Member-specific method
                } else {
                    cout << "Invalid option!\n";
                }
                break;

            case 4:
                if (isLoggedIn) {
                    // Logout
                    cout << "\n--- Logout ---\n";
                    isLoggedIn = false;
                    cout << "You have successfully logged out.\n";
                } else {
                    cout << "Invalid option!\n";
                }
                break;

            case 0:
                cout << "Exiting program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
