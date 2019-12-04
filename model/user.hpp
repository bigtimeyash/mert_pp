#ifndef USER_HPP
#define USER_HPP

using namespace std;

#include <vector>
#include <iostream>

class User {
    protected:
        string name;
        int score;
        int scoreLimit;

    public:
        User(string name, int scoreLimit);
        void updateScore(int);
        int getScore();
        int getScoreLimit();
};

#endif