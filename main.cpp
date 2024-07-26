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

class Lotto
{
private:
    User &user;
    UserManager &userManager;
    Wallet &wallet;

public:
    Lotto(User &user, UserManager &userManager, Wallet &wallet)
        : user(user), userManager(userManager), wallet(wallet) {}

    void instructions(){
        cout << "+----------------------------------------+" << endl;
        cout << "|              INSTRUCTIONS              |" << endl;
        cout << "+----------------------------------------+" << endl;
        cout << "\nObjective:\n" << endl;
        cout << "- The goal of the game is to match all 6 numbers of your bets with the 6 randomly" << endl;
        cout << " generated winning numbers." << endl;

        cout << "\nBetting:\n" << endl;
        cout << "- You will be prompted to enter 6 different bets." << endl;
        cout << "- Each bet must be a unique integer between 0 and the maximum number allowed." << endl;

        cout << "\nWinning Numbers:\n" << endl;
        cout << "- After entering your bets, the game will generate 6 random winning numbers." << endl;
        cout << "- These numbers are also unique and fall within the same range as your bets." << endl;

        cout << "\nMatching:\n" << endl;
        cout << "- The game will compare your bets with the winning numbers." << endl;
        cout << "- If all 6 of your bets match the winning numbers, you win!" << endl;
        cout << "- Otherwise, you lose." << endl;

        userManager.press_return();
    }

    void difficulty_menu(){
        int choice;

        while(true){
            cout << "+----------------------------------+" << endl;
            cout << "|        Difficulty Levels         | " << endl;
            cout << "+----------------------------------+" << endl;
            cout << "|                                  |" << endl;
            cout << "| [1] Easy         | 1 - 19 | $300 |" << endl;
            cout << "| [2] Intermediate | 1 - 39 | $200 |" << endl;
            cout << "| [3] Difficult    | 1 - 59 | $100 |" << endl;
            cout << "|                                  |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << "| [0] Cancel                       |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << "Choose difficulty: " ;

            if (!(cin >> choice)){
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                userManager.clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
                continue;
            }

            switch (choice){
                case 0:
                    userManager.clear_screen();
                    return;
                    break;
                case 1:
                    if (bet_balance_check(300)){
                        userManager.clear_screen();
                        cout << "+----------------------------------+" << endl;
                        cout << "|        EASY LEVEL: 1 - 19        |" << endl;
                        cout << "+----------------------------------+" << endl;
                        game_menu(19, 300);
                        user.addTotalSpent(300);
                    }
                    break;
                case 2:
                    if (bet_balance_check(200)){
                        userManager.clear_screen();
                        cout << "+----------------------------------+" << endl;
                        cout << "|     INTERMEDIATE LEVEL: 1 - 39   |" << endl;
                        cout << "+----------------------------------+" << endl;
                        game_menu(39, 200);
                        user.addTotalSpent(200);
                    }
                    break;
                case 3:
                    if (bet_balance_check(100)){
                        userManager.clear_screen();
                        cout << "+----------------------------------+" << endl;
                        cout << "|       DIFFICULT LEVEL: 1 - 59    |" << endl;
                        cout << "+----------------------------------+" << endl;
                        game_menu(59, 100);
                        user.addTotalSpent(100);
                    }
                    break;
                default:
                    userManager.clear_screen();
                    cout << "Please enter a valid choice from the menu.\n" << endl;
                    break;
            }
        }
    }

    bool bet_balance_check(int bet){
        if (user.getBalance() <  bet){
            userManager.clear_screen();
            cout << "Insufficient balance. You only have $" << user.getBalance() << " for a $" << bet << " bet.\n" << endl;
            return false;
        }
        return true;
    }

    void game_menu(int max_num, int bet) {
            srand((unsigned) time(NULL));

            bool result = game(max_num);
            if (result) {
                cout << ANSI_COLOR_RED << "\nCONGRATULATIONS!" << ANSI_COLOR_RESET << " You won $" << user.getJackpot() << "!" << endl;
                user.addBalance(user.getJackpot());
            } else {
                cout << "\nYou did not guess all of the winning numbers." << endl;
                cout << "You lose $" << bet << "." << endl;
                user.subtractBalance(bet);
                user.addTotalLoss(bet);
                user.addToJackpot(bet);
            }

            userManager.press_return();
            return;
        }

    bool game(int max_num) {
            int arr_bet[6];
            int arr_wnums[6];

            get_bets(arr_bet, max_num);

            if (!verify_bets(arr_bet, max_num)) {
                return false;
            }

            userManager.clear_screen();
            cout << "+----------------------------------------+" << endl;
            cout << "|                RESULTS                 |" << endl;
            cout << "+----------------------------------------+\n" << endl;

            cout << "BETS:" << endl;
            for (int i = 0; i < 6; i++) {
                cout << "[ " << arr_bet[i] << " ] ";
            }

            get_winning_numbers(arr_wnums, max_num);

            for (int s = 0; s < 6; s++) {
                cout << "[ " << arr_wnums[s] << " ] ";
            }
            cout << "\n\n+----------------------------------------+" << endl;

            return bet_num_matches(arr_bet, arr_wnums);
        }

    void get_bets(int arr_bet[], int max_num) const {
            cout << "\nEnter your bets: " << endl;
            for (int i = 0; i < 6; i++) {
                arr_bet[i] = get_unique_bet(arr_bet, i, max_num);
            }
        }

    int get_unique_bet(int arr[], int size, int max_num) const {
            int element;
            bool unique;
            bool valid;

            do {
                cout << "[" << size + 1 << "] -- ";
                valid = true;

                if (!(cin >> element)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nPlease enter a valid integer.\n" << endl;
                    valid = false;
                }

                if (valid && (element > max_num || element <= 0)) {
                    cout << "\nBets must be between 1 and " << max_num << ".\n" << endl;
                    valid = false;
                }

                if (valid) {
                    unique = is_unique(arr, size, element);
                    if (!unique) {
                        cout << "\nYou have already bet on this number. Duplicate bets are not allowed. Please enter a different bet.\n" << endl;
                    }
                }
            } while (!valid || !unique);

            return element;
        }

    bool is_unique(int arr[], int size, int element) const {
            for (int i = 0; i < size; ++i) {
                if (arr[i] == element) {
                    return false;
                }
            }
            return true;
        }

    bool verify_bets(int arr[], int max_num) {
            int choice;

            userManager.clear_screen();
            while (true) {
                cout << "+----------------------------------------+" << endl;
                cout << "|                  BETS                  | " << endl;
                cout << "+----------------------------------------+\n" << endl;
                for (int i = 0; i < 6; i++) {
                    cout << "[ " << arr[i] << " ] ";
                }

                cout << "\n\n+----------------------------------------+" << endl;
                cout << "| [1] Change a bet                       |" << endl;
                cout << "| [2] Finalize bets                      |" << endl;
                cout << "+----------------------------------------+" << endl;
                cout << "| [0] Cancel                             | " << endl;
                cout << "+----------------------------------------+" << endl;
                cout << "\nChoose option: ";

                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    userManager.clear_screen();
                    cout << "Please enter a valid choice from the menu.\n" << endl;
                    continue;
                }

                switch (choice) {
                    case 0:
                        userManager.clear_screen();
                        main_menu();
                        break;
                    case 1:
                        userManager.clear_screen();
                        change_bet(arr, max_num);
                        break;
                    case 2:
                        return true;
                    default:
                        userManager.clear_screen();
                        cout << "Invalid choice. Please enter 1 or 2.\n" << endl;
                        break;
                }
            }
        }

    void change_bet(int arr[], int max_num) {
        int index, new_bet;

        while (true) {
            display_bets(arr);

            cout << "\nEnter the position of the bet you want to change (enter 0 to cancel): ";

            if (!(cin >> index)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userManager.clear_screen();
                cout << "Please enter an integer.\n" << endl;
                continue;
            } 
            else if (index == 0) {
                userManager.clear_screen();
                return;  
            } 
            else if (index < 1 || index > 6) {
                userManager.clear_screen(); 
                cout << "Please enter a number between 1 and 6.\n" << endl;
                continue;
            }
            else{
                index--;
                cout << "\nEnter the new bet: ";
                if (!(cin >> new_bet) || new_bet < 0 || new_bet > max_num || !is_unique(arr, 6, new_bet)) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    userManager.clear_screen(); 
                    cout << "Invalid bet. Please enter a unique number between 0 and " << max_num << ".\n" << endl;
                    continue;
                }
                arr[index] = new_bet;
                userManager.clear_screen();
                break;
            }
        }
    }

    void display_bets(int arr[]) const {
            cout << "Your bets: " << endl;
            for (int j = 0; j < 6; j++) {
                cout << "[" << j + 1 << "] -- " << arr[j] << endl;
            }
        }

    void get_winning_numbers(int arr_wnums[], int max_num) const {
            cout << "\n\nWINNING NUMBERS:" << endl;

            for (int k = 0; k < 6; k++) {
                arr_wnums[k] = get_unique_num(arr_wnums, k, max_num);
            }
        }

    int get_unique_num(int arr[], int size, int max_num) const {
            int random_num;
            bool unique;
            do {
                random_num = 1 + rand() % max_num;
                unique = is_unique(arr, size, random_num);
            } while (!unique);
            return random_num;
        }

    bool bet_num_matches(int bets[], int nums[]) const {
            int match = 0;

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    if (bets[i] == nums[j]) {
                        match++;
                        break;
                    }
                }
            }

            return match == 6;
        }

    void main_menu(){
        int choice;

        while (true){
            cout << "+----------------------------------+" << endl;
            cout << "|        Welcome to Lotto!         |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << "          !!! Jackpot !!!" << endl;
            cout << "             $" << int(user.getJackpot())<< endl;
            cout << "+----------------------------------+" << endl;
            cout << "| Select an option:                |" << endl;
            cout << "| [1] Start the Game               |" << endl;
            cout << "| [2] Instructions                 |" << endl;
            cout << "| [3] View Wallet                  |" << endl;
            cout << "| [4] Return to Main Menu          |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << " Enter you choice: ";

            if (!(cin >> choice)){
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                userManager.clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
                continue;
            }

            switch (choice) {
                case 1:
                    userManager.clear_screen();
                    difficulty_menu();
                    break;
                case 2:
                    userManager.clear_screen();
                    instructions();
                    break;
                case 3:
                    userManager.clear_screen();
                    wallet.view_wallet();
                    break;
                case 4:
                    userManager.clear_screen();
                    return;
                    break;
                default:
                    userManager.clear_screen();
                    cout << "Please enter a valid choice from the menu.\n" << endl;
                    break;
            }
        }
    }
};
