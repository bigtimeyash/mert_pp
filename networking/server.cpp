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

static int num = 0;
static std::vector<Game> games;
static std::vector<std::string> names; // cached for easy dupe checking
static std::vector<User> users;

int main(void)
{
    using namespace httplib;

    Server svr;

    games.push_back(Game("Default1"));
    games.push_back(Game("Default2"));
    names.push_back("defaultName1");
    users.push_back(User("defaultName1", 0));

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
        for (Game game : games)
        {
            out.append(game.getName());
            out.append("\n");
        }
        res.set_content(out, "text/plain");
    });

    svr.Post("/getScores", [](const Request &req, Response &res) {
        // Get game
        std::string game;
        auto it = req.params.begin();
        auto &x = *it;
        game = x.first;

        res.set_content("SCORES", "text/plain");
    });

    svr.Get("/userList", [](const Request &req, Response &res) {
        std::string out;
        for (User u : users)
        {
            out.append(u.getName());
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

        names.push_back(name);
        User a(name, std::stoi(limit));
        users.push_back(a);

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

        games[gameInd].addPlayer(name);

        res.set_content("|" + name + "|" + std::to_string(gameInd) + "|", "text/plain");
    });
    svr.Post("/createGame", [](const Request &req, Response &res) {
        // Retrieve name
        std::string name;
        auto it = req.params.begin();
        auto &x = *it;
        name = x.first;

        res.set_content("success", "text/plain");
    });

    svr.Post("/isUnique", [](const Request &req, Response &res) {
        // Retrieve name
        std::string name;
        auto it = req.params.begin();
        auto &x = *it;
        name = x.first;

        // See if names vector contains name
        std::string result = "true";
        if (find(names.begin(), names.end(), name) != names.end())
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