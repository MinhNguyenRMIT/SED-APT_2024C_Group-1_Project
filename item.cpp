#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
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
    cout << "\n-------------------------------------------------------" << endl;
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
    cout << "-------------------------------------------------------\n" << endl;
}

item* loadItem(const string &itemId) {
    ifstream inFile("item.txt");
    if (!inFile) {
        cerr << "Error: Unable to open item.txt.\n";
        return nullptr;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string ID, itemName, category, description, highestBidder, seller;
        int startingBid, currentBid, minBuyerRating;
        time_t endTime, startTime;

        getline(ss, ID, ',');
        if (ID == itemId) {
            getline(ss, itemName, ',');
            getline(ss, category, ',');
            getline(ss, description, ',');
            getline(ss, highestBidder, ',');
            getline(ss, seller, ',');
            ss >> startingBid;
            ss.ignore(); 
            ss >> currentBid;
            ss.ignore();
            ss >> minBuyerRating;
            ss.ignore();
            ss >> endTime;
            ss.ignore();
            ss >> startTime;

            inFile.close();
            return new item(ID, itemName, category, description, highestBidder, seller, startingBid, currentBid, minBuyerRating, endTime, startTime);
        }
    }

    inFile.close();
    return nullptr;
}


void item::updateListing(item i) {
    ifstream inFile("item.txt");
    ofstream outFile("temp.txt");
    string line;

    if (!inFile || !outFile) {
        cerr << "Error: Unable to open file for updating.\n";
        return;
    }

    while (getline(inFile, line)) {
        stringstream ss(line);
        string ID;
        getline(ss, ID, ',');

        if (ID == i.getID()) {
            // Replace with updated item details
            outFile << i.ID << "," << i.itemName << "," << i.category << "," << i.description << ","
                    << i.highestBidder << "," << i.seller << "," << i.startingBid << "," 
                    << i.currentBid << "," << i.minBuyerRating << "," << i.endTime << "," 
                    << i.startTime << endl;
        } else {
            // Write the existing line as is
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    // Replace the old file with the updated file
    remove("item.txt");
    rename("temp.txt", "item.txt");
}



void item::addBid(const string& bidderName, int bidAmount, int rating, const string& itemID) {
    // Check if the item ID matches
    if (itemID != ID) {
        cout << "Item ID does not match." << endl;
        return;
    }

    // Check if the auction has ended
    if (difftime(endTime, current_time) <= 0) {
        cout << "Auction has ended." << endl;
        return;
    }

    // Check if the bid amount is valid
    if (bidAmount > currentBid) {
        // Check if the buyer meets the rating requirement
        if (rating >= minBuyerRating) {
            currentBid = bidAmount;
            highestBidder = bidderName;
            cout << "Bid placed successfully! Current highest bid: " << currentBid 
                 << " by " << highestBidder << endl;

            // Update the item listing file with the new bid details
            updateListing(*this);
        } else {
            cout << "You do not meet the minimum buyer rating requirement." << endl;
        }
    } else {
        cout << "Your bid is lower than or equal to the current bid." << endl;
    }
}
  

void item::concludeAuction(item i){
    if (localtime(&current_time) == localtime(&i.endTime)){
    cout<<"Auction has ended"<<endl;
    ifstream infile("item.txt");
    ofstream tempFile("temp.txt");
    string line;
    while (getline(infile, line)) {
        if (line.substr(0, line.find(',')) != i.ID) {
        tempFile << line << endl;
        }
    }
    infile.close();
    tempFile.close();
    remove("item.txt");
    rename("temp.txt", "item.txt");
        
    } else {
        cout<<"Auction has not ended"<<endl;
    };
};

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

void activeBids() {
    time_t current_time;
    time(&current_time);
    std::time(nullptr)  ;  
    ifstream file("item.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
            stringstream ss(line);
            string ID, itemName, category, description, highestBidder, seller;
            int startingBid, currentBid, minBuyerRating;
            time_t endTime, startTime;

            // Parse the line
            getline(ss, ID, ',');
            
            getline(ss, itemName, ',');
            getline(ss, category, ',');
            getline(ss, description, ',');
            getline(ss, highestBidder, ',');
            getline(ss, seller, ',');
            ss >> startingBid;
            ss.ignore();
            ss >> currentBid;
            ss.ignore();
            ss >> minBuyerRating;
            ss.ignore();
            ss >> endTime;
            ss.ignore();
            ss >> startTime;
            if (difftime(endTime, std::time(nullptr)) > 0) {
                string itemId;
                item* loadedItem = loadItem(itemId);
                if (loadedItem) {
                        loadedItem->viewBidding(); 
                    delete loadedItem;        
                }
            }
        }
        file.close();
    } else {
        cout << "Error opening file" << endl;
    }
}