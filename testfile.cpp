#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class User {
private:
    string username;
    string password;
    int creditPoints;
    int itemsWon;

public:
    User(string uname = "", string pwd = "", int credits = 0, int won = 0)
        : username(uname), password(pwd), creditPoints(credits), itemsWon(won) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    int getCreditPoints() const { return creditPoints; }
    int getItemsWon() const { return itemsWon; }

    void setUsername(const string &uname) { username = uname; }
    void setPassword(const string &pwd) { password = pwd; }
    void setCreditPoints(int points) { creditPoints = points; }
    void setItemsWon(int won) { itemsWon = won; }

    void displayDashboard(const vector<string> &activeItems, const vector<string> &activeBids) {
        cout << "Account Overview: " << username << endl;
        cout << "-----------------------------------" << endl;
        cout << "Active Item Listings: " << activeItems.size() << " | Active Bids: " << activeBids.size() << endl;
        cout << "Items Won: " << itemsWon << " | Account Balance: " << creditPoints << " CP\n";

        cout << "\nYour active item listings:\n";
        cout << "No. | Name            | Category      | Current Bid | Current Bidder | End Date & Time\n";
        for (size_t i = 0; i < activeItems.size(); ++i) {
            cout << i + 1 << "   | " << activeItems[i] << endl;
        }

        cout << "\nYour active bids:\n";
        cout << "No. | Name            | Category      | Your Bid    | Current Bid    | End Date & Time\n";
        for (size_t i = 0; i < activeBids.size(); ++i) {
            cout << i + 1 << "   | " << activeBids[i] << endl;
        }
    }
};


class Item {
private:
    string itemName;
    string category;
    int currentBid;
    string highestBidder;
    int minBuyerRating;
    time_t endTime;

public:
    Item(string name = "", string cat = "", int bid = 0, string bidder = "", int minRating = 0, time_t end = 0)
        : itemName(name), category(cat), currentBid(bid), highestBidder(bidder), minBuyerRating(minRating), endTime(end) {}

    string getItemName() const { return itemName; }
    string getCategory() const { return category; }
    int getCurrentBid() const { return currentBid; }
    string getHighestBidder() const { return highestBidder; }
    int getMinBuyerRating() const { return minBuyerRating; }
    time_t getEndTime() const { return endTime; }

    void autoBid(const string &bidder, int bidIncrement, int bidLimit, int buyerRating) {
        if (buyerRating < minBuyerRating) {
            cout << "Buyer does not meet the minimum rating threshold.\n";
            return;
        }

        while (currentBid + bidIncrement <= bidLimit) {
            currentBid += bidIncrement;
            highestBidder = bidder;
            cout << "Bid automatically incremented to: " << currentBid << " by " << highestBidder << "\n";
        }
    }

    void displayItem() {
        cout << itemName << " | " << category << " | " << currentBid << " | " << highestBidder << " | "
             << asctime(localtime(&endTime));
    }
};

void welcomeScreen() {
    cout << "-----------------------------------\n";
    cout << "AUCTION APPLICATION\n";
    cout << "-----------------------------------\n";
    cout << "1. Guest\n2. Member\n3. Admin\n";
    cout << "Enter your choice: ";
}

void handleMember(User &user, vector<string> &activeItems, vector<string> &activeBids) {
    int choice;
    do {
        cout << "\nMember Menu:\n";
        cout << "1. View Dashboard\n2. Place a Bid\n3. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                user.displayDashboard(activeItems, activeBids);
                break;
            case 2: {
                int bidChoice;
                cout << "Select an item to bid on (enter item number): ";
                cin >> bidChoice;
                if (bidChoice > 0 && bidChoice <= activeItems.size()) {
                    int bidAmount;
                    cout << "Enter your bid amount: ";
                    cin >> bidAmount;
                    cout << "Bid placed successfully on item: " << activeItems[bidChoice - 1] << "\n";
                } else {
                    cout << "Invalid item selection.\n";
                }
                break;
            }
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

int main() {
    vector<string> activeItems = {
        "iPhone 13 Pro    | Electronics   | 350         | iAmMember12    | 16/12/2024 18:00",
        "Rare coin set    | Collectibles  | 300         | iAmMember4     | 20/12/2024 09:00",
        "PlayStation 4    | Games         | No bids     | No bidders     | 25/12/2024 08:00"
    };

    vector<string> activeBids = {
        "Sony headphones  | Electronics   | 100         | 250            | 20/12/2024 10:00",
        "Road bike        | Vehicles      | 300         | 310            | 23/12/2024 17:30"
    };

    int userType;
    welcomeScreen();
    cin >> userType;

    if (userType == 2) {
        string username, password;
        cout << "\nEnter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        User user(username, password, 300, 1);
        cout << "\nYou have successfully logged in.\n";
        handleMember(user, activeItems, activeBids);
    } else {
        cout << "Feature not implemented for this user type.\n";
    }

    return 0;
}
