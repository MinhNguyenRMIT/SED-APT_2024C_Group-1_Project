#include <iostream>
#include <string>
//#include <fstream>
//#include <sstream>
using namespace std;

class User
{
    private:
        string username;
        string password;
        string fullName;
        int phoneNumber;
        string email;
        string idNumber;
        int rating;
        int creditPoints;

    public:
        User(string uname = "", string pwd = "", string fname = "", int phone = 0, string mail = "", string id = "", int rate = 0, int credits = 0)
        : username(uname), password(pwd), fullName(fname), phoneNumber(phone), email(mail), idNumber(id), rating(rate), creditPoints(credits) {}

    void login(){};

    void registerUser(){};

    void viewProfile(){};

    void updateProfile(){};
};