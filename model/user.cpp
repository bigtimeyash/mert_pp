#include "user.hpp"

using namespace std;
User::User() : name{"defaultctr"}, score{0}, scoreLimit{10} {}
User::User(string name, int scoreLimit) : name{name}, score{0}, scoreLimit{scoreLimit} {}

void User::updateScore(int newScore)
{
    score = newScore;
}

string User::getName()
{
    return name;
}

int User::getScore()
{
    return score;
}

int User::getScoreLimit()
{
    return scoreLimit;
}