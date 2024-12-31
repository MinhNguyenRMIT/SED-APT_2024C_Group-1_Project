#include <iostream>
using std::string;
using namespace std;
#include <ctime>

class item
{
private:
    string itemName,category ,description, highestBidder,ID;
    int startingBid,currentBid,minBuyerRating;
    time_t endTime,startTime,currentTime;
    time(&currentTime);

public:
    item(string ID,string itemName="",string category="",string description="",string highestBidder="",int startingBid=0,int currentBid=0,int minBuyerRating=0,time_t endTime=0,time_t startTime=0):ID(ID),itemName(itemName),category(category),description(description),highestBidder(highestBidder),startingBid(startingBid),currentBid(currentBid), minBuyerRating(minBuyerRating),endTime(endTime),startTime(startTime){
        
    }
    void setID(string ID) { this->ID = ID; }
    void setItemName(string itemName) { this->itemName = itemName; }
    void setCategory(string category) { this->category = category; }
    void setDescription(string description) { this->description = description; }
    void setHighestBidder(string highestBidder) { this->highestBidder = highestBidder; }
    void setStartingBid(int startingBid) { this->startingBid = startingBid; }
    void setCurrentBid(int currentBid) { this->currentBid = currentBid; }
    void setMinBuyerRating(int minBuyerRating) { this->minBuyerRating = minBuyerRating; }
    void setEndTime(time_t endTime) { this->endTime = endTime; }
    void setStartTime(time_t startTime) { this->startTime = startTime; }

    string getID()  { return ID; }
    string getItemName()  { return itemName; }
    string getCategory()  { return category; }
    string getDescription()  { return description; }
    string getHighestBidder()  { return highestBidder; }
    int getStartingBid()  { return startingBid; }
    int getCurrentBid()  { return currentBid; }
    int getMinBuyerRating()  { return minBuyerRating; }
    time_t getEndTime()  { return endTime; }
    time_t getStartTime()  { return startTime; }

    void updateListing(item i){
        ofstream file;
        file.open("item.txt",ios::app);
        if (file.is_open())
        {
            file<<i.ID<<" "<<i.itemName<<" "<<i.category<<" "<<i.description<<" "<<i.highestBidder<<" "<<i.startingBid<<" "<<i.currentBid<<" "<<i.minBuyerRating<<" "<<i.endTime<<" "<<i.startTime<<endl;
            file.close();
        }
        

    };
void addBid(string bidderName, int bidAmount,int rating,string itemID){
    
    if (itemID==ID && localtime(&currentTime) < localtime(&endTime)){
        if(bidAmount>currentBid && rating>=minBuyerRating){
            currentBid = bidAmount;
            highestBidder = bidderName;
        }
        else if(bidAmount>currentBid && rating<minBuyerRating){
            cout<<"You do not meet the minimum buyer rating requirement"<<endl;
        }
        else if(bidAmount<=currentBid){
            cout<<"Your bid is lower than the current bid"<<endl;
    }
    }
    else if (itemID!=ID){
        cout<<"Item ID does not match"<<endl;
    }
    else if (localtime(&currentTime) >= localtime(&endTime)){
        cout<<"Auction has ended"<<endl;
    }

};
void concludeAuction(item i){
    if (localtime(&currentTime) == localtime(&i.endTime))
    {
        cout<<"Auction has ended"<<endl;
    }
    
    
};
};







int main()
{
    item i1("1","item1","category1","description1","bidder1",100,100,4,4000,0);
    time_t endTime = i1.getEndTime();
    cout << ctime(&endTime) << endl;
    updateListing(i1);
    return 0;

}

