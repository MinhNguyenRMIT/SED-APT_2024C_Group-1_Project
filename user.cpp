#include <iostream>
#include <string>
//#include <fstream> //For future implementation for saving user data into file
//#include <sstream> //For future implementation for saving user data into file
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

        void setUsername(const string &uname) { username = uname; }
        void setPassword(const string &pwd) { password = pwd; }
        void setFullName(const string &fname) { fullName = fname; }
        void setPhoneNumber(int phone) { phoneNumber = phone; }
        void setEmail(const string &mail) { email = mail; }
        void setIdNumber(const string &id) { idNumber = id; }
        void setRating(int rate) { rating = rate; }
        void setCreditPoints(int points) { creditPoints = points; }

        string getUsername() const { return username; }
        string getPassword() const { return password; }
        string getFullName() const { return fullName; }
        string getEmail() const { return email; }
        int getPhoneNumber() const { return phoneNumber; }
        string getIdNumber() const { return idNumber; }
        int getRating() const { return rating; }
        int getCreditPoints() const { return creditPoints; }

    void login(const string &inputUsername, const string &inputPassword)
    {
        if (inputUsername == username && inputPassword == password) 
        {
            cout << "Login successful!" << endl;
        } 
        else 
        {
            cout << "Invalid username or password!" << endl;
        }
    };

    void registerUser()
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Full Name: ";

        cin.ignore(); 
        getline(cin, fullName);

        cout << "Enter Phone Number: ";
        cin >> phoneNumber;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter ID Number: ";
        cin >> idNumber;
        cout << "Registration complete!" << endl;
    };

    void viewProfile()
    {
        cout << "Profile Information:" << endl;
        cout << "Username: " << username << endl;
        cout << "Full Name: " << fullName << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        cout << "ID Number: " << idNumber << endl;
        cout << "Rating: " << rating << endl;
        cout << "Credit Points: " << creditPoints << endl;
    };

    void updateProfile()
    {
        cout << "Update Profile Information:" << endl;
        cout << "1. Full Name\n2. Phone Number\n3. Email\n4. Password" << endl;
        int choice;
        cin >> choice;
        cin.ignore(); // Handle leftover newline
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
            default:
                cout << "Invalid choice!" << endl;
        }
        cout << "Profile updated successfully!" << endl;
    };
};

//TEST MAIN

int main() {

    //User object
    User user("", "", "", 0, "", "");

    int choice;
    bool isLoggedIn = false;

    while (true) {
        cout << "\n--- User Menu ---\n";
        if (!isLoggedIn) {
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "0. Exit\n";
        } else {
            cout << "1. View Profile\n";
            cout << "2. Update Profile\n";
            cout << "3. Logout\n";
            cout << "0. Exit\n";
        }

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!isLoggedIn) {
                    // Register new user
                    cout << "\n--- Register ---\n";
                    user.registerUser();
                } else {
                    // View Profile
                    cout << "\n--- Profile ---\n";
                    user.viewProfile();
                }
                break;

            case 2:
                if (!isLoggedIn) {
                    // Login
                    cout << "\n--- Login ---\n";
                    string inputUsername, inputPassword;
                    cout << "Enter Username: ";
                    cin >> inputUsername;
                    cout << "Enter Password: ";
                    cin >> inputPassword;

                    if (inputUsername == user.getUsername() && inputPassword == user.getPassword()) {
                        cout << "Login successful!\n";
                        isLoggedIn = true;
                    } else {
                        cout << "Invalid username or password. Please try again.\n";
                    }
                } else {
                    // Update Profile
                    cout << "\n--- Update Profile ---\n";
                    user.updateProfile();
                }
                break;

            case 3:
                if (isLoggedIn) {
                    // Logout
                    cout << "\n--- Logout ---\n";
                    isLoggedIn = false;
                    cout << "You have successfully logged out.\n";
                } else {
                    cout << "Invalid option!\n";
                }
                break;

            case 0:
                cout << "Exiting program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
