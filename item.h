#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class item {
private:
    string ID;
    string itemName;
    string category;
    string description;
    string highestBidder;
    string seller;
    int startingBid;
    int currentBid;
    int minBuyerRating;
    time_t endTime;
    time_t startTime;
    time_t current_time;
public:
    item();
    item(string ID, string itemName, string category, string description, string highestBidder, string seller, int startingBid, int currentBid, int minBuyerRating, time_t endTime, time_t startTime);

    void setID(string ID);
    void setItemName(string itemName);
    void setCategory(string category);
    void setDescription(string description);
    void setHighestBidder(string highestBidder);
    void setSeller(string seller);
    void setStartingBid(int startingBid);
    void setCurrentBid(int currentBid);
    void setMinBuyerRating(int minBuyerRating);
    void setEndTime(time_t endTime);
    void setStartTime(time_t startTime);

    string getID();
    string getItemName();
    string getCategory();
    string getDescription();
    string getHighestBidder();
    string getSeller();
    int getStartingBid();
    int getCurrentBid();
    int getMinBuyerRating();
    time_t getEndTime();
    time_t getStartTime();

    void viewBidding();
    void updateListing(item i);
    void addBid(const string& bidderName, int bidAmount, int rating, const string& itemID);
    void concludeAuction(item i);
};
#endif // ITEM_H