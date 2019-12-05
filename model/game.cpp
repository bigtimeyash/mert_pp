#include "game.hpp"
#include <iostream>

using namespace std;

Game::Game(string hostName) : hostName{hostName}
{
    Game::score[hostName] = 0;
}

void Game::addPlayer(string player)
{
    Game::score[player] = 0;
}

string Game::getName()
{
    return Game::hostName;
}

bool Game::removePlayer(string player)
{
    if (Game::score.count(player) > 0)
    {
        Game::score.erase(player);
        return true;
    }
    else
    {
        return false;
    }
}