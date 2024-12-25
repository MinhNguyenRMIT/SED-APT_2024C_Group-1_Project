#include <iostream>
using std::string;
using namespace std;
#include <ctime>
class item
{
private:
    string itemName,category ,description, highestBidder;
    int startingBid,currentBid,minBuyerRating;
    time_t endTime,startTime;

public:
    item(string itemName="",string category="",string description="",string highestBidder="",int startingBid=0,int currentBid=0,int minBuyerRating=0,time_t endTime,time_t startTime):itemName(itemName),category(category),description(description),highestBidder(highestBidder),startingBid(startingBid),currentBid(currentBid), minBuyerRating(minBuyerRating),endTime(endTime),startTime(startTime){}
    ~item();
};

void updateListing(){};
void addBid(){};
void concludeAuttion(){};