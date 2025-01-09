#include <iostream>
#include <string>
#include <iomanip>


class Member {
private:
    std::string username;
    double buyerRating;
    double sellerRating;
    int buyerRatingCount;
    int sellerRatingCount;

public:
    // Constructor
<<<<<<< HEAD
    Member(std::string uname)
=======
    Member(string uname = "")
>>>>>>> c0748fa814ab0e3334a9b05c25d06d5db607b9b4
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
    }

    void rateSeller(double rating) {
        sellerRating = ((sellerRating * sellerRatingCount) + rating) / (sellerRatingCount + 1);
        sellerRatingCount++;
    }

    // Display Member's Rating Info
    void displayRatings() const {
        std::cout << username << "'s Ratings:\n";
        std::cout << "  Buyer Rating: " << std::fixed << std::setprecision(2) << buyerRating << "\n";
        std::cout << "  Seller Rating: " << std::fixed << std::setprecision(2) << sellerRating << "\n";
    }
}();

// int main() {
//     // Create two members
//     Member seller("JaneSeller");
//     Member buyer("JohnBuyer");

//     std::cout << "Initial Ratings:\n";
//     seller.displayRatings();
//     buyer.displayRatings();

//     // Simulate a transaction
//     std::cout << "\nTransaction Completed!\n";
//     std::cout << "Both parties can rate each other (1-5).\n";

//     double sellerToBuyerRating, buyerToSellerRating;

//     // Input seller rating the buyer
//     std::cout << "Seller rates Buyer (1-5): ";
//     cin >> sellerToBuyerRating;
//     while (sellerToBuyerRating < 1 || sellerToBuyerRating > 5) {
//         std::cout << "Invalid rating. Please rate between 1 and 5: ";
//         cin >> sellerToBuyerRating;
//     }

//     // Input buyer rating the seller
//     std::cout << "Buyer rates Seller (1-5): ";
//     cin >> buyerToSellerRating;
//     while (buyerToSellerRating < 1 || buyerToSellerRating > 5) {
//         std::cout << "Invalid rating. Please rate between 1 and 5: ";
//         cin >> buyerToSellerRating;
//     }

//     // Update ratings
//     seller.rateBuyer(sellerToBuyerRating);
//     buyer.rateSeller(buyerToSellerRating);

//     // Display updated ratings
//     std::cout << "\nUpdated Ratings:\n";
//     seller.displayRatings();
//     buyer.displayRatings();

//     return 0;
// }
