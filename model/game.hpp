#ifndef GAME_HPP
#define GAME_HPP

using namespace std;
#include <vector>
#include <map>
#include <iostream>

class Game
{
protected:
    string hostName;
    map<string, int> score;

public:
    Game(string);
    void addPlayer(string);

    string getName();
    bool removePlayer(string);
};

#endif