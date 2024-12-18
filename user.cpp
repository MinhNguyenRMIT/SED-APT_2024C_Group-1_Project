#include <iostream>
using std::string;
class user
{
private:
   string username,password,fullname,email,idNumber;
   int phoneNumber,rating,creditPoint;
public:
    user(string username="",string password="",string fullname="",string email="",string idNumber="",int phoneNumber=0,int rating=0, int creditPoint=0):username(username),fullname(fullname),email(email),idNumber(idNumber),phoneNumber(phoneNumber),rating(rating),creditPoint(creditPoint){}
    ~user();
};

int main(){
}