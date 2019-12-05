#include "../cpp-httplib-master/httplib.h"
#include "../model/user.hpp"
#include <iostream>

using namespace std;

int main()
{
    httplib::Client cli("localhost", 1234);

    cout << "Welcome to drink++ !!!" << endl;
    cout << endl;

    cout << "What is your name?" << endl;
    string name;
    cin >> name;
    cout << endl;

    cout << "How many shots until you blackout?" << endl;
    int limit;
    cin >> limit;
    while (cin.fail())
    {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> limit;
        if (limit < 1)
        {
            cin.setstate(ios_base::failbit);
        }
    }

    // User user = new User()

    // show list of games

    cout << endl
         << "Awesome! Here is a list of existing games:"
         << endl
         << endl;

    auto res = cli.Get("/gameList");
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
        auto res = cli.Post("/create", "asdf", "application/x-www-form-urlencoded");
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
    cout << "out of this test area";
}