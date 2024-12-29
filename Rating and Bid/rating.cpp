#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Member {
private:
    string username;
    double buyerRating;
    double sellerRating;
    int buyerRatingCount;
    int sellerRatingCount;

public:
    // Constructor
    Member(string uname)
        : username(uname), buyerRating(3.0), sellerRating(3.0),
          buyerRatingCount(0), sellerRatingCount(0) {}

    // Getters
    string getUsername() const { return username; }
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

    // Display Member Info
    void displayRatings() const {
        cout << username << "'s Ratings:\n";
        cout << "  Buyer Rating: " << fixed << setprecision(2) << buyerRating << "\n";
        cout << "  Seller Rating: " << fixed << setprecision(2) << sellerRating << "\n";
    }
};

int main() {
    // Create two members
    Member seller("JaneSeller");
    Member buyer("JohnBuyer");

    cout << "Initial Ratings:\n";
    seller.displayRatings();
    buyer.displayRatings();

    // Simulate a transaction
    cout << "\nTransaction Completed!\n";
    cout << "Both parties can rate each other (1-5).\n";

    double sellerToBuyerRating, buyerToSellerRating;

    // Input seller rating the buyer
    cout << "Seller rates Buyer (1-5): ";
    cin >> sellerToBuyerRating;
    while (sellerToBuyerRating < 1 || sellerToBuyerRating > 5) {
        cout << "Invalid rating. Please rate between 1 and 5: ";
        cin >> sellerToBuyerRating;
    }

    // Input buyer rating the seller
    cout << "Buyer rates Seller (1-5): ";
    cin >> buyerToSellerRating;
    while (buyerToSellerRating < 1 || buyerToSellerRating > 5) {
        cout << "Invalid rating. Please rate between 1 and 5: ";
        cin >> buyerToSellerRating;
    }

    // Update ratings
    seller.rateBuyer(sellerToBuyerRating);
    buyer.rateSeller(buyerToSellerRating);

    // Display updated ratings
    cout << "\nUpdated Ratings:\n";
    seller.displayRatings();
    buyer.displayRatings();

    return 0;
}
