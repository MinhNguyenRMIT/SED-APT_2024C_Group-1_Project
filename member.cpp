#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct Item {
    int itemID;
    string name;
    string category;
    string description;
    int startingBid;
    int highestBid;
    string highestBidder;
    bool isActive;

    Item(int id, string n, string cat, string desc, int startBid)
        : itemID(id), name(n), category(cat), description(desc),
          startingBid(startBid), highestBid(startBid), isActive(true), highestBidder("") {}
};

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
    float rating;
    vector<Item> itemsListed;
    vector<int> itemsBid; // Store item IDs for items this member has bid on

public:
    Member(string uname = "", string pwd = "", string fname = "", int phone = 0, string mail = "", int idNumber = 0, int rate = 3, int creditPoints = 0, int won = 0)
        : username(uname), password(pwd), fullName(fname), phoneNumber(phone), email(mail), id(idNumber), rating(rate), creditPoints(creditPoints), itemsWon(won) {}

    // Getters
    string getUsername() const { return username; }
    float getRating() const { return rating; }
    int getCreditPoints() const { return creditPoints; }

    // Add credit points
    void topUpCredits(int amount) {
        creditPoints += amount;
        cout << "Successfully added " << amount << " credit points. Current balance: " << creditPoints << "\n";
    }

    // Create a new item listing
    void createItemListing(int id, string name, string category, string description, int startingBid) {
        Item newItem(id, name, category, description, startingBid);
        itemsListed.push_back(newItem);
        cout << "Item \"" << name << "\" has been listed successfully.\n";
    }

    // View dashboard
    void viewDashboard() {
        cout << "\n--- Dashboard ---\n";
        cout << "Credit Points: " << creditPoints << "\n";
        cout << "Rating: " << rating << "\n";
        cout << "Credit Points: " << creditPoints << "\n";
        cout << "Items Won: " << itemsWon << "\n";
        cout << "-----------------------------------\n";

        cout << "\n1. Top up credits\n2. Update Proifle\n0. Exit\n";
    }

    // Place a bid on an item
    void placeBid(Item &item, int amount) {
        if (!item.isActive) {
            cout << "Item \"" << item.name << "\" is no longer active for bidding.\n";
            return;
        }

        if (amount > creditPoints) {
            cout << "Insufficient credit points to place a bid.\n";
            return;
        }

        if (amount <= item.highestBid) {
            cout << "Bid amount must be higher than the current highest bid (" << item.highestBid << ").\n";
            return;
        }

        // Place the bid
        item.highestBid = amount;
        item.highestBidder = username;
        creditPoints -= amount;

        // Track items the member has bid on
        if (find(itemsBid.begin(), itemsBid.end(), item.itemID) == itemsBid.end()) {
            itemsBid.push_back(item.itemID);
        }

        cout << "Successfully placed a bid of " << amount << " on item \"" << item.name << "\".\n";
    }

    // Save member details to file
    void saveToFile() {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << " " << creditPoints << " " << rating << "\n";
            file.close();
        } else {
            cerr << "Error: Unable to open file for saving user data.\n";
        }
    }

    // Load member details from file
    void loadFromFile() {
        ifstream file("users.txt");
        if (file.is_open()) {
            string u, p;
            int cp;
            float r;
            while (file >> u >> p >> cp >> r) {
                if (u == username) {
                    password = p;
                    creditPoints = cp;
                    rating = r;
                    break;
                }
            }
            file.close();
        } else {
            cerr << "Error: Unable to open file for loading user data.\n";
        }
    }
};
