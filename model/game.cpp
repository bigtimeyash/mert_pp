#include "game.hpp"
#include "user.hpp"
#include <iostream>

using namespace std;

Game::Game()
{
    User dfu;
    Game::hostName = dfu.getName();
    Game::users[dfu.getName()] = dfu;
}
Game::Game(User host) : hostName{host.getName()}
{
    Game::users[host.getName()] = host;
}

void Game::addPlayer(User player)
{
    Game::users[player.getName()] = player;
}

string Game::getName()
{
    return Game::hostName;
}

map<string, int> Game::getScores()
{
    map<string, int> out;
    for (auto u : users)
    {
        out[u.first] = u.second.getScore();
    }
    return out;
}

bool Game::incrementScore(string player)
{
    if (users[player].getScoreLimit() > users[player].getScore())
    {
        users[player].updateScore(users[player].getScore() + 1);
        return true;
    }
    else
    {
        return false;
    }
}

bool Game::removePlayer(string player)
{
    if (users.count(player))
    {
        users.erase(player);
        return true;
    }
    else
    {
        return false;
    }
}