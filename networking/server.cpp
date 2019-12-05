/*
 *   https://github.com/yhirose/cpp-httplib
 */

#include "../cpp-httplib-master/httplib.h"
#include "../model/user.hpp"
#include "../model/game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

static int num = 0;
static vector<string> names;

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

    svr.Get("/hi", [](const Request &req, Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/num", [](const Request &req, Response &res) {
        num++;
        char *val = (char *)malloc(1024 * sizeof(char));
        sprintf(val, "%d", num);
        res.set_content(val, "text/plain");
    });

    svr.Post("/create", [](const Request &req, Response &res) {
        // Retrieve name
        string name;
        auto it = req.params.begin();
        auto &x = *it;
        name = x.first;

        // Add name to vector of names
        names.push_back(name);
        
        res.set_content(name, "text/plain");
    });

    svr.Post("/isUnique", [](const Request &req, Response &res) {
        // Retrieve name
        string name;
        auto it = req.params.begin();
        auto &x = *it;
        name = x.first;

        // See if names vector contains name
        string result = "true";
        if (find(names.begin(), names.end(), name) != names.end()) {
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