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

// //TEST MAIN FOR USER CLASS SWITCH CASE

void viewDashboard() {
    cout << "\n--- Dashboard ---\n";

    cout << "\nYour active item listings:\n";
    cout << "No. | Name            | Category      | Current Bid | Current Bidder  | End Date & Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
   

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

        case 3:
            cout << "Bidding!";
            break;

        case 4:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid option. Returning to main menu...\n";
            break;

    } 
}

void handleMember(Member &member) {
    int choice;
    do {
        cout << "\nMember Menu:\n";
        cout << "1. View Dashboard\n2. View Profile\n3. Create Item Listing\n4. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                viewDashboard();
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
            case 4:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}



//NEW TEST MAIN
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



// //     
// //     {
// //         cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n" 
// //         << "Semester 3 2024\n" 
// //         << "AUCTION APPLICATION\n" 
// //         << "\nInstructor: Dr Ling Huo Chong\n" 
// //         << "Group: Group No 1.\n" 
// //         << "S3979760, Pham Hieu Dat\n"
// //         << "S3965654, Le Tuan Kiet\n"
// //         << "S4066691, Le Van Chi Hoang\n"
// //         << "S3915233, Nguyen Hoanh Minh\n";

// //         cout << "\n--- User Menu ---\n";

// //         if (!isLoggedIn) 
// //         {
// //             cout << "1. Register\n";
// //             cout << "2. Login\n";
// //             cout << "0. Exit\n";
// //         } 
// //         else 
// //         {
// //             cout << "1. View Profile\n";
// //             cout << "2. Update Profile\n";
// //             cout << "3. Logout\n";
// //             cout << "0. Exit\n";
// //         }

//          int choice;
//          cout << "Enter your choice: ";
//          cin >> choice;

//          switch (choice) 
//          {
//              case 1:
//                  if (!isLoggedIn) 
//                  {
// //                     // Register new user
//                      cout << "\n--- Register ---\n";
//                      currentUser.registerUser();
//                      break;
//                  } 
//                  else 
//                  {
// //                      View Profile
//                      cout << "\n--- Profile ---\n";
//                      currentUser.viewProfile();
//                  }
//                  break;

//              case 2:
//                  if (!isLoggedIn) {
// //                     // Login
//                      cout << "\n--- Login ---\n";
//                      string inputUsername, inputPassword;
//                      cout << "Enter Username: ";
//                      cin >> inputUsername;
//                      cout << "Enter Password: ";
//                      cin >> inputPassword;

//                      isLoggedIn = isLoggedIn = currentUser.isLoggedIn(inputUsername, inputPassword);
                    
// //                     testing isLoggedIn() status
//                      if (isLoggedIn) {
//                          cout << "Login successful!\n";
//                      } else {
//                          cout << "Invalid username or password. Please try again.\n";
//                      }

//                  } else {
//                       //Update Profile
//                      cout << "\n--- Update Profile ---\n";
//                      currentUser.updateProfile();
//                  }
//                  break;

//              case 3:
//                  if (isLoggedIn) {
// //                     // Logout
//                      cout << "\n--- Logout ---\n";
//                      isLoggedIn = false;
//                      cout << "You have successfully logged out.\n";
//                  } else {
//                      cout << "Invalid option!\n";
//                  }
//                  break;
//                  case 4:
//                    cout << "\n--- item listing ---\n";
//                     viewBidding();
                        
                     
//                      break;
//             case 5:
//                 if (isLoggedIn) {
//                     cout << "\n--- Add Bid ---\n";
//                     string bidderName;
//                     int bidAmount;
//                     int rating;
//                     string itemID;
//                     cout << "Enter bidder name: ";
//                     cin >> bidderName;
//                     cout << "Enter bid amount: ";
//                     cin >> bidAmount;
//                     cout << "Enter rating: ";
//                     cin >> rating;
//                     cout << "Enter item ID: ";
//                     cin >> itemID;
//                     item.addBid(bidderName, bidAmount, rating, itemID);
//                 } else {
//                     cout << "You must be logged in to add a bid.\n";
//                 }
//              case 0:
//                  cout << "Exiting program. Goodbye!\n";
//                  return 0;

//              default:
//                  cout << "Invalid choice! Please try again.\n";
//          }
//      };
