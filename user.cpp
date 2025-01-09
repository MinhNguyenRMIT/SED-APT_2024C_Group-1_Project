#include <iostream>
#include <string>
#include <fstream> // For future implementation for saving user data into file
#include <sstream> // For future implementation for saving user data into file
#include <vector>
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

    bool isLoggedIn(const string &inputUsername, const string &inputPassword)
    {  
        ifstream inFile("users.txt");
        if (!inFile) 
        {
            cerr << "Err: Unable to open data file.\n";
            return false;
        };

        string line, uname, pwd, fname, mail, id;
        int phone, rate, credits;
        bool found = false;

        while (getline(inFile, line)) 
        {
            stringstream ss(line);
            
            getline(ss, uname, ',');
            getline(ss, pwd, ',');
            getline(ss, fname, ',');

            ss >> phone;
            ss.ignore();

            getline(ss, mail, ',');
            getline(ss, id, ',');

            ss >> rate;
            ss.ignore();
            ss >> credits;

            
            if (uname == inputUsername && pwd == inputPassword) 
            {
                // fill current user details
                username = uname;
                password = pwd;
                fullName = fname;
                phoneNumber = phone;
                email = mail;
                idNumber = id;
                rating = rate;
                creditPoints = credits;
                
                inFile.close();
                return true;
            };
        };

        inFile.close();
        return false; 

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

        // Saving user information into text file 
        // NOTE: PLEASE REVIEW which type of file is used to save user information
        // >>> txt file as data file
        ofstream outFile("users.txt", ios::app); 
        if (outFile) {
            outFile << username << "," << password << "," << fullName << "," << phoneNumber << "," << email << "," << idNumber << "," << rating << "," << creditPoints << "\n";
            cout << "Registration complete!" << endl;
        }
        else
        {
            cerr << "Error: Unable to save user information to file.\n";
        };
        outFile.close();
    };

    void viewProfile()
    {
        ifstream inFile("users.txt");
        if (!inFile) 
        {
            cerr << "Err: Unable to open data file.\n";
        };

        string line, uname, pwd, fname, mail, id;
        int phone, rate, credits;
        bool found = false;

        while (getline(inFile, line)) 
        {
            stringstream ss(line);
            
            getline(ss, uname, ',');
            getline(ss, pwd, ',');
            getline(ss, fname, ',');

            ss >> phone;
            ss.ignore();

            getline(ss, mail, ',');
            getline(ss, id, ',');

            ss >> rate;
            ss.ignore();
            ss >> credits;

            if (uname == username && pwd == password) 
            {
                found = true;

                cout << "Profile Information:" << "\n";

                cout << "Username: " << uname << "\n";
                cout << "Full Name: " << fname << "\n";
                cout << "Phone Number: " << phone << "\n";
                cout << "Email: " << mail << "\n";
                cout << "ID Number: " << id << "\n";
                cout << "Rating: " << rate << "\n";
                cout << "Credit Points: " << credits << "\n";

                break;
            }
        };

        if (!found) 
        {
            cout << "Err: User has not registered or does not exist in database!\n";
        }

        inFile.close();

    };

    // method of updating profile was written based on this source:
    // https://stackoverflow.com/questions/34507989/update-and-delete-data-from-file-in-c 
    void updateProfile()
    {
        cout << "Update Profile Information:" << endl;
        cout << "1. Full Name\n2. Phone Number\n3. Email\n4. Password" << endl;

        int choice;
        cin >> choice;
        cin.ignore(); 

        switch (choice) 
        {
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
                return;
        };

        ifstream inFile("users.txt");
        ofstream tempFile("temp.txt");
        if (!inFile || !tempFile) 
        {
        cerr << "Err: Unable to open data file.\n";
        return;
        }

        string line, uname, pwd;
        while (getline(inFile, line)) 
        {
            stringstream ss(line);
            getline(ss, uname, ',');
            getline(ss, pwd, ',');

            if (uname == username && pwd == password) {
                // Update the logged-in user's record
                tempFile << username << "," << password << "," << fullName << "," << phoneNumber << "," << email << "," << idNumber << "," << rating << "," << creditPoints << "\n";
            } else {
                // Write other records as-is
                tempFile << line << "\n";
            };
        };

        inFile.close();
        tempFile.close();

        remove("users.txt");
        rename("temp.txt", "users.txt");

        cout << "Profile updated successfully!" << endl;
    };
};

//TEST MAIN
// int main() {
//     User currentUser;
//     bool isLoggedIn = false;

//     while (true) {
//         cout << "\n--- User Menu ---\n";
//         if (!isLoggedIn) {
//             cout << "1. Register\n";
//             cout << "2. Login\n";
//             cout << "0. Exit\n";
//         } else {
//             cout << "1. View Profile\n";
//             cout << "2. Update Profile\n";
//             cout << "3. Logout\n";
//             cout << "0. Exit\n";
//         }

//         int choice;
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 if (!isLoggedIn) {
//                     // Register new user
//                     cout << "\n--- Register ---\n";
//                     currentUser.registerUser();
//                     break;
//                 } else {
//                     // View Profile
//                     cout << "\n--- Profile ---\n";
//                     currentUser.viewProfile();
//                 }
//                 break;

//             case 2:
//                 if (!isLoggedIn) {
//                     // Login
//                     cout << "\n--- Login ---\n";
//                     string inputUsername, inputPassword;
//                     cout << "Enter Username: ";
//                     cin >> inputUsername;
//                     cout << "Enter Password: ";
//                     cin >> inputPassword;

//                     isLoggedIn = isLoggedIn = currentUser.isLoggedIn(inputUsername, inputPassword);
                    
//                     //testing isLoggedIn() status
//                     if (isLoggedIn) {
//                         cout << "Login successful!\n";
//                     } else {
//                         cout << "Invalid username or password. Please try again.\n";
//                     }

//                 } else {
//                     // Update Profile
//                     cout << "\n--- Update Profile ---\n";
//                     currentUser.updateProfile();
//                 }
//                 break;

//             case 3:
//                 if (isLoggedIn) {
//                     // Logout
//                     cout << "\n--- Logout ---\n";
//                     isLoggedIn = false;
//                     cout << "You have successfully logged out.\n";
//                 } else {
//                     cout << "Invalid option!\n";
//                 }
//                 break;

//             case 0:
//                 cout << "Exiting program. Goodbye!\n";
//                 return 0;

//             default:
//                 cout << "Invalid choice! Please try again.\n";
//         }
//     }
// };

