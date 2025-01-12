#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


class bidding {
private:
    std::string itemName;
    std::string category;
    double minBid;
    double currentBid;
    std::string sellerUsername;
    std::string highestBidder;
    double minBuyerRating;
    bool isActive;

public:
    // Constructor
    bidding(std::string name, std::string cat, double minB, std::string seller, double minRating)
        : itemName(name), category(cat), minBid(minB), currentBid(0),
          sellerUsername(seller), highestBidder(""), minBuyerRating(minRating), isActive(true) {}

    // Getters
    std::string getItemName() const { return itemName; }
    double getCurrentBid() const { return currentBid; }
    std::string getHighestBidder() const { return highestBidder; }
    double getMinBuyerRating() const { return minBuyerRating; }
    bool getIsActive() const { return isActive; }

    // Place a bid
    bool placeBid(std::string buyer, double bidAmount, double buyerCP, double buyerRating) {
        if (!isActive) {
            std::cout << "This item is no longer active for bidding.\n";
            return false;
        }

        if (buyerRating < minBuyerRating) {
            std::cout << "Buyer does not meet the minimum rating threshold.\n";
            return false;
        }

        if (bidAmount <= currentBid) {
            std::cout << "Bid amount must be higher than the current highest bid.\n";
            return false;
        }

        if (bidAmount > buyerCP) {
            std::cout << "Insufficient credit points to place this bid.\n";
            return false;
        }

        currentBid = bidAmount;
        highestBidder = buyer;
        std::cout << "Bid placed successfully! Current highest bid: " << currentBid << " by " << highestBidder << "\n";
        return true;
    }
};

// int main() {
//     // Create an item
//     Item laptop("Laptop", "Electronics", 500, "JaneSeller", 3.0);

//     // Display initial item details
//     std::cout << "Item: " << laptop.getItemName() << "\n";
//     std::cout << "Minimum Rating Required: " << laptop.getMinBuyerRating() << "\n";
//     std::cout << "Current Highest Bid: " << laptop.getCurrentBid() << "\n\n";

//     // Simulate bidding
//     std::string buyer1 = "JohnBuyer";
//     double buyer1CP = 1000;  // Credit points
//     double buyer1Rating = 4.0;

//     std::cout << buyer1 << " tries to place a bid of 600.\n";
//     laptop.placeBid(buyer1, 600, buyer1CP, buyer1Rating);

//     std::string buyer2 = "AliceBuyer";
//     double buyer2CP = 700;  // Credit points
//     double buyer2Rating = 2.5;

//     std::cout << "\n" << buyer2 << " tries to place a bid of 700.\n";
//     laptop.placeBid(buyer2, 700, buyer2CP, buyer2Rating);

//     // Display updated item details
//     std::cout << "\nUpdated Item Details:\n";
//     std::cout << "Current Highest Bid: " << laptop.getCurrentBid() << "\n";
//     std::cout << "Highest Bidder: " << laptop.getHighestBidder() << "\n";

//     return 0;
// }
