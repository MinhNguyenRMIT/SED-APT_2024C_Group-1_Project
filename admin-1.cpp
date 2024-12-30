#include <iostream>
using std::string;
using namespace std;
#include <ctime>
#include <bits/stdc++.h>
class admin
{
    private:
        string adminUser = "admin";
        string adminPass = "admin123";

    public:
    
};

int  main(){
    ifstream in("user.txt");
    string text;
    while(getline(in,text)){
        
        
        cout<<text;


    }
    in.close();
    return 0;

};