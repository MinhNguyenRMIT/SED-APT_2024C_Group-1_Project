#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Item {
private:
    string itemName;
    string category;
    double minBid;
    double currentBid;
    string sellerUsername;
    string highestBidder;
    double minBuyerRating;
    bool isActive;

public:
    // Constructor
    Item(string name, string cat, double minB, string seller, double minRating)
        : itemName(name), category(cat), minBid(minB), currentBid(0),
          sellerUsername(seller), highestBidder(""), minBuyerRating(minRating), isActive(true) {}

    // Getters
    string getItemName() const { return itemName; }
    double getCurrentBid() const { return currentBid; }
    string getHighestBidder() const { return highestBidder; }
    double getMinBuyerRating() const { return minBuyerRating; }
    bool getIsActive() const { return isActive; }

    // Place a bid
    bool placeBid(string buyer, double bidAmount, double buyerCP, double buyerRating) {
        if (!isActive) {
            cout << "This item is no longer active for bidding.\n";
            return false;
        }

        if (buyerRating < minBuyerRating) {
            cout << "Buyer does not meet the minimum rating threshold.\n";
            return false;
        }

        if (bidAmount <= currentBid) {
            cout << "Bid amount must be higher than the current highest bid.\n";
            return false;
        }

        if (bidAmount > buyerCP) {
            cout << "Insufficient credit points to place this bid.\n";
            return false;
        }

        currentBid = bidAmount;
        highestBidder = buyer;
        cout << "Bid placed successfully! Current highest bid: " << currentBid << " by " << highestBidder << "\n";
        return true;
    }
};

int main() {
    // Create an item
    Item laptop("Laptop", "Electronics", 500, "JaneSeller", 3.0);

    // Display initial item details
    cout << "Item: " << laptop.getItemName() << "\n";
    cout << "Minimum Rating Required: " << laptop.getMinBuyerRating() << "\n";
    cout << "Current Highest Bid: " << laptop.getCurrentBid() << "\n\n";

    // Simulate bidding
    string buyer1 = "JohnBuyer";
    double buyer1CP = 1000;  // Credit points
    double buyer1Rating = 4.0;

    cout << buyer1 << " tries to place a bid of 600.\n";
    laptop.placeBid(buyer1, 600, buyer1CP, buyer1Rating);

    string buyer2 = "AliceBuyer";
    double buyer2CP = 700;  // Credit points
    double buyer2Rating = 2.5;

    cout << "\n" << buyer2 << " tries to place a bid of 700.\n";
    laptop.placeBid(buyer2, 700, buyer2CP, buyer2Rating);

    // Display updated item details
    cout << "\nUpdated Item Details:\n";
    cout << "Current Highest Bid: " << laptop.getCurrentBid() << "\n";
    cout << "Highest Bidder: " << laptop.getHighestBidder() << "\n";

    return 0;
}
