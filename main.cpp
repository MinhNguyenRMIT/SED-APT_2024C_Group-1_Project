#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#include "member.cpp"
#include "user.cpp"
#include "admin-1.cpp"
#include "item.cpp"
#include "item.h"
#include "Rating and Bid/bidding.cpp"
#include "Rating and Bid/rating.cpp"

// Welcome Screen for all users
void welcomeScreen() {
    cout << "-----------------------------------\n";
    cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\nSemester 3 2024\nAUCTION APPLICATION\n\nInstructor: Dr Ling Huo Chong\nGroup: Group No 1.\nS3979760, Pham Hieu Dat\nS3965654, Le Tuan Kiet\nS4066691, Le Van Chi Hoang\nS3915233, Nguyen Hoanh Minh\n";
    cout << "-----------------------------------\n";
    cout << "-----------------------\n";
    cout << "AUCTION APPLICATION\n";
    cout << "-----------------------\n";
    cout << "1. Guest\n2. Member\n3. Admin\n4. Register as Member\n0. Exit\n";
    cout << "Enter your choice: ";
}

// Auction Dashboard Screen
void viewDashboard(const string &username) {
    cout << "\n--- Dashboard ---\n";

    cout << "\nYour active item listings:\n";
    cout << "No. | Name            | Category      | Current Bid | Current Bidder  | End Date & Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
    ifstream inFile("item.txt");
    if (!inFile) {
        cerr << "Error: Unable to open item.txt.\n";
        return;
    }

    string line;
    int itemCount = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string ID, itemName, category, description, highestBidder, seller;
        int startingBid, currentBid, minBuyerRating;
        time_t endTime, startTime;

        // Parse the line
        getline(ss, ID, ',');
        getline(ss, itemName, ',');
        getline(ss, category, ',');
        getline(ss, description, ',');
        getline(ss, highestBidder, ',');
        getline(ss, seller, ',');
        ss >> startingBid;
        ss.ignore();
        ss >> currentBid;
        ss.ignore();
        ss >> minBuyerRating;
        ss.ignore();
        ss >> endTime;
        ss.ignore();
        ss >> startTime;

        // Check if the seller matches the current user
        if (seller == username) {
            itemCount++;
            cout << itemCount << "   | " << itemName
                 << " | " << category
                 << "            | " << (currentBid == startingBid ? "No Bids" : to_string(currentBid))
                 << "      | " << highestBidder
                 << " | " << asctime(localtime(&endTime));
        }
    }

    inFile.close();

    // Handle case when no items are found
    if (itemCount == 0) {
        cout << "No active item listings found.\n";
    }

    cout << "\nYour active bids:\n";
    cout << "No. | Name            | Category      | Your Bid    | Current Bid     | End Date & Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
    

    int choice;
    cout << "\n1. View Item Listing Details\n2. View Active Bid Details\n3. Place a Bid\n4. Return to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;

    
    switch (choice) {
        case 1: {
            string itemId;
            cout << "Enter the number of the item listing to view details: ";
            cin >> itemId;
            item* loadedItem = loadItem(itemId);
            if (loadedItem) {
                loadedItem->viewBidding(); 
                delete loadedItem;        
            }
            break;
        }
        case 2: {
            cout << "Enter the number of the bid to view details: ";
            break;
        }

        case 3: {
            cout << "Bidding!\n";

            string currBidderName, newItemId, passw;
            int bidAmount, rate;

            cout << "Please re-enter your Password: ";
            cin >> passw;

            Member* loadedMember = loadUser(username, passw);
            if (loadedMember) {
                currBidderName = username;
                rate = loadedMember->getRating();
                delete loadedMember;
            } else {
                cout << "Invalid password or user not found.\n";
                break;
            }

            cout << "\nEnter Auction ID you wish to bid: ";
            cin >> newItemId;
            cout << "\nEnter Your bid amount: ";
            cin >> bidAmount;

            // Load item and place the bid
            item* loadedItem = loadItem(newItemId);
            if (loadedItem) {
                loadedItem->addBid(currBidderName, bidAmount, rate, newItemId);
                delete loadedItem;
            } else {
                cout << "Item not found for the given Auction ID.\n";
            }
            break;
        }

        case 4:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid option. Returning to main menu...\n";
            break;

    } 
}

// Member's Main Menu screen
void handleMember(Member &member) {
    int choice;
    do {
        cout << "\nMember Menu:\n";
        cout << "1. View Dashboard\n2. View Profile\n3. Create Item Listing\n4. Update Profile\n5. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                viewDashboard(member.getMemberName());
                break;
            case 2:
                int profChoice;
                member.viewProfile();
                cout << "Enter your Choice: ";
                cin >> profChoice;
                switch(profChoice){
                    case 1:
                        // topUpCredits(member);
                        break;
                    case 2:
                        cout << "\nProfile Updated Successfully!\n";
                        break;
                    case 0:
                        break;
                }

                break;
            case 3: {
                string ID, itemName, category, description, highestBidder, seller;
                int startingBid, currentBid, minBuyerRating;
                time_t endTime, startTime;

                seller = member.getMemberName();
                cout << "Enter Item ID: ";
                cin >> ID;
                cin.ignore();
                cout << "Enter Item Name: ";
                getline(cin, itemName);
                cout << "Enter Category: ";
                getline(cin, category);
                cout << "Enter Description: ";
                getline(cin, description);
                highestBidder = "---";
                cout << "Enter Starting Bid: ";
                cin >> startingBid;
                currentBid = 0;
                cout << "Enter Minimum Buyer Rating: ";
                cin >> minBuyerRating;
                cout << "Enter bid length in days: ";
                cin >> endTime;
                cout << "Enter start time in days: ";
                cin >> startTime;

                item item(ID, itemName, category, description, highestBidder, seller, startingBid, currentBid, minBuyerRating, endTime, startTime);
                ofstream outFile("item.txt", ios::app);
                if (outFile) {
                    outFile << ID << "," << itemName << "," << category << "," << description << "," << highestBidder << "," << seller << "," << startingBid << "," << currentBid << "," << minBuyerRating << "," << endTime << "," << startTime << "," << "\n";
                    cout << "Item Listing created! Here's what the info: ";
                    item.viewBidding();
                } else {
                    cerr << "Error: Unable to save Item Listing information to file.\n";
                }
                outFile.close();
                break;
            }
            case 4:{ // Option for updating profile
                string currUser = member.getMemberName();
                string password;
                cout << "Re-enter your password for security: ";
                cin >> password;
                updateProfile(currUser, password); // Pass current username and password
                break;
            }

            case 5:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);
}

// NEW TEST MAIN
int main() {
    int userType;
    
    while (true) {
        welcomeScreen();
        cin >> userType;

        switch (userType) {
            case 1:
                cout << "Feature not implemented for this member type.\n";
                break;

            case 2: {
                string username, password;
                cout << "\nEnter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                login(username, password);
                if (isLoggedIn(username, password)) {
                    Member *member = loadUser(username, password);
                    if (member) {
                        handleMember(*member);
                        delete member;
                    }
                } else {
                    cout << "Invalid username or password.\n";
                }
                break;
            }

            case 3:
                adminView();
                break;

            case 4:
                registerUser();
                break;

            case 0:
                cout << "Exiting program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}
