#ifndef USER_HPP
#define USER_HPP

using namespace std;
#include <vector>

class User
{
protected:
    int UserId;
    int score;
    int scoreLimit;

public:
    User(int); // pass in maxscore

    void updateScore(int);
};

#endif