#include "item.cpp" 
#include "admin-1.cpp"
#include "Rating and Bid/Bidding.cpp"
#include "Rating and Bid/Rating.cpp"
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
    int creditPoints;
    int itemsWon;
    vector<item> itemsListed; // Use the `item` class for listed items
    vector<string> itemsBid; // Store IDs of items bid on

public:
    Member(string uname = "", string pwd = "", string fname = "", int phone = 0, string mail = "", int idNumber = 0, int rate = 0, int creditPoints = 0, int won = 0)
        : username(uname), password(pwd), fullName(fname), phoneNumber(phone), email(mail), id(idNumber), rating(rate), creditPoints(creditPoints), itemsWon(won) {}

    string getMembername() const { return username; }
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
    }

    void topUpCredits(int amount) {

        creditPoints += amount;
        cout << "Successfully added " << amount << " credit points.\n";
    }

    void createItemListing(string id, string name, string category, string description, int startingBid, int minBuyerRating) {
        time_t now = time(0);
        time_t endTime = now + (7 * 24 * 60 * 60); // Auction ends in 7 days
        item newItem(id, name, category, description, "", startingBid, startingBid, minBuyerRating, endTime, now);
        itemsListed.push_back(newItem);
        cout << "Item \"" << name << "\" has been listed successfully.\n";
    }

    void viewDashboard() {
    cout << "\n--- Dashboard ---\n";
    cout << "Credit Points: " << creditPoints << "\n";
    cout << "Rating: " << rating << "\n";

    cout << "\nYour active item listings:\n";
    cout << "No. | Name            | Category      | Current Bid | Current Bidder  | End Date & Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < itemsListed.size(); ++i) {
        item &itm = itemsListed[i];
        time_t endTime = itm.getEndTime();
        cout << itm.getID() << "   | "<< itm.getItemName() << " | " << itm.getCategory() << " | " << (itm.getCurrentBid() == itm.getStartingBid() ? "No Bids" : to_string(itm.getCurrentBid())) << " | " << itm.getHighestBidder()<< " | " << asctime(localtime(&endTime));
    }

    cout << "\nYour active bids:\n";
    cout << "No. | Name            | Category      | Your Bid    | Current Bid     | End Date & Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < itemsBid.size(); ++i) {
        item &itm = itemsListed[i];
        time_t endTime = itm.getEndTime();
        cout << itm.getID() << "   | "<< itm.getItemName() << " | " << itm.getCategory() << " | " << (itm.getCurrentBid() == itm.getStartingBid() ? "No Bids" : to_string(itm.getCurrentBid())) << " | " << itm.getHighestBidder()<< " | " << asctime(localtime(&endTime));
    }

    int choice;
    cout << "\n1. View Item Listing Details\n2. View Active Bid Details\n3. Return to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int itemID;
            cout << "Enter the number of the item listing to view details: ";
            cin >> itemID;
            if (itemID > 0 && itemID <= itemsListed.size()) {
                itemsListed[itemID - 1].viewBidding();
            } else {
                cout << "Invalid item selection.\n";
            }
            break;
        }
        case 2: {
            int bidID;
            cout << "Enter the number of the bid to view details: ";
            cin >> bidID;
            if (bidID > 0 && bidID <= itemsBid.size()) {
                item &itm = itemsListed[bidID - 1];
                itm.viewBidding();
            } else {
                cout << "Invalid bid selection.\n";
            }
            break;
        }
        case 3:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid option. Returning to main menu...\n";
    }
}

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
        outFile << uname << "," << pwd << "," << fname << ","
                << phone << "," << mail << "," << idNumber << ",3,,0\n";
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

void handleMember(Member &member) {
    int choice;
    do {
        cout << "\nMember Menu:\n";
        cout << "1. View Dashboard\n2. View Profile\n3. Create Item Listing\n4. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                member.viewDashboard();
                break;
            case 2:
                member.viewProfile();
                break;
            case 3: {
                string id, name, category, description;
                int startingBid, minBuyerRating;
                cout << "Enter Item ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Item Name: ";
                getline(cin, name);
                cout << "Enter Category: ";
                getline(cin, category);
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Starting Bid: ";
                cin >> startingBid;
                cout << "Enter Minimum Buyer Rating: ";
                cin >> minBuyerRating;

                member.createItemListing(id, name, category, description, startingBid, minBuyerRating);
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
