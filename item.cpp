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
    item(string itemName="",string category="",string description="",string highestBidder="",int startingBid=0,int currentBid=0,int minBuyerRating=0,time_t endTime=0,time_t startTime=0):itemName(itemName),category(category),description(description),highestBidder(highestBidder),startingBid(startingBid),currentBid(currentBid), minBuyerRating(minBuyerRating),endTime(endTime),startTime(startTime){}
    ~item();
};

void updateListing(){};
void addBid(){};
void concludeAuction(){
    if tiempoActual > endTime
    {
        if currentBid > startingBid
        {
            //send email to highestBidder
            //send email to seller
        }
        else
        {
            //send email to seller
        }
    }
};
int main(int argc, char const *argv[])
{
    item("item1","category1","description1","highestBidder1",100,200,4,0,0);
    cout<<"Item created"<<endl;
    return 0;
}
