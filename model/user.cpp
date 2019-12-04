#include "user.hpp"

User::User(string name, int scoreLimit) {
    name = name;
    score = 0;
    scoreLimit = scoreLimit;
}

int User::getScore() {
    return score;
}

int User::getScoreLimit() {
    return scoreLimit;
}