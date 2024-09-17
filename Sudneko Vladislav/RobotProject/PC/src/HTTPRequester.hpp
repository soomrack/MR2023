#ifndef HTTPREQUESTER
#define HTTPREQUESTER

#include <iostream>
#include <string>
#include "httplib.h"

class HTTPRequester {
public:
    HTTPRequester(const std::string& base_url) : base_url(base_url) {}

    std::string send_get_request(const std::string& path) {
        httplib::Client cli(base_url.c_str());
        auto res = cli.Get(path.c_str());

        if (res && res->status == 200) {
            return res->body;
        } else {
            std::cerr << "GET request failed: " << (res ? std::to_string(res->status) : "No response") << std::endl;
            return "";
        }
    }

    bool send_post_request(const std::string& path, const std::string& body) {
        httplib::Client cli(base_url.c_str());
        auto res = cli.Post(path.c_str(), body, "text/plain");

        if (res && res->status == 200) {
            return true;
        } else {
            std::cerr << "POST request failed: " << (res ? std::to_string(res->status) : "No response") << std::endl;
            return false;
        }
    }

private:
    std::string base_url;
};

#endif // HTTPREQUESTER