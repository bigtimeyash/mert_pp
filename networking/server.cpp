/*
 *   https://github.com/yhirose/cpp-httplib
 */

#include "../cpp-httplib-master/httplib.h"
#include <stdio.h>
#include <stdlib.h>

static int num = 0;

int main(void) {
    using namespace httplib;

    Server svr;

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/num", [](const Request& req, Response& res) {
        num++;
        char *val = (char*)malloc(1024 * sizeof(char));
        sprintf(val, "%d", num);
        res.set_content(val, "text/plain");
    });

    svr.Get("/create", [](const Request& req, Response& res) {
        res.set_content("Succesfully created a new game!", "text/plain");
    });

    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });

    svr.Get("/stop", [&](const Request& req, Response& res) {
        svr.stop();
    });

    svr.listen("localhost", 1234);
}