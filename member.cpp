#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
          startingBid(startBid), highestBid(startBid), isActive(true) {}
};


class Member {
private:
    string username;
    string password;
    int creditPoints;
    float rating;
    vector<Item> itemsListed;
    vector<int> itemsBid;

public:
    Member(string u, string p) : username(u), password(p), creditPoints(0), rating(3.0) {}

    void topUpCredits(int amount) {
        creditPoints += amount;
        cout << "Successfully added " << amount << " credit points.\n";
    }


    void createItemListing(int id, string name, string category, string description, int startingBid) {
        Item newItem(id, name, category, description, startingBid);
        itemsListed.push_back(newItem);
        cout << "Item \"" << name << "\" has been listed successfully.\n";
    }

    void viewDashboard() {
        cout << "\n--- Dashboard ---\n";
        cout << "Credit Points: " << creditPoints << "\n";
        cout << "Rating: " << rating << "\n";

        cout << "\nItems Listed:\n";
        for (const auto &item : itemsListed) {
            cout << "ID: " << item.itemID << " | Name: " << item.name
                 << " | Highest Bid: " << item.highestBid << " | Active: "
                 << (item.isActive ? "Yes" : "No") << "\n";
        }

        cout << "\nItems Bid On:\n";
        for (const auto &bid : itemsBid) {
            cout << "Item ID: " << bid << "\n";
        }
    }

    void placeBid(Item &item, int amount) {
        if (amount <= creditPoints && amount > item.highestBid) {
            item.highestBid = amount;
            item.highestBidder = username;
            itemsBid.push_back(item.itemID);
            cout << "Successfully placed a bid of " << amount << " on item \"" << item.name << "\".\n";
        } else {
            cout << "Insufficient credit points or bid amount is too low.\n";
        }
    }

    void saveToFile() {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << " " << creditPoints << " " << rating << "\n";
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file("users.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                string u, p;
                int cp;
                float r;
                file >> u >> p >> cp >> r;
                if (u == username) {
                    password = p;
                    creditPoints = cp;
                    rating = r;
                    break;
                }
            }
            file.close();
        }
    }
};
