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

bool Game::removePlayer(string player)
{
    if (Game::score.count(player) > 0)
    {
        Game::score.erase(player);
    }
    else
    {
        return false;
    }
}