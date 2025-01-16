// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include <ctime>
// #include <iomanip>

// using namespace std;

// class User {
// private:
//     string username;
//     string password;
//     string fullName;
//     int phoneNumber;
//     string email;
//     int id;
//     int rating;
//     int creditPoints;
//     int itemsWon;

// public:
//     User(string uname = "", string pwd = "", string fname = "", int phone = 0, string mail = "", int idNumber = 0, int rate = 0, int credits = 0, int won = 0)
//         : username(uname), password(pwd), fullName(fname), phoneNumber(phone), email(mail), id(idNumber), rating(rate), creditPoints(credits), itemsWon(won) {}

//     string getUsername() const { return username; }
//     string getPassword() const { return password; }
//     string getFullName() const { return fullName; }
//     string getEmail() const { return email; }
//     int getPhoneNumber() const { return phoneNumber; }
//     int getCreditPoints() const { return creditPoints; }
//     int getItemsWon() const { return itemsWon; }

//     void setUsername(const string &uname) { username = uname; }
//     void setPassword(const string &pwd) { password = pwd; }
//     void setFullName(const string &fname) { fullName = fname; }
//     void setPhoneNumber(int phone) { phoneNumber = phone; }
//     void setEmail(const string &mail) { email = mail; }
//     void setRating(int rate) { rating = rate; }
//     void setCreditPoints(int points) { creditPoints = points; }
//     void setItemsWon(int won) { itemsWon = won; }

//     void displayDashboard(const vector<string> &activeItems, const vector<string> &activeBids) {
//         cout << "Account Overview: " << username << endl;
//         cout << "-----------------------------------" << endl;
//         cout << "Active Item Listings: " << activeItems.size() << " | Active Bids: " << activeBids.size() << endl;
//         cout << "Items Won: " << itemsWon << " | Account Balance: " << creditPoints << " CP\n";

//         cout << "\nYour active item listings:\n";
//         cout << "No. | Name            | Category      | Current Bid | Current Bidder | End Date & Time\n";
//         for (size_t i = 0; i < activeItems.size(); ++i) {
//             cout << i + 1 << "   | " << activeItems[i] << endl;
//         }

//         cout << "\nYour active bids:\n";
//         cout << "No. | Name            | Category      | Your Bid    | Current Bid    | End Date & Time\n";
//         for (size_t i = 0; i < activeBids.size(); ++i) {
//             cout << i + 1 << "   | " << activeBids[i] << endl;
//         }
//     }

//     void viewProfile() const {
//     cout << "\n--- Profile Information ---\n";
//     cout << "Username: " << username << "\n";
//     cout << "Full Name: " << fullName << "\n";
//     cout << "Phone Number: " << phoneNumber << "\n";
//     cout << "Email: " << email << "\n";
//     cout << "ID Number: " << id << "\n";
//     cout << "Rating: " << rating << "\n";
//     cout << "Credit Points: " << creditPoints << "\n";
//     cout << "Items Won: " << itemsWon << "\n";
//     cout << "-----------------------------------\n";
// }

// };

// User* loadUser(const string& username, const string& password) {
//     ifstream inFile("users.txt");
//     if (!inFile) {
//         cerr << "Error: Unable to open users.txt.\n";
//         return nullptr;
//     }

//     string line, uname, pwd;
//     while (getline(inFile, line)) {
//         stringstream ss(line);
//         getline(ss, uname, ',');
//         getline(ss, pwd, ',');

//         if (uname == username && pwd == password) {
//             string fullName, email;
//             int idNumber, phoneNumber, rating, creditPoints;

//             getline(ss, fullName, ',');
//             ss >> phoneNumber;
//             ss.ignore();
//             getline(ss, email, ',');
//             ss >> idNumber;
//             ss >> rating;
//             ss.ignore();
//             ss >> creditPoints;

//             inFile.close();
//             return new User(uname, pwd, fullName, phoneNumber, email, idNumber, rating, creditPoints);
//         }
//     }
//     inFile.close();
//     return nullptr; 
// }

// bool isLoggedIn(const string& inputUsername, const string& inputPassword) {
//     ifstream inFile("users.txt");
//     if (!inFile) {
//         cerr << "Error: Unable to open users.txt for reading.\n";
//         return false;
//     }

//     string line, username, password;
//     while (getline(inFile, line)) {
//         stringstream ss(line);
//         getline(ss, username, ',');
//         getline(ss, password, ',');

//         if (username == inputUsername && password == inputPassword) {
//             inFile.close();
//             return true;
//         }
//     }

//     inFile.close();
//     return false;
// }

// void login(string username, string password) {
//     if (isLoggedIn(username, password) == true) {
//         cout << "Login successful!\n";
//     } else {
//         cout << "Invalid username or password.\n";
//     }
// }

// void registerUser() {
//     cout << "\n--- Register New User ---\n";
    
//     string uname, pwd, fname, mail;
//     int phone, idNumber;

//     cout << "Enter Username: ";
//     cin >> uname;
//     cout << "Enter Password: ";
//     cin >> pwd;
//     cout << "Enter Full Name: ";
//     cin.ignore();
//     getline(cin, fname);
//     cout << "Enter Phone Number: ";
//     cin >> phone;
//     cout << "Enter Email: ";
//     cin >> mail;
//     cout << "Enter ID Number: ";
//     cin >> idNumber;

//     ofstream outFile("users.txt", ios::app);
//     if (outFile) {
//         outFile << uname << "," << pwd << "," << fname << "," 
//                 << phone << "," << mail << "," << idNumber << ",0,0,0\n";
//         cout << "Registration successful!\n";
//     } else {
//         cerr << "Error: Unable to save user information to file.\n";
//     }
//     outFile.close();
// }


// // class Item {
// // private:
// //     string itemName;
// //     string category;
// //     int currentBid;
// //     string highestBidder;
// //     int minBuyerRating;
// //     time_t endTime;
// // public:
// //     Item(string name = "", string cat = "", int bid = 0, string bidder = "", int minRating = 0, time_t end = 0)
// //         : itemName(name), category(cat), currentBid(bid), highestBidder(bidder), minBuyerRating(minRating), endTime(end) {}
// //     string getItemName() const { return itemName; }
// //     string getCategory() const { return category; }
// //     int getCurrentBid() const { return currentBid; }
// //     string getHighestBidder() const { return highestBidder; }
// //     int getMinBuyerRating() const { return minBuyerRating; }
// //     time_t getEndTime() const { return endTime; }

// //     void autoBid(const string &bidder, int bidIncrement, int bidLimit, int buyerRating) {
// //         if (buyerRating < minBuyerRating) {
// //             cout << "Buyer does not meet the minimum rating threshold.\n";
// //             return;
// //         }

// //         while (currentBid + bidIncrement <= bidLimit) {
// //             currentBid += bidIncrement;
// //             highestBidder = bidder;
// //             cout << "Bid automatically incremented to: " << currentBid << " by " << highestBidder << "\n";
// //         }
// //     }

// //     void displayItem() {
// //         cout << itemName << " | " << category << " | " << currentBid << " | " << highestBidder << " | "
// //              << asctime(localtime(&endTime));
// //     }
// // };

// void welcomeScreen() {
//     cout << "-----------------------------------\n";
//     cout << "AUCTION APPLICATION\n";
//     cout << "-----------------------------------\n";
//     cout << "1. Guest\n2. Member\n3. Admin\n4. Register as Member\n0. Exit\n";
//     cout << "Enter your choice: ";
// }

// void handleMember(User &user, vector<string> &activeItems, vector<string> &activeBids) {
//     int choice;
//     do {
//         cout << "\nMember Menu:\n";
//         cout << "1. View Dashboard\n2. View Profile\n3. Place a Bid\n4. Log Out\n";
//         cout << "Enter your choice: ";
//         cin >> choice;
//         switch (choice) {
//             case 1:
//                 user.displayDashboard(activeItems, activeBids);
//                 break;
//             case 2:
//                 user.viewProfile();
//                 break;
//             case 3: {
//                 int bidChoice;
//                 cout << "Select an item to bid on (enter item number): ";
//                 cin >> bidChoice;
//                 if (bidChoice > 0 && bidChoice <= activeItems.size()) {
//                     int bidAmount;
//                     cout << "Enter your bid amount: ";
//                     cin >> bidAmount;
//                     cout << "Bid placed successfully on item: " << activeItems[bidChoice - 1] << "\n";
//                 } else {
//                     cout << "Invalid item selection.\n";
//                 }
//                 break;
//             }
//             case 4:
//                 cout << "Logging out...\n";
//                 break;
//             default:
//                 cout << "Invalid choice. Please try again.\n";
//         }
//     } while (choice != 4);
// }



// int main() {
//     vector<string> activeItems = {
//         "iPhone 13 Pro    | Electronics   | 350         | iAmMember12    | 16/12/2024 18:00",
//         "Rare coin set    | Collectibles  | 300         | iAmMember4     | 20/12/2024 09:00",
//         "PlayStation 4    | Games         | No bids     | No bidders     | 25/12/2024 08:00"
//     };

//     vector<string> activeBids = {
//         "Sony headphones  | Electronics   | 100         | 250            | 20/12/2024 10:00",
//         "Road bike        | Vehicles      | 300         | 310            | 23/12/2024 17:30"
//     };


//     int userType;

//     while (true) { 
//         welcomeScreen();
//         cin >> userType;

//         switch(userType) {
//             case 1:
//                 cout << "Feature not implemented for this user type.\n";
//                 break; 

//             case 2: {
//                 string username, password;
//                 cout << "\nEnter username: ";
//                 cin >> username;
//                 cout << "Enter password: ";
//                 cin >> password;

//                 // User user(username, password, 300, 1);
//                 // cout << "\nYou have successfully logged in.\n";
//                 // handleMember(user, activeItems, activeBids);

//                 login(username, password);
//                 if (isLoggedIn){
//                     User* user = loadUser(username, password);
//                     handleMember(*user, activeItems, activeBids);
//                 } else {
//                     cout << "Invalid username or password.\n";
//                 }
//                 break;
//             }
                
//             case 3:
//                 cout << "Feature not implemented for this user type.\n"; 

//             case 4:
//                 registerUser();
//                 break;

//             case 0: { 
//                 cout << "Exiting program. Goodbye!\n";
//                 return 0;
//             }

//             default: {
//                 cout << "Invalid option. Please try again.\n";
//                 break;
//             }
//         }    
//     }

//     return 0;
// }
