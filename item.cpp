#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
#include "item.h"

item::item() : ID(""), itemName(""), category(""), description(""), highestBidder(""), seller(""), startingBid(0), currentBid(0), minBuyerRating(0), endTime(0), startTime(0) {
    time(&current_time);
}

item::item(string ID, string itemName, string category, string description, string highestBidder, string seller, int startingBid, int currentBid, int minBuyerRating, time_t endTime, time_t startTime)
    : ID(ID), itemName(itemName), category(category), description(description), highestBidder(highestBidder), seller(seller), startingBid(startingBid), currentBid(currentBid), minBuyerRating(minBuyerRating), endTime(endTime), startTime(startTime) {
    time(&current_time);
}

void item::setID(string ID) { this->ID = ID; }
void item::setItemName(string itemName) { this->itemName = itemName; }
void item::setCategory(string category) { this->category = category; }
void item::setDescription(string description) { this->description = description; }
void item::setHighestBidder(string highestBidder) { this->highestBidder = highestBidder; }
void item::setSeller(string seller) { this->seller = seller; }
void item::setStartingBid(int startingBid) { this->startingBid = startingBid; }
void item::setCurrentBid(int currentBid) { this->currentBid = currentBid; }
void item::setMinBuyerRating(int minBuyerRating) { this->minBuyerRating = minBuyerRating; }
void item::setEndTime(time_t endTime) { this->endTime = endTime; }
void item::setStartTime(time_t startTime) { this->startTime = startTime; }

string item::getID() { return ID; }
string item::getItemName() { return itemName; }
string item::getCategory() { return category; }
string item::getDescription() { return description; }
string item::getHighestBidder() { return highestBidder; }
string item::getSeller() {return seller;}
int item::getStartingBid() { return startingBid; }
int item::getCurrentBid() { return currentBid; }
int item::getMinBuyerRating() { return minBuyerRating; }
time_t item::getEndTime() { return endTime; }
time_t item::getStartTime() { return startTime; }

void item::viewBidding() {
    cout << "-------------------------------------------------------" << endl;
    cout << "Item ID: " << ID << endl;
    cout << "Item Name: " << itemName << endl;
    cout << "Category: " << category << endl;
    cout << "Description: " << description << endl;
    cout << "Highest Bidder: " << highestBidder << endl;
    cout << "Seller: " << seller << endl;
    cout << "Starting Bid: " << startingBid << endl;
    cout << "Current Bid: " << currentBid << endl;
    cout << "Minimum Buyer Rating: " << minBuyerRating << endl;
    cout << "End Time: " << ctime(&endTime);
    cout << "Start Time: " << ctime(&startTime);
    cout << "-------------------------------------------------------" << endl;
}

void item::updateListing(item i) {
    ofstream file;
    file.open("item.txt", ios::app);
    if (file.is_open()) {
        file << i.ID << "," << i.itemName << "," << i.category << "," << i.description << "," << i.highestBidder << "," << i.seller << "," << i.startingBid << "," << i.currentBid << "," << i.minBuyerRating << "," << i.endTime << "," << i.startTime << endl;
        file.close();
    } else {
        cout << "Error opening file" << endl;
    }
}

void item::addBid(const string& bidderName, int bidAmount, int rating, const string& itemID) {
    if (itemID == ID && localtime(&current_time) < localtime(&endTime)) {
        if (bidAmount > currentBid && rating >= minBuyerRating) {
            currentBid = bidAmount;
            highestBidder = bidderName;
        } else if (bidAmount > currentBid && rating < minBuyerRating) {
            cout << "You do not meet the minimum buyer rating requirement" << endl;
        } else if (bidAmount <= currentBid) {
            cout << "Your bid is lower than the current bid" << endl;
        }
    } else if (itemID != ID) {
        cout << "Item ID does not match" << endl;
    } else if (localtime(&current_time) >= localtime(&endTime)) {
        cout << "Auction has ended" << endl;
    }
}

void item::concludeAuction(item i) {
    if (localtime(&current_time) == localtime(&i.endTime)) {
        cout << "Auction has ended" << endl;
    }
}

void viewBidding() {
    ifstream file("item.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error opening file" << endl;
    }
}

// int main()
// {
//     // item zero("0","0","0","0","0","0",0,0,0,0,0);
//     item aiyesg("2","item2","category2","description2","bidder2","bidder1",200,200,3,1610000000,1600000000);
//     // item item3("3","item3","category3","description3","bidder3","bidder4",300,300,2,1610000000,1600000000);
    
//     aiyesg.addBid("bidder5", 250, 4, "3");   
//     // item3.addBid("bidder6", 350, 3, "2");
//     // aiyesg.updateListing(aiyesg);
//     // item3.updateListing(item3);

//     // zero.viewBidding();
//     aiyesg.viewBidding();
    
//     return 0;
// }
