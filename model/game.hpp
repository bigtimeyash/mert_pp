#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <map>
#include <iostream>

class Game
{
protected:
    std::string hostName;
    std::map<std::string, int> score;

public:
    Game(std::string);
    void addPlayer(std::string);

    std::string getName();
    bool removePlayer(std::string);
};

#endif