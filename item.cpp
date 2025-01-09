#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

template <typename T>
void saveToFile(const string& filename, const T& data) {
    ofstream file;
    file.open(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << data << endl;
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

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
        ofstream file;
        file.open("item.txt", ios::app);
        if (file.is_open()) {
            if (i.ID == ID) {
            string line;
            ifstream infile("item.txt");
            bool idExists = false;
            while (getline(infile, line)) {
                if (line.substr(0, line.find(',')) == i.ID) {
                idExists = true;
                break;
                }
            }
            infile.close();
            if (!idExists) {
                file << i.ID << "," << i.itemName << "," << i.category << "," << i.description << "," << i.highestBidder << "," << i.startingBid << "," << i.currentBid << "," << i.minBuyerRating << "," << i.endTime << "," << i.startTime << endl;
            } else {
                cout << "ID already exists in the file" << endl;
            }
            }
            
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
        
    }else{
        cout<<"Auction has not ended"<<endl;
    
    
};
};







// int main()
// {
   

//     item zero("0","0","0","0","0",0,0,0,0,0);
//     item aiyesg("2","item2","category2","description2","bidder2",200,200,3,1610000000,1600000000);
//     item item3("3","item3","category3","description3","bidder3",300,300,2,1610000000,1600000000);
    
//     aiyesg.addBid("bidder2", 250, 4, "2");   
//     item3.addBid("bidder3", 350, 3, "3");
//     aiyesg.updateListing(aiyesg);
//     item3.updateListing(item3);
    
   
//     return 0;

// }
