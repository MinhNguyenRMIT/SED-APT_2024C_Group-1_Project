#include <iostream>
#include "membertest.cpp" 

using namespace std;

int main() {
    Member currentMember;
    bool isLoggedIn = false;

    while (true) {
        cout << "\n------ Main Menu ------\n";
        if (!isLoggedIn) {
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "0. Exit";
        } else {
            cout << "1. View your account\n";
            cout << "2. Update Profile\n";
            cout << "3. View Dashboard\n";
            cout << "4. Create Item Listing\n";
            cout << "5. Top-Up Credit Points\n";
            cout << "6. Logout\n";
            cout << "0. Exit";
        }
        cout << "\n-----------------------\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!isLoggedIn) {
                    // Register user
                    cout << "\n--- Register ---\n";
                    currentMember.registerUser(); // Inherited from User class
                } else {
                    // View Profile
                    cout << "\n--- Profile ---\n";
                    currentMember.viewProfile();
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
                    // Update Profile
                    cout << "\n--- Update Profile ---\n";
                    currentMember.updateProfile();
                }
                break;

            case 3:
                if (!isLoggedIn) {
                    cout << "Invalid option!\n";
                } else {
                    // View Dashboard
                    currentMember.viewDashboard(); // Member-specific method
                }
                break;

            case 4:
                if (!isLoggedIn) {
                    cout << "Invalid option!\n";
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

            case 5:
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

            case 6:
                if (isLoggedIn){
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
