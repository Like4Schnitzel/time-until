#pragma once

#include "datetimeparser.hpp"
#include <math.h>
#include <cpprest/http_listener.h>

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class Handler
{
    public:
        Handler();
        Handler(string url);
        pplx::task<void> open();
        pplx::task<void> close();

    private:
        void handleGet(http_request message);
        http_listener listener;
};
