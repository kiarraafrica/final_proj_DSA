#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <cstring>

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class User {
private:
    struct user {
        string username;
        string password;
        float balance;
        float total_spent;
        float total_loss;
    };

    void createFilesIfNeeded() {
        // Check if the user info file exists, if not create it
        ifstream infile("user_info.txt");
        if (!infile.good()) {
            ofstream outfile("user_info.txt");
            outfile.close();
        }
        infile.close();

        // Check if the jackpot file exists, if not create it with an initial value of 100000
        ifstream jackpotFile("jackpot.txt");
        if (!jackpotFile.good()) {
            ofstream jackpotOut("jackpot.txt");
            jackpotOut << "Jackpot: 100000.0" << endl;
            jackpotOut.close();
        }
        jackpotFile.close();
    }

    // Read the jackpot value from the file
    float readJackpot() const {
        ifstream file("jackpot.txt");
        if (!file.is_open()) {
            cerr << "Error: Could not open jackpot file." << endl;
            return 0.0;
        }

        string line;
        getline(file, line);
        file.close();

        size_t pos = line.find("Jackpot: ");
        if (pos != string::npos) {
            return stof(line.substr(pos + 9));
        }
        return 0.0;
    }

    // Write the jackpot value to the file
    void writeJackpot(float jackpot) {
        ofstream file("jackpot.txt");
        if (!file.is_open()) {
            cerr << "Error: Could not open jackpot file." << endl;
            return;
        }

        file << "Jackpot: " << jackpot << endl;
        file.close();
    }

public:
    user current_user;

    User(float initial_balance = 0.0f) {
        current_user.balance = initial_balance;
        current_user.total_spent = 0.0f;
        current_user.total_loss = 0.0f;
        createFilesIfNeeded();
    }

    float getBalance() const {
        return current_user.balance;
    }

    float getTotalSpent() const {
        return current_user.total_spent;
    }

    float getTotalLoss() const {
        return current_user.total_loss;
    }

    void addBalance(float amount) {
        current_user.balance += amount;
        save_user();
    }

    void subtractBalance(float amount) {
        current_user.balance -= amount;
        save_user();
    }

    void addTotalSpent(float amount) {
        current_user.total_spent += amount;
        save_user();
    }

    void addTotalLoss(float amount) {
        current_user.total_loss += amount;
        save_user();
    }

    void setUsername(const string& username) {
        current_user.username = username;
    }

    string getUsername() const {
        return current_user.username;
    }

    string getPassword() const {
        return current_user.password;
    }

    void setPassword(const string& password) {
        current_user.password = password;
        save_user();
    }

    void save_user() {
        ifstream infile("user_info.txt");
        stringstream buffer;
        buffer << infile.rdbuf();
        infile.close();

        string content = buffer.str();
        stringstream new_content;
        bool user_found = false;

        string line;
        while (getline(buffer, line)) {
            if (line.find("Username: " + getUsername()) != string::npos) {
                line = "Username: " + getUsername() + " Password: " + getPassword() +
                       " Balance: " + to_string(getBalance()) +
                       " TotalSpent: " + to_string(getTotalSpent()) +
                       " TotalLoss: " + to_string(getTotalLoss());
                user_found = true;
            }
            new_content << line << "\n";
        }

        if (!user_found) {
            new_content << "Username: " + getUsername() + " Password: " + getPassword() +
                           " Balance: " + to_string(getBalance()) +
                           " TotalSpent: " + to_string(getTotalSpent()) +
                           " TotalLoss: " + to_string(getTotalLoss()) + "\n";
        }

        ofstream outfile("user_info.txt");
        outfile << new_content.str();
        outfile.close();
    }

    bool load_user(const string& username, const string& password) {
        ifstream file("user_info.txt");
        if (!file.is_open()) return false;

        string line;
        while (getline(file, line)) {
            if (line.find("Username: " + username) != string::npos) {
                size_t pos = line.find("Password: ");
                if (pos != string::npos) {
                    size_t password_end = line.find(" Balance: ", pos);
                    string stored_password = line.substr(pos + 10, password_end - (pos + 10));
                    if (stored_password == password) {
                        size_t balance_pos = line.find("Balance: ");
                        size_t total_spent_pos = line.find(" TotalSpent: ");
                        size_t total_loss_pos = line.find(" TotalLoss: ");
                        if (balance_pos != string::npos && total_spent_pos != string::npos && total_loss_pos != string::npos) {
                            float balance = stof(line.substr(balance_pos + 9, total_spent_pos - balance_pos - 9));
                            float total_spent = stof(line.substr(total_spent_pos + 12, total_loss_pos - total_spent_pos - 12));
                            float total_loss = stof(line.substr(total_loss_pos + 11));
                            setUsername(username);
                            current_user.password = stored_password;  // Set password directly to avoid unnecessary saving
                            current_user.balance = balance;
                            current_user.total_spent = total_spent;
                            current_user.total_loss = total_loss;
                            file.close();
                            return true;
                        }
                    }
                }
            }
        }
        file.close();
        return false;
    }

    bool changePassword(const string& currentPassword, const string& newPassword) {
        if (current_user.password == currentPassword) {
            current_user.password = newPassword;
            save_user();
            return true;
        }
        return false;
    }

    float getJackpot() const {
        return readJackpot();
    }

    void addToJackpot(float amount) {
        float current_jackpot = readJackpot();
        current_jackpot += amount;
        writeJackpot(current_jackpot);
    }
};

class UserManager {
public:
    void clear_screen() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void press_return() const {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPress Enter to return.";
        cin.get();
        clear_screen();
    }

    string get_username_input() const {
        string username;
        while (true) {
            cout << "Enter username: ";
            cin >> username;
            if (username == "x" || username == "X"){
                return "x";
            }
            if (username.length() >= 4) break;
            cout << "\nUsername must be at least 4 characters long.\n" << endl;
        }
        return username;
    }

    string get_password_input() const {
        string password;
        char ch;
        while ((ch = _getch()) != 13) { 
            if (ch == 8) { 
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        return password;
    }

    string get_confirmed_password() const {
        string password, confirm_password;
        while (true) {
            while (true) {
                cout << "Enter password: ";
                password = get_password_input();
                if (password.length() >= 6) break;
                cout << "\nPassword must be at least 6 characters long.\n" << endl;
            }

            cout << "Confirm password: ";
            confirm_password = get_password_input();

            if (password == confirm_password) break;
            cout << "\nPasswords do not match. Please try again.\n" << endl;
        }
        return password;
    }

    bool username_exists(const string& username) const {
        ifstream file("user_info.txt");
        if (!file.is_open()) return false;

        string line;
        while (getline(file, line)) {
            if (line.find("Username: " + username) != string::npos) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool verify_user(const string& username, const string& password) const {
        ifstream file("user_info.txt");
        if (!file.is_open()) return false;

        string line;
        while (getline(file, line)) {
            if (line.find("Username: " + username) != string::npos) {
                size_t pos = line.find("Password: ");
                if (pos != string::npos && line.substr(pos + 10) == password) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
        return false;
    }
};


class UserProfile {
private:
    User& user; 
    UserManager& userManager; 
public:
    UserProfile(User& user, UserManager& userManager)
        : user(user), 
        userManager(userManager) {}

    void user_profile() {
        int choice;
        while (true) {
            cout << "+---------------------------------------+" << endl;
            cout << "|             User Profile              |" << endl;
            cout << "+---------------------------------------+" << endl;
            cout << endl;
            cout << " Username:                 " << user.getUsername() << endl;
            cout << " Total amount spent:       $" << user.getTotalSpent() << endl;
            cout << " Total amount loss:        $" << user.getTotalLoss() << endl; 
            cout << " Current Balance:          $" << user.getBalance() << endl; 
            cout << endl;
            cout << "+---------------------------------------+" << endl;
            cout << "| [1] Change password                   |" << endl;
            cout << "| [2] Return to main menu               |" << endl;
            cout << "+---------------------------------------+" << endl;
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userManager.clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
                continue;
            }

            switch (choice) {
            case 1:
                userManager.clear_screen();
                change_password();
                break;
            case 2:
                userManager.clear_screen();
                return;
            default:
                userManager.clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
            }   
        }
    }

    void change_password() {
        cout << "Enter current password for verification: ";
        string old_password = userManager.get_password_input();

        if (user.load_user(user.getUsername(), old_password)) {
            userManager.clear_screen();
            cout << "+----------------------------------+" << endl;
            cout << "|         Change Password          |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << "\nCurrent Password: " << user.getPassword() << endl;
            cout << endl;
            string password = userManager.get_confirmed_password();
            user.changePassword(old_password, password);

            cout << "\nPassword successfully updated!" << endl;
            userManager.press_return();
            return;

        } else {
            userManager.clear_screen();
            cout << "Invalid username or password. Please try again." << endl;
            userManager.press_return();
        }
    }
};

class Wallet
{
private:
    User& user; 
    UserManager userManager;

public:
    Wallet(User &user) : user(user) {}

    void view_wallet() {
        int choice;

        while (true) {
            cout << "+----------------------------------------+" << endl;
            cout << "|                WALLET                  |" << endl;
            cout << "+----------------------------------------+\n" << endl;

            cout << "Current Balance: $" << user.getBalance() << endl;

            cout << "\n+----------------------------------------+" << endl;
            cout << "| [1] Top-Up                             |" << endl;
            cout << "| [2] Withdraw                           |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "| [3] Exit                               |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << " Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userManager.clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
                continue;
            }

            switch (choice) {
            case 1:
                userManager.clear_screen();
                top_up();
                break;
            case 2:
                userManager.clear_screen();
                withdraw();
                break;
            case 3:
                userManager.clear_screen();
                return;
            default:
                userManager.clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
            }
        }
    }

    void top_up() {
        float amount;

        while (true) {
            cout << "+----------------------------------------+" << endl;
            cout << "|                Top-Up                  |" << endl;
            cout << "+----------------------------------------+\n" << endl;

            cout << "Enter amount to top-up: ";

            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userManager.clear_screen();
                cout << "Please enter a valid amount.\n" << endl;
                continue;
            } else if (amount <= 0) {
                userManager.clear_screen();
                cout << "Amount must be greater than 0.\n" << endl;
                continue;
            } else {
                user.addBalance(amount);
                cout << "\nSuccessfully updated balance!" << endl;
                userManager.press_return();
                return;
            }
        }
    }

    void withdraw() {
        float amount;

        while (true) {
            cout << "+----------------------------------------+" << endl;
            cout << "|                Withdraw                |" << endl;
            cout << "+----------------------------------------+\n" << endl;

            cout << "Enter amount to withdraw: ";

            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userManager.clear_screen();
                cout << "Please enter a valid amount.\n" << endl;
                continue;
            } else if (amount <= 0) {
                userManager.clear_screen();
                cout << "Amount must be greater than 0.\n" << endl;
                continue;
            } else if (amount > user.getBalance()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userManager.clear_screen();
                cout << "You do not have enough balance. Please enter a valid amount.\n" << endl;
                continue;
            } else {
                user.subtractBalance(amount);
                cout << "\nSuccessfully updated balance!" << endl;
                userManager.press_return();
                return;
            }
        }
    }

};
