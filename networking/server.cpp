// #include <httpserver.hpp>
// #include "../libhttpserver-master/src/httpserver.hpp"

// using namespace httpserver;

// class hello_world_resource : public http_resource
// {
// public:
//     const std::shared_ptr<http_response> render(const http_request &)
//     {
//         return std::shared_ptr<http_response>(new string_response("Hello, World!"));
//     }
// };

// int main(int argc, char **argv)
// {
//     webserver ws = create_webserver(8080);

//     hello_world_resource hwr;
//     ws.register_resource("/hello", &hwr);
//     ws.start(true);

//     return 0;
// }

#include "../cpp-httplib-master/httplib.h"

int main(void) {
    using namespace httplib;

    Server svr;

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
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