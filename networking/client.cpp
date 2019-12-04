#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to drink++ !!!" << endl;
    cout << endl;

    cout << "[1] Create new game" << endl;
    cout << "[2] Join existing game" << endl;
    cout << endl;

    int input = 0;
    cin >> input;
    while (cin.fail()) {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> input;
        if (input < 1 || input > 2) {
            cin.setstate(ios_base::failbit);
        }
    }

    cout << "Input: " << input << endl;
}