#ifndef GAME_HPP
#define GAME_HPP

using namespace std;
#include <vector>

class Game
{
protected:
    int GameID;
    vector<int> users;

public:
    Game();

    void addPlayer(int);
    void removePlayer(int);
};

#endif