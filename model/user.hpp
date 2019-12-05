#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include <iostream>

class User
{
protected:
    std::string name;
    int score;
    int scoreLimit;

public:
    User(std::string name, int scoreLimit);
    void updateScore(int newScore);
    std::string getName();
    int getScore();
    int getScoreLimit();
};

#endif