#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#include "member.cpp"
#include "user.cpp"
#include "admin-1.cpp"
#include "item.cpp"
#include "Rating and Bid/bidding.cpp"
#include "Rating and Bid/rating.cpp"

//TEST MAIN FOR USER CLASS SWITCH CASE
 int main() 
 {
    
    
    
     User currentUser;
     bool isLoggedIn = false;

//     
//     {
//         cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n" 
//         << "Semester 3 2024\n" 
//         << "AUCTION APPLICATION\n" 
//         << "\nInstructor: Dr Ling Huo Chong\n" 
//         << "Group: Group No 1.\n" 
//         << "S3979760, Pham Hieu Dat\n"
//         << "S3965654, Le Tuan Kiet\n"
//         << "S4066691, Le Van Chi Hoang\n"
//         << "S3915233, Nguyen Hoang Minh\n";

//         cout << "\n--- User Menu ---\n";

//         if (!isLoggedIn) 
//         {
//             cout << "1. Register\n";
//             cout << "2. Login\n";
//             cout << "0. Exit\n";
//         } 
//         else 
//         {
//             cout << "1. View Profile\n";
//             cout << "2. Update Profile\n";
//             cout << "3. Logout\n";
//             cout << "0. Exit\n";
//         }

         int choice;
         cout << "Enter your choice: ";
         cin >> choice;

         switch (choice) 
         {
             case 1:
                 if (!isLoggedIn) 
                 {
//                     // Register new user
                     cout << "\n--- Register ---\n";
                     currentUser.registerUser();
                     break;
                 } 
                 else 
                 {
//                      View Profile
                     cout << "\n--- Profile ---\n";
                     currentUser.viewProfile();
                 }
                 break;

             case 2:
                 if (!isLoggedIn) {
//                     // Login
                     cout << "\n--- Login ---\n";
                     string inputUsername, inputPassword;
                     cout << "Enter Username: ";
                     cin >> inputUsername;
                     cout << "Enter Password: ";
                     cin >> inputPassword;

                     isLoggedIn = isLoggedIn = currentUser.isLoggedIn(inputUsername, inputPassword);
                    
//                     testing isLoggedIn() status
                     if (isLoggedIn) {
                         cout << "Login successful!\n";
                     } else {
                         cout << "Invalid username or password. Please try again.\n";
                     }

                 } else {
                      //Update Profile
                     cout << "\n--- Update Profile ---\n";
                     currentUser.updateProfile();
                 }
                 break;

             case 3:
                 if (isLoggedIn) {
//                     // Logout
                     cout << "\n--- Logout ---\n";
                     isLoggedIn = false;
                     cout << "You have successfully logged out.\n";
                 } else {
                     cout << "Invalid option!\n";
                 }
                 break;
                 case 4:
                   cout << "\n--- item listing ---\n";
                    viewBidding();
                        
                     
                     break;
            case 5:
                if (isLoggedIn) {
                    cout << "\n--- Add Bid ---\n";
                    string bidderName;
                    int bidAmount;
                    int rating;
                    string itemID;
                    cout << "Enter bidder name: ";
                    cin >> bidderName;
                    cout << "Enter bid amount: ";
                    cin >> bidAmount;
                    cout << "Enter rating: ";
                    cin >> rating;
                    cout << "Enter item ID: ";
                    cin >> itemID;
                    item.addBid(bidderName, bidAmount, rating, itemID);
                } else {
                    cout << "You must be logged in to add a bid.\n";
                }
             case 0:
                 cout << "Exiting program. Goodbye!\n";
                 return 0;

             default:
                 cout << "Invalid choice! Please try again.\n";
         }
     };
