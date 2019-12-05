#include "../cpp-httplib-master/httplib.h"
#include "../model/user.hpp"
#include <iostream>

using namespace std;

httplib::Client cli("localhost", 1234);

bool validateName(string name)
{
    auto res = cli.Post("/isUnique", name, "application/x-www-form-urlencoded");
    if (res && res->status == 200)
    {
        string body = res->body;

        // Name is unique
        if (body.compare("true") == 0)
        {
            cout << "Hello, " << name << "!" << endl;
            return true;
        }
        // Name is not unique
        else if (body.compare("false") == 0)
        {
            cout << "The name " << name << " is already in use. Please try another name." << endl;
            return false;
        }
    }
    else
    {
        cout << "Oh no! Server error!" << endl;
    }

    return false;
}

int main()
{
    cout << "Welcome to drink++ !!!" << endl;
    cout << endl;

    // Get name
    string isUnique = "false";
    string name;
    cout << "What is your name?" << endl;
    cin >> name;
    cout << endl;

    // Check if name is unique
    while (!validateName(name))
    {
        cin >> name;
    }
    cout << endl;

    cout << "How many shots until you blackout?" << endl;
    int limit;
    cin.clear();
    cin >> limit;
    while (cin.fail())
    {
        cout << "Invalid input! Please try again." << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> limit;
        if (limit < 1)
        {
            cin.setstate(ios_base::failbit);
        }
    }
    cout << endl;

    //create user on the server
    auto res = cli.Post("/createUser", "name=" + name + "&limit=" + to_string(limit), "application/x-www-form-urlencoded");
    if (res && res->status == 200)
    {
        cout << res->body << endl;
    }
    else
    {
        cout << "Oh no! An error occured while attempting to create a new user." << endl;
    }

    cout << endl
         << "Awesome! Here is a list of existing users:"
         << endl
         << endl;

    res = cli.Get("/userList");
    if (res && res->status == 200)
    {
        cout << res->body << endl;
    }
    else
    {
        cout << "Oh no! An error occured while attempting to create a new game." << endl;
    }

    // show list of games

    cout << endl
         << "Awesome! Here is a list of existing games:"
         << endl
         << endl;

    res = cli.Get("/gameList");
    if (res && res->status == 200)
    {
        cout << res->body << endl;
    }
    else
    {
        cout << "Oh no! An error occured while attempting to create a new game." << endl;
    }

    cout << "[1] Create new game" << endl;
    cout << "[2] Join existing game" << endl;
    cout << endl;

    int input = 0;
    cin >> input;
    while (cin.fail())
    {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> input;
        if (input < 1 || input > 2)
        {
            cin.setstate(ios_base::failbit);
        }
    }

    // Create new game
    if (input == 1)
    {
        cout << "Creating new game...." << endl
             << endl;
        res = cli.Post("/create", name, "application/x-www-form-urlencoded");
        if (res && res->status == 200)
        {
            cout << res->body << endl;
        }
        else
        {
            cout << "Oh no! An error occured while attempting to create a new game." << endl;
        }
    }
    // Join existing game
    else if (input == 2)
    {
    }
    cout << "out of this test area" << endl;
}