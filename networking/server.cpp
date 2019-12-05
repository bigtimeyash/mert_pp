/*
 *   https://github.com/yhirose/cpp-httplib
 */

#include "../cpp-httplib-master/httplib.h"
#include "../model/user.hpp"
#include "../model/game.hpp"
#include "../model/user.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>

static int num = 0;
static std::vector<Game> games;

static std::map<std::string, User> users;

int main(void)
{
    using namespace httplib;

    Server svr;

    //dummy users and games for testing
    User df1 = User("Default1", 1);
    User df2 = User("Default2", 2);
    games.push_back(Game(df1));
    games.push_back(Game(df2));
    users[df1.getName()] = df1;
    users[df2.getName()] = df2;

    svr.Get("/hi", [](const Request &req, Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/num", [](const Request &req, Response &res) {
        num++;
        char *val = (char *)malloc(1024 * sizeof(char));
        sprintf(val, "%d", num);
        res.set_content(val, "text/plain");
    });

    svr.Get("/gameList", [](const Request &req, Response &res) {
        std::string out;
        int i = 0;
        for (Game game : games)
        {
            out.append("[");
            out.append(std::to_string(i));
            out.append("]");
            out.append(" ");
            out.append(game.getName());
            out.append("\n");
            i++;
        }
        res.set_content(out, "text/plain");
    });

    svr.Post("/getScores", [](const Request &req, Response &res) {
        // Get game
        std::string game;
        auto it = req.params.begin();
        auto &x = *it;
        game = x.first;

        int gameInd = std::stoi(game);
        Game g = games[gameInd];

        std::string scores;
        for (auto e : g.getScores())
        {
            scores.append(e.first);
            scores.append(": ");
            scores.append(std::to_string(e.second));
            scores.append("\n");
        }

        res.set_content(scores, "text/plain");
    });

    svr.Post("/increaseScore", [](const Request &req, Response &res) {
        std::string game, name;

        auto it = req.params.begin();

        game = it->second;
        it++;
        name = it->second;

        int gameInd = std::stoi(game);
        if (games[gameInd].incrementScore(name))
        {
            res.set_content("Incremented", "text/plain");
        }
        else
        {
            res.set_content("false", "text/plain");
        }
    });

    svr.Get("/userList", [](const Request &req, Response &res) {
        std::string out;
        for (auto u : users)
        {
            out.append(u.second.getName());
            out.append("\n");
        }
        res.set_content(out, "text/plain");
    });

    svr.Post("/createUser", [](const Request &req, Response &res) {
        // Retrieve name
        std::string name, limit;

        auto it = req.params.begin();

        limit = it->second;
        it++;
        name = it->second;

        User a(name, std::stoi(limit));
        users[name] = a;

        res.set_content("|" + name + "|" + limit + "|", "text/plain");
    });

    svr.Post("/joinGame", [](const Request &req, Response &res) {
        // Retrieve name
        std::string name;
        int gameInd;

        auto it = req.params.begin();

        gameInd = std::stoi(it->second);
        it++;
        name = it->second;

        games[gameInd].addPlayer(users[name]);

        res.set_content("|" + name + "|" + std::to_string(gameInd) + "|", "text/plain");
    });
    svr.Post("/createGame", [](const Request &req, Response &res) {
        // Retrieve name
        std::string name;
        auto it = req.params.begin();
        auto &x = *it;
        name = x.first;

        Game g = Game(users[name]);
        games.push_back(g);

        res.set_content(std::to_string(games.size() - 1), "text/plain");
    });

    svr.Post("/isUnique", [](const Request &req, Response &res) {
        // Retrieve name
        std::string name;
        auto it = req.params.begin();
        auto &x = *it;
        name = x.first;

        std::string result = "true";
        if (users.count(name))
        {
            result = "false";
        }

        res.set_content(result, "text/plain");
    });

    svr.Get(R"(/numbers/(\d+))", [&](const Request &req, Response &res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });

    svr.Get("/stop", [&](const Request &req, Response &res) {
        svr.stop();
    });

    // svr.set_logger([](const Request &req, const Response &res) {
    //     printf("%s", log(req, res).c_str());
    // });

    svr.listen("localhost", 1234);
}

std::string dump_headers(const httplib::Headers &headers)
{
    std::string s;
    char buf[BUFSIZ];

    for (auto it = headers.begin(); it != headers.end(); ++it)
    {
        const auto &x = *it;
        snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
        s += buf;
    }

    return s;
}

std::string log(const httplib::Request &req, const httplib::Response &res)
{
    std::string s;
    char buf[BUFSIZ];

    s += "================================\n";

    snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
             req.version.c_str(), req.path.c_str());
    s += buf;

    std::string query;
    for (auto it = req.params.begin(); it != req.params.end(); ++it)
    {
        const auto &x = *it;
        snprintf(buf, sizeof(buf), "%c%s=%s",
                 (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
                 x.second.c_str());
        query += buf;
    }
    snprintf(buf, sizeof(buf), "%s\n", query.c_str());
    s += buf;

    s += dump_headers(req.headers);

    s += "--------------------------------\n";

    snprintf(buf, sizeof(buf), "%d %s\n", res.status, res.version.c_str());
    s += buf;
    s += dump_headers(res.headers);
    s += "\n";

    if (!res.body.empty())
    {
        s += res.body;
    }

    s += "\n";

    return s;
}