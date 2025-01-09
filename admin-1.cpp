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
void readUsers() {
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cerr << "Unable to open users.txt" << endl;
        return;
    }
    string line;
    while (getline(usersFile, line)) {
        cout << line << endl;
    }
    usersFile.close();
}

void readItems() {
    ifstream itemsFile("item.txt");
    if (!itemsFile) {
        cerr << "Unable to open items.txt" << endl;
        return;
    }
    string line;
    while (getline(itemsFile, line)) {
        cout << line << endl;
    }
    itemsFile.close();
}
int  main(){
    readItems();
    readUsers();
    return 0;

};