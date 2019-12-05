/*
 *   https://github.com/yhirose/cpp-httplib
 */

#include "../cpp-httplib-master/httplib.h"
#include "../model/game.hpp"
#include "../model/user.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

static int num = 0;

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

int main(void)
{
    using namespace httplib;

    Server svr;

    vector<Game> games;
    games.push_back(Game("Matt"));
    games.push_back(Game("Clouds"));

    svr.Get("/hi", [](const Request &req, Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/num", [](const Request &req, Response &res) {
        num++;
        char *val = (char *)malloc(1024 * sizeof(char));
        sprintf(val, "%d", num);
        res.set_content(val, "text/plain");
    });

    svr.Get("/gameList", [games](const Request &req, Response &res) {
        string out;
        for (Game game : games)
        {
            out.append(game.getName());
            out.append("\n");
        }
        res.set_content(out, "text/plain");
    });

    svr.Post("/create", [](const Request &req, Response &res) {
        string test;
        for (auto it = req.params.begin(); it != req.params.end(); ++it)
        {
            const auto &x = *it;
            test.append(x.first);
            test.append("\n");
            test.append(x.second);
            //cout << x.first << "  " << x.second;
        }
        // printf("%s", "test");

        // res.set_content("Succesfully created a new game!", "text/plain");
        res.set_content(test, "text/plain");
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