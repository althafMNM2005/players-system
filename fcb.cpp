#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits> // for numeric_limits
using namespace std;

void login();
void registration();
void forgot();
void details();
void logout();
void displayPlayers();
void addPlayer();
void manageTeams();
void searchPlayers();

vector<string> loggedInUser;

void showMenu();

int main()
{
    showMenu();
    return 0;
}

void showMenu()
{
    int c;
    while (true)
    {
        cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
        cout << "\t\t\t~~~~Welcome to the Upcountry Warriors~~~~\n\n\n";
        cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~Menu~~~~~~~~~~~~~~~~~\n\n";
        cout << "\t| Press 1 to Login                    |\n";
        cout << "\t| Press 2 to Register                 |\n";
        cout << "\t| Press 3 if you forgot the password  |\n";
        cout << "\t| Press 4 to Exit                     |\n";
        cout << "\n\t\t\tPlease enter your choice: ";
        cin >> c;
        cout << endl;

        switch (c)
        {
            case 1:
                login();
                break;
            case 2:
                registration();
                break;
            case 3:
                forgot();
                break;
            case 4:
                cout << "\t\t\tThank you!\n\n";
                return;
            default:
                cout << "\t\t\tPlease select from the options given above.\n";
        }
    }
}

void login()
{
    int count = 0;
    string userid, password, id, pass;
    cout << "\t\t\tPlease enter the username and password:\n";
    cout << "\t\t\tUsername: ";
    cin >> userid;
    cout << "\t\t\tPassword: ";
    cin >> password;

    ifstream input("records.txt");

    if (!input)
    {
        cerr << "Unable to open file records.txt\n";
        return;
    }

    while (input >> id >> pass)
    {
        if (id == userid && pass == password)
        {
            count = 1;
            loggedInUser.push_back(userid);
            break;
        }
    }
    input.close();

    if (count == 1)
    {
        cout << userid << "\nYour login is successful!\nThanks for logging in!\n";
        int option;
        while (true)
        {
            cout << "\nMenu:\n";
            cout << "1. Details\n";
            cout << "2. Logout\n";
            cout << "3. Display players information\n";
            cout << "4. Add new players\n";
            cout << "5. Manage teams\n";
            cout << "6. Search players\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> option;

            switch (option)
            {
                case 1:
                    details();
                    break;
                case 2:
                    logout();
                    return;
                case 3:
                    displayPlayers();
                    break;
                case 4:
                    addPlayer();
                    break;
                case 5:
                    manageTeams();
                    break;
                case 6:
                    searchPlayers();
                    break;
                case 7:
                    cout << "Exiting...\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    else
    {
        cout << "\nLogin error\nPlease check your username and password\n";
    }
}

void registration()
{
    string ruserid, rpassword;
    cout << "\t\t\tEnter the username: ";
    cin >> ruserid;
    cout << "\t\t\tEnter the password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    if (!f1)
    {
        cerr << "Unable to open file records.txt\n";
        return;
    }
    f1 << ruserid << ' ' << rpassword << endl;
    cout << "\n\t\t\tRegistration is successful!\n";
}

void forgot()
{
    int option;
    cout << "\t\t\tYou forgot the password? No worries\n";
    cout << "\tPress 1 to search your ID by username\n";
    cout << "\tPress 2 to go back to the main menu\n";
    cout << "\t\t\tEnter your choice: ";
    cin >> option;

    switch (option)
    {
        case 1:
        {
            int count = 0;
            string suserid, sid, spass;
            cout << "\n\t\t\tEnter the username which you remembered: ";
            cin >> suserid;

            ifstream f2("records.txt");
            if (!f2)
            {
                cerr << "Unable to open file records.txt\n";
                return;
            }

            while (f2 >> sid >> spass)
            {
                if (sid == suserid)
                {
                    count = 1;
                    cout << "\n\nYour account is found!\n";
                    cout << "\n\nYour password is: " << spass << endl;
                    break;
                }
            }
            f2.close();
            if (count == 0)
            {
                cout << "\n\tSorry! Your account is not found!\n";
            }
            break;
        }
        case 2:
        {
            return;
        }
        default:
            cout << "\t\t\tWrong choice! Please try again\n";
    }
}

void details()
{
    if (!loggedInUser.empty())
    {
        cout << "\nDetails of the logged-in user:\n";
        cout << "Username: " << loggedInUser.front() << endl;
    }
    else
    {
        cout << "\nNo user is currently logged in.\n";
    }
}

void logout()
{
    cout << "Logging out...\n";
    loggedInUser.clear();
}

void displayPlayers()
{
    cout << "\nDisplaying players information...\n";
    string line;
    ifstream playersFile("players.txt");
    if (!playersFile)
    {
        cerr << "Unable to open file players.txt\n";
        return;
    }
    while (getline(playersFile, line))
    {
        cout << line << endl;
    }
    playersFile.close();
}

void addPlayer()
{
    string regNumber, firstName, lastName, dob, age, city, country, phone, email;
    cout << "\nEnter the registration number: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // to clear the input buffer
    getline(cin, regNumber);
    cout << "Enter the first name: ";
    getline(cin, firstName);
    cout << "Enter the last name: ";
    getline(cin, lastName);
    cout << "Enter the date of birth (DD/MM/YYYY): ";
    getline(cin, dob);
    cout << "Enter the age: ";
    getline(cin, age);
    cout << "Enter the city: ";
    getline(cin, city);
    cout << "Enter the country: ";
    getline(cin, country);
    cout << "Enter the phone number: ";
    getline(cin, phone);
    cout << "Enter the email address: ";
    getline(cin, email);

    ofstream playersFile("players.txt", ios::app);
    if (!playersFile)
    {
        cerr << "Unable to open file players.txt\n";
        return;
    }
    playersFile << regNumber << ", " << firstName << ", " << lastName << ", " << dob << ", " << age << ", " << city << ", " << country << ", " << phone << ", " << email << endl;
    playersFile.close();

    cout << "\nPlayer added successfully!\n";
}

void manageTeams()
{
    cout << "\nManaging teams (feature to be implemented)...\n";
}

void searchPlayers()
{
    string searchName, line;
    cout << "\nEnter the name of the player to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // to clear the input buffer
    getline(cin, searchName);

    ifstream playersFile("players.txt");
    if (!playersFile)
    {
        cerr << "Unable to open file players.txt\n";
        return;
    }
    bool found = false;
    while (getline(playersFile, line))
    {
        if (line.find(searchName) != string::npos)
        {
            cout << "Player found: " << line << endl;
            found = true;
            break;
        }
    }
    playersFile.close();

    if (!found)
    {
        cout << "Player not found.\n";
    }
}

