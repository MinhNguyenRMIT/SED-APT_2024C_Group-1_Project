#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#include "member.cpp"
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
    ifstream inFileS("item.txt");
    if (!inFileS) {
        cerr << "Error: Unable to open item.txt.\n";
        return;
    };

    string sLine;
    while (getline(inFileS, sLine)) {
        stringstream ss(sLine);
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
            cout << ID << "   | " << itemName
                 << " | " << category
                 << "            | " << (currentBid == startingBid ? "No Bids" : to_string(currentBid))
                 << "      | " << highestBidder
                 << " | " << asctime(localtime(&endTime));
        }
    }
    inFileS.close();

    cout << "\nYour active bids:\n";
    cout << "No. | Name     | Category      | Your Bid    | Current Bid     | End Date & Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
    ifstream inFileH("item.txt");
    if (!inFileH) {
        cerr << "Error: Unable to open item.txt.\n";
        return;
    };

    string hLine;
    while (getline(inFileH, hLine)) {
        stringstream ss(hLine);
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

        // Check if the highest bidder matches the current user
        if (highestBidder == username) {
            cout << ID << "   | " << itemName
                 << " | " << category
                 << "            | " << (currentBid == startingBid ? "No Bids" : to_string(currentBid))
                 << "      | " << highestBidder
                 << " | " << asctime(localtime(&endTime));
        }
    }

    inFileH.close();

    int choice;
    cout << "\n1. View Item Listing Details\n2. View Active Bid Details\n3. Place a Bid\n4. View Ratings\n5. Rate a Buyer\n6. Rate a Seller\n7. Return to Main Menu\n";
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
            activeBids();

            break;
        }

        case 3: {
            cout << "Bidding!\n";

            string currBidderName, newItemId, pass;
            int bidAmount, rate;

            cout << "Please re-enter your Password: ";
            cin >> pass;

            Member* loadedMember = loadUser(username, pass);
            if (!loadedMember) {
                cout << "Invalid password or user not found.\n";
                break;
            }

            currBidderName = username;
            rate = loadedMember->getRating();
            double bidderCP = loadedMember->getCreditPoints();
            delete loadedMember;  // No longer needed after extracting required info

            cout << "\nEnter Auction ID you wish to bid: ";
            cin >> newItemId;
            cout << "\nEnter Your bid amount: ";
            cin >> bidAmount;

            // Load item details
            item* loadedItem = loadItem(newItemId);
            if (loadedItem) {
                // Create a Bidding instance with the item's attributes
                Bidding biddingInstance(
                    loadedItem->getItemName(),
                    loadedItem->getCategory(),
                    loadedItem->getStartingBid(),
                    loadedItem->getSeller(),
                    loadedItem->getMinBuyerRating(),
                    10.0 //temp bid increment value
                );

                // Attempt to place a bid using the Bidding instance
                if (biddingInstance.placeBid(currBidderName, bidAmount, bidderCP, rate)) {
                    loadedItem->setCurrentBid(biddingInstance.getCurrentBid());
                    loadedItem->setHighestBidder(biddingInstance.getHighestBidder());
                    loadedItem->updateListing(*loadedItem);  // Update item in the file
                }
                delete loadedItem;
            } else {
                cout << "Item not found for the given Auction ID.\n";
            }
            break;
        }

        case 4:{
            Rating userRating(username);
            userRating.displayRatings();
            break;
        }

        case 5:{
            double rating;
            string buyer;
            cout << "Enter Buyer's Username: ";
            cin >> buyer;
            cout << "Rate the Buyer (1-5): ";
            cin >> rating;
            while (rating < 1 || rating > 5) {
                cout << "Invalid rating. Please rate between 1 and 5: ";
                cin >> rating;
            }
            Rating buyerRating(buyer);
            buyerRating.rateBuyer(rating);
            cout << "Buyer has been rated successfully!\n";
            break;
        }

        case 6:{
            double rating;
            string seller;
            cout << "Enter Seller's Username: ";
            cin >> seller;
            cout << "Rate the Seller (1-5): ";
            cin >> rating;
            while (rating < 1 || rating > 5) {
                cout << "Invalid rating. Please rate between 1 and 5: ";
                cin >> rating;
            }
            Rating sellerRating(seller);
            sellerRating.rateSeller(rating);
            cout << "Seller has been rated successfully!\n";
            break;
        }

        case 7:
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
        cout << "----------------------------------";
        cout << "\nMember Menu:\n";
        cout << "----------------------------------\n";
        cout << "1. View Dashboard\n2. View Profile\n3. Create Item Listing\n4. Update Profile\n5. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            // 1. View Dashboard
            case 1:
                viewDashboard(member.getMemberName());
                break;
            //2. View Profile
            case 2:
                int profChoice;
                member.viewProfile();
                cout << "Enter your Choice: ";
                cin >> profChoice;
                switch(profChoice){
                    case 1:
                        topUpCredits(member);
                        break;
                    case 2:
                        updateProfile(member.getMemberName(), member.getPassword());    
                        break;
                    case 0:
                        cout << "Returning to main menu...";
                        break;
                }

                break;
            // 3. Create Item Listing   
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
                cin >> endTime;// just around 1737079211
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
                // cout << "Feature not implemented for this member type.\n";
                activeBids();
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
