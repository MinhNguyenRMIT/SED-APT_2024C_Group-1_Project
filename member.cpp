// #include "item.cpp" 
// #include "item.h"
// #include "admin-1.cpp"
// #include "Rating and Bid/Bidding.cpp"
// #include "Rating and Bid/Rating.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>


using namespace std;

class Member {
private:
    string username;
    string password;
    string fullName;
    int phoneNumber;
    string email;
    int id;
    int rating;
    double creditPoints;
    int itemsWon;
    // vector<item> itemsListed; // Use the `item` class for listed items
    // vector<string> itemsBid; // Store IDs of items bid on

public:
    Member(string uname = "", string pwd = "", string fname = "", int phone = 0, string mail = "", int idNumber = 0, int rate = 0, double creditPoints = 0.0, int won = 0)
        : username(uname), password(pwd), fullName(fname), phoneNumber(phone), email(mail), id(idNumber), rating(rate), creditPoints(creditPoints), itemsWon(won) {}

    string getMemberName() const { return username; }
    string getPassword() const { return password; }
    string getFullName() const { return fullName; }
    string getEmail() const { return email; }
    int getPhoneNumber() const { return phoneNumber; }
    int getCreditPoints() const { return creditPoints; }
    int getItemsWon() const { return itemsWon; }

    void setMembername(const string &uname) { username = uname; }
    void setPassword(const string &pwd) { password = pwd; }
    void setFullName(const string &fname) { fullName = fname; }
    void setPhoneNumber(int phone) { phoneNumber = phone; }
    void setEmail(const string &mail) { email = mail; }
    void setRating(int rate) { rating = rate; }
    void setCreditPoints(int points) { creditPoints = points; }
    void setItemsWon(int won) { itemsWon = won; }

    void viewProfile() const {
        cout << "\n--- Profile Information ---\n";
        cout << "Username: " << username << "\n";
        cout << "Full Name: " << fullName << "\n";
        cout << "Phone Number: " << phoneNumber << "\n";
        cout << "Email: " << email << "\n";
        cout << "ID Number: " << id << "\n";
        cout << "Rating: " << rating << "\n";
        cout << "Credit Points: " << creditPoints << "\n";
        cout << "Items Won: " << itemsWon << "\n";
        cout << "-----------------------------------\n";

        cout << "\n1. Top up credits \n0. Exit";
    }

    // void createItemListing(string id, string name, string category, string description, int startingBid, int minBuyerRating) {
    //     time_t now = time(0);
    //     time_t endTime = now + (7 * 24 * 60 * 60); // Auction ends in 7 days
    //     item newItem(id, name, category, description, "", startingBid, startingBid, minBuyerRating, endTime, now);
    //     itemsListed.push_back(newItem);
    //     cout << "Item \"" << name << "\" has been listed successfully.\n";
    // }

    

    // void placeBid(item &itm, int amount) {
    //     if (amount <= creditPoints && amount > itm.getCurrentBid()) {
    //         itm.setCurrentBid(amount);
    //         itm.setHighestBidder(username);
    //         itemsBid.push_back(itm.getID());
    //         cout << "Successfully placed a bid of " << amount << " on item \"" << itm.getItemName() << "\".\n";
    //     } else {
    //         cout << "Insufficient credit points or bid amount is too low.\n";
    //     }
    // }

    // void placeBidding(Bidding &bidding, double amount, double buyerRating) {
    //     if (bidding.placeBid(username, amount, creditPoints, buyerRating)) {
    //         creditPoints -= amount;
    //     }
    // }
};

Member* loadUser(const string &username, const string &password) {
    ifstream inFile("users.txt");
    if (!inFile) {
        cerr << "Error: Unable to open users.txt.\n";
        return nullptr;
    }

    string line, uname, pwd;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, uname, ',');
        getline(ss, pwd, ',');

        if (uname == username && pwd == password) {
            string fullName, email;
            int idNumber, phoneNumber, rating, creditPoints;

            getline(ss, fullName, ',');
            ss >> phoneNumber;
            ss.ignore();
            getline(ss, email, ',');
            ss >> idNumber;
            ss >> rating;
            ss.ignore();
            ss >> creditPoints;

            inFile.close();
            return new Member(uname, pwd, fullName, phoneNumber, email, idNumber, rating, creditPoints);
        }
    }
    inFile.close();
    return nullptr;
}

bool isLoggedIn(const string &inputUsername, const string &inputPassword) {
    ifstream inFile("users.txt");
    if (!inFile) {
        cerr << "Error: Unable to open users.txt for reading.\n";
        return false;
    }

    string line, username, password;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');

        if (username == inputUsername && password == inputPassword) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

void login(const string &username, const string &password) {
    if (isLoggedIn(username, password)) {
        cout << "Login successful!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void registerUser() {
    cout << "\n--- Register New Member ---\n";
    string uname, pwd, fname, mail;
    int phone, idNumber;

    cout << "Enter Username: ";
    cin >> uname;
    cout << "Enter Password: ";
    cin >> pwd;
    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, fname);
    cout << "Enter Phone Number: ";
    cin >> phone;
    cout << "Enter Email: ";
    cin >> mail;
    cout << "Enter ID Number: ";
    cin >> idNumber;

    ofstream outFile("users.txt", ios::app);
    if (outFile) {
        outFile << uname << "," << pwd << "," << fname << "," << phone << "," << mail << "," << idNumber << ",3,0.0,0\n";
        cout << "Registration successful!\n";
    } else {
        cerr << "Error: Unable to save member information to file.\n";
    }
    outFile.close();
}

void welcomeScreen() {
    
    cout << "-----------------------------------\n";
    cout << "AUCTION APPLICATION\n";
    cout << "-----------------------------------\n";
    cout << "1. Guest\n2. Member\n3. Admin\n4. Register as Member\n0. Exit\n";
    cout << "Enter your choice: ";
}

// void topUpCredits(Member &member) {
//     double currCP = member.getCreditPoints();
//     currCP += 1.0;
//     member.getCreditPoints = currCP;
//     cout << "Successfully added 1 credit point.\n";
// }




