#include <iostream>
using std::string;
using namespace std;
class user
{
private:
   string username,password,fullname,email,idNumber;
   int phoneNumber,rating;
public:
    user(string username="",string password="",string fullname="",string email="",string idNumber="",int phoneNumber=0,int rating=0):username(username),fullname(fullname),email(email),idNumber(idNumber),phoneNumber(phoneNumber),rating(rating){}
    ~user();
};

int main(){
}