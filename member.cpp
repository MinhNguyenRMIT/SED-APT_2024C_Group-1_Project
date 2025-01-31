#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class Member {
private:
    string username;
    string password;
    string fullName;
    int phoneNumber;
    string email;
    int id;
    float rating;
    int creditPoints;
    int itemsWon;

public:
    Member(string uname = "", string pwd = "", string fname = "", int phone = 0, string mail = "", int idNumber = 0, float rate = 3.0, int creditPoints = 0, int won = 0)
        : username(uname), password(pwd), fullName(fname), phoneNumber(phone), email(mail), id(idNumber), rating(rate), creditPoints(creditPoints), itemsWon(won) {}

    string getMemberName() const { return username; }
    string getPassword() const { return password; }
    string getFullName() const { return fullName; }
    string getEmail() const { return email; }
    double getRating() const { return rating; }
    int getPhoneNumber() const { return phoneNumber; }
    int getCreditPoints() const { return creditPoints; }
    int getItemsWon() const { return itemsWon; }

    void setMembername(const string &uname) { username = uname; }
    void setPassword(const string &pwd) { password = pwd; }
    void setFullName(const string &fname) { fullName = fname; }
    void setPhoneNumber(int phone) { phoneNumber = phone; }
    void setEmail(const string &mail) { email = mail; }
    void setRating(double rate) { rating = rate; }
    void setCreditPoints(int points) { creditPoints = points; }
    void setItemsWon(int won) { itemsWon = won; }

    void viewProfile() const {
        cout << "\n--- Profile Information ---\n";
        cout << "Username: " << username << "\n";
        cout << "Full Name: " << fullName << "\n";
        cout << "Phone Number: " << phoneNumber << "\n";
        cout << "Email: " << email << "\n";
        cout << "ID Number: " << id << "\n";
        cout << "Rating: " << rating << "\n";
        cout << "Credit Points: " << creditPoints << "\n";
        cout << "Items Won: " << itemsWon << "\n";
        cout << "-----------------------------------\n";

        cout << "\n1. Top up credits\n2. Update Proifle\n0. Exit\n";
    }
};

Member* loadUser(const string &username, const string &password) {
    ifstream inFile("users.txt");
    if (!inFile) {
        cerr << "Error: Unable to open users.txt.\n";
        return nullptr;
    }
    // Search through data file
    string line, uname, pwd;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, uname, ',');
        getline(ss, pwd, ',');

        // Load current user based on their logged in credentials
        if (uname == username && pwd == password) {
            string fullName, email;
            double rating;
            int idNumber, phoneNumber, creditPoints, itemsWon;

            getline(ss, fullName, ',');
            ss >> phoneNumber;
            ss.ignore();  
            getline(ss, email, ',');
            ss >> idNumber;
            ss.ignore();  
            ss >> rating; 
            ss.ignore();  
            ss >> creditPoints;
            ss.ignore();  
            ss >> itemsWon;

            return new Member(uname, pwd, fullName, phoneNumber, email, idNumber, rating, creditPoints, itemsWon);
        }
    }
    inFile.close();
    return nullptr;
}

bool isLoggedIn(const string &inputUsername, const string &inputPassword) {
    ifstream inFile("users.txt");
    if (!inFile) {
        cerr << "Error: Unable to open users.txt for reading.\n";
        return false;
    }

    string line, username, password;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');

        if (username == inputUsername && password == inputPassword) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

void login(const string &username, const string &password) {
    if (isLoggedIn(username, password)) {
        cout << "Login successful!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void registerUser() {
    cout << "\n--- Register New Member ---\n";
    string uname, pwd, fname, mail;
    int phone, idNumber;

    cout << "Enter Username: ";
    cin >> uname;
    cout << "Enter Password: ";
    cin >> pwd;
    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, fname);
    cout << "Enter Phone Number: ";
    cin >> phone;
    cout << "Enter Email: ";
    cin >> mail;
    cout << "Enter ID Number: ";
    cin >> idNumber;

    // Saving user information into text file 
    // NOTE: PLEASE REVIEW which type of file is used to save user information
    // >>> txt file as data file
    // Write new user data into file
    ofstream outFile("users.txt", ios::app);
    if (outFile) {
        outFile << uname << "," << pwd << "," << fname << "," << phone << "," << mail << "," << idNumber << ",3.0,0,0\n";
        cout << "Registration successful!\n";
    } else {
        cerr << "Error: Unable to save member information to file.\n";
    }
    outFile.close();
}

// method of updating profile was written based on this source:
// https://stackoverflow.com/questions/34507989/update-and-delete-data-from-file-in-c 
void updateProfile(const string &currentUsername, const string &currentPassword) {
    string fullName, phoneNumber, email, password;
    bool updated = false;

    cout << "\nUpdate Profile Information:\n";
    cout << "1. Full Name\n2. Phone Number\n3. Email\n4. Password\n0. Cancel\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore(); 

    // User's choice for which data field to change
    switch (choice) {
        case 1:
            cout << "Enter new Full Name: ";
            getline(cin, fullName);
            break;
        case 2:
            cout << "Enter new Phone Number: ";
            cin >> phoneNumber;
            break;
        case 3:
            cout << "Enter new Email: ";
            cin >> email;
            break;
        case 4:
            cout << "Enter new Password: ";
            cin >> password;
            break;
        case 0:
            cout << "Operation cancelled!\n";
            return;
        default:
            cout << "Invalid choice! Returning to menu...\n";
            return;
    }

    ifstream inFile("users.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error: Unable to open data file.\n";
        return;
    }

    // Searches user data based on credentials 
    string line, uname, pwd;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, uname, ',');
        getline(ss, pwd, ',');

        if (uname == currentUsername && pwd == currentPassword) {
            // Update specific fields based on user's choice
            string oldFullName, oldPhoneNumber, oldEmail, idNumber, rating, creditPoints;

            // Get current user's current information
            getline(ss, oldFullName, ',');
            getline(ss, oldPhoneNumber, ',');
            getline(ss, oldEmail, ',');
            getline(ss, idNumber, ',');
            getline(ss, rating, ',');
            getline(ss, creditPoints, ',');

            // Apply updated data depending on user's choice
            if (choice == 1) oldFullName = fullName;
            if (choice == 2) oldPhoneNumber = phoneNumber;
            if (choice == 3) oldEmail = email;
            if (choice == 4) pwd = password;

            // Write updated record into user.txt file
            tempFile << uname << "," << pwd << "," << oldFullName << "," 
                     << oldPhoneNumber << "," << oldEmail << "," 
                     << idNumber << "," << rating << "," << creditPoints << "\n";

            updated = true;
        } else {
            // Write unmodified records
            tempFile << line << "\n";
        }
    }

    inFile.close();
    tempFile.close();

    if (updated) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        cout << "Profile updated successfully!\n";
    } else {
        cout << "User not found or incorrect credentials.\n";
    }
}

void topUpCredits(Member member) {
    int currCP = member.getCreditPoints();
    currCP += 1;
    member.setCreditPoints(currCP);
    cout << "Successfully added 1 credit point.\n";
}
