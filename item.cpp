#include <iostream>
using std::string;
using namespace std;
#include <ctime>

class item
{
private:
    string itemName,category ,description, highestBidder;
    int startingBid,currentBid,minBuyerRating;
    time_t endTime,startTime,currentTime;

public:
    item(string itemName="",string category="",string description="",string highestBidder="",int startingBid=0,int currentBid=0,int minBuyerRating=0,time_t endTime=0,time_t startTime=0):itemName(itemName),category(category),description(description),highestBidder(highestBidder),startingBid(startingBid),currentBid(currentBid), minBuyerRating(minBuyerRating),endTime(endTime),startTime(startTime){
        
    }
    void setItemName(string itemName) { this->itemName = itemName; }
void setCategory(string category) { this->category = category; }
void setDescription(string description) { this->description = description; }
void setHighestBidder(string highestBidder) { this->highestBidder = highestBidder; }
void setStartingBid(int startingBid) { this->startingBid = startingBid; }
void setCurrentBid(int currentBid) { this->currentBid = currentBid; }
void setMinBuyerRating(int minBuyerRating) { this->minBuyerRating = minBuyerRating; }
void setEndTime(time_t endTime) { this->endTime = endTime; }
void setStartTime(time_t startTime) { this->startTime = startTime; }

    
    string getItemName() const { return itemName; }
string getCategory() const { return category; }
string getDescription() const { return description; }
string getHighestBidder() const { return highestBidder; }
int getStartingBid() const { return startingBid; }
int getCurrentBid() const { return currentBid; }
int getMinBuyerRating() const { return minBuyerRating; }
time_t getEndTime() const { return endTime; }
time_t getStartTime() const { return startTime; }

    void updateListing(){};
    void addBid(){};
    void concludeAuction(){};
};






    
int main()
{
    item i1("item1","category1","description1","highestBidder1",100,100,5,0,0);
    cout << i1.getItemName() << endl;
    return 0;
}

