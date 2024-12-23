#include <iostream>
using std::string;
using namespace std;
#include <ctime>
class user
{
private:
   string username,password,fullname,email,idNumber;
   int phoneNumber;
public:
    user(string username="",string password="",string fullname="",string email="",string idNumber="",int phoneNumber=0):username(username),fullname(fullname),email(email),idNumber(idNumber),phoneNumber(phoneNumber){}
    ~user();
};

class member
{
private:
    int creditPoint,rating;

public:
    member(int creditPoint=0,int rating=0):creditPoint(creditPoint),rating(rating){}
    member();
};
