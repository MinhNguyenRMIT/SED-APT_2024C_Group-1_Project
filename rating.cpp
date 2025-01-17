#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

class Rating {
private:
    std::string username;
    double buyerRating;
    double sellerRating;
    int buyerRatingCount;
    int sellerRatingCount;

public:
    // Constructor
    Rating(std::string uname)
        : username(uname), buyerRating(3.0), sellerRating(3.0),
          buyerRatingCount(0), sellerRatingCount(0) {}

    // Getters
    std::string getUsername() const { return username; }
    double getBuyerRating() const { return buyerRating; }
    double getSellerRating() const { return sellerRating; }

    // Update Ratings
    void rateBuyer(double rating) {
        buyerRating = ((buyerRating * buyerRatingCount) + rating) / (buyerRatingCount + 1);
        buyerRatingCount++;
        updateUserFile("buyer");
    }

    void rateSeller(double rating) {
        sellerRating = ((sellerRating * sellerRatingCount) + rating) / (sellerRatingCount + 1);
        sellerRatingCount++;
        updateUserFile("seller");
    }

    // Display Member's Rating Info
    void displayRatings() const {
        std::cout << username << "'s Ratings:\n";
        std::cout << "  Buyer Rating: " << std::fixed << std::setprecision(2) << buyerRating << "\n";
        std::cout << "  Seller Rating: " << std::fixed << std::setprecision(2) << sellerRating << "\n";
    }

    // Update users.txt file
    void updateUserFile(const std::string& role) {
        std::ifstream inFile("users.txt");
        std::ofstream outFile("user_temp.txt");
        std::string line;

        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::vector<std::string> fields;
            std::string field;

            // Split the line by commas
            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            // Check if this is the user to update
            if (fields.size() > 1 && fields[0] == username) {
                if (role == "buyer") {
                    fields[6] = std::to_string(buyerRating); // Update buyer rating
                } else if (role == "seller") {
                    fields[6] = std::to_string(sellerRating); // Update seller rating
                }
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
        std::remove("users.txt");
        std::rename("user_temp.txt", "users.txt");
    }
};
