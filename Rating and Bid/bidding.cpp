#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

class Bidding {
private:
    std::string itemName;
    std::string category;
    double minBid;
    double currentBid;
    std::string sellerUsername;
    std::string highestBidder;
    double minBuyerRating;
    bool isActive;
    double bidIncrement;
    std::map<std::string, double> bidLimits; // Stores buyer's bid limits

public:
    // Constructor
    Bidding(std::string name, std::string cat, double minB, std::string seller, double minRating, double increment)
        : itemName(name), category(cat), minBid(minB), currentBid(minB),
          sellerUsername(seller), highestBidder(""), minBuyerRating(minRating),
          isActive(true), bidIncrement(increment) {}

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

        // Update item.txt
        updateItemFile();

        return true;
    }

    // Update item.txt file
    void updateItemFile() {
        std::ifstream inFile("item.txt");
        std::ofstream outFile("item_temp.txt");
        std::string line;

        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::vector<std::string> fields;
            std::string field;

            // Split the line by commas
            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            // Check if this is the item to update
            if (fields.size() > 1 && fields[1] == itemName) {
                fields[7] = std::to_string(currentBid); // Update currentBid
                fields[4] = highestBidder;             // Update highestBidder
            }

            // Write updated line to the new file
            for (size_t i = 0; i < fields.size(); ++i) {
                outFile << fields[i];
                if (i != fields.size() - 1) {
                    outFile << ",";
                }
            }
            outFile << "\n";
        }

        inFile.close();
        outFile.close();

        // Replace the old file with the updated file
        std::remove("item.txt");
        std::rename("item_temp.txt", "item.txt");
    }

    // Set bid limit
    bool setBidLimit(std::string buyer, double limit) {
        if (bidLimits.count(buyer) > 0) {
            std::cout << "You already have a bid limit set.\n";
            return false;
        }

        for (const auto& [otherBuyer, otherLimit] : bidLimits) {
            if (otherLimit == limit) {
                std::cout << "Bid limit conflicts with another buyer's limit. Suggested limit: " << limit + bidIncrement << "\n";
                return false;
            }
        }

        bidLimits[buyer] = limit;
        std::cout << "Bid limit set successfully for " << buyer << ": " << limit << "\n";
        return true;
    }

    // Automatically handle bids based on limits
    void handleAutomaticBids(std::string newBidder, double newBidAmount) {
        for (auto& [buyer, limit] : bidLimits) {
            if (buyer != newBidder && newBidAmount + bidIncrement <= limit && newBidAmount + bidIncrement > currentBid) {
                currentBid = newBidAmount + bidIncrement;
                highestBidder = buyer;
                std::cout << "Automatic bid placed for " << buyer << ": " << currentBid << "\n";
                updateItemFile();
                return;
            }
        }

        std::cout << "No automatic bids placed.\n";
    }
};

// int main() {
//     // Create an item
//     Bidding item("Laptop", "Electronics", 50, "JaneSeller", 3.0, 10);

//     // Set bid limits
//     item.setBidLimit("BuyerXXX", 90);
//     item.setBidLimit("BuyerYYY", 100);
//     item.setBidLimit("BuyerZZZ", 110);

//     // Simulate bidding
//     item.placeBid("BuyerYYY", 60, 1000, 4.0);
//     item.handleAutomaticBids("BuyerYYY", 60);

//     item.placeBid("BuyerZZZ", 80, 1000, 4.0);
//     item.handleAutomaticBids("BuyerZZZ", 80);

//     item.placeBid("BuyerWWW", 100, 1000, 4.0);
//     item.handleAutomaticBids("BuyerWWW", 100);

//     return 0;
// }
