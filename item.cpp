#include <iostream>
#include <fstream>
#include <ctime>
using std::string;
using namespace std;

class item
{
private:
    string itemName,category ,description, highestBidder,ID;
    int startingBid,currentBid,minBuyerRating;
    time_t endTime, startTime, current_time;
    

public:
    item(string ID,string itemName="",string category="",string description="",string highestBidder="",int startingBid=0,int currentBid=0,int minBuyerRating=0,time_t endTime=0,time_t startTime=0):ID(ID),itemName(itemName),category(category),description(description),highestBidder(highestBidder),startingBid(startingBid),currentBid(currentBid), minBuyerRating(minBuyerRating),endTime(endTime),startTime(startTime){
     time(&current_time);   }




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

    

    void updateListing(item i) {
        ifstream infile("item.txt");
        ofstream outfile("item_temp.txt", ios::app);
        bool itemExists = false;
        if (infile.is_open() && outfile.is_open()) {
            string line;
            while (getline(infile, line)) {
                if (line.find(i.ID) != string::npos) {
                    cout << "Item with ID " << i.ID << " already exists." << endl;
                    itemExists = true;
                }
                outfile << line << endl;
            }
            if (!itemExists) {
                outfile << i.ID << "," << i.itemName << "," << i.category << "," << i.description << "," << i.highestBidder << "," << i.startingBid << "," << i.currentBid << "," << i.minBuyerRating << "," << i.endTime << "," << i.startTime << endl;
            }
            infile.close();
            outfile.close();
            remove("item.txt");
            rename("item_temp.txt", "item.txt");
        } else {
            cout << "Error opening file" << endl;
        }
    }
    void addBid(string bidderName, int bidAmount,int rating,string itemID){
    
    if (itemID==ID && localtime(&current_time) < localtime(&endTime)){
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
    else if (localtime(&current_time) >= localtime(&endTime)){
        cout<<"Auction has ended"<<endl;
    }

};
void concludeAuction(item i){
    if (localtime(&current_time) == localtime(&i.endTime))
    {
        cout<<"Auction has ended"<<endl;
    }
    
    
};
};







int main()
{
    item i1("1","item1","category1","description1","bidder1",100,100,4,4000,0);
    item i2("2","item2","category2","description2","bidder2",200,200,3,5000,0);
    item i3("3","item3","category3","description3","bidder3",300,300,2,6000,0);     
    i1.updateListing(i2);
    time_t endTime = i1.getEndTime();
    
    i1.updateListing(i1);
    return 0;

}

