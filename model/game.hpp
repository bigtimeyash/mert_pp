#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <map>
#include <iostream>
#include "user.hpp"

class Game
{
protected:
    std::string hostName;
    std::map<std::string, User> users;

public:
    Game();
    Game(User);
    void addPlayer(User);

    std::string getName();
    std::map<std::string, int> getScores();
    bool incrementScore(std::string);
    bool removePlayer(std::string);
};

#endif