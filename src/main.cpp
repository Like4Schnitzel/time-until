#include "handler.hpp"
#include <iostream>

std::unique_ptr<Handler> httpHandler;

void initialize(const string& address)
{
    uri_builder uri(address);
    auto addr = uri.to_uri().to_string();
    httpHandler = std::unique_ptr<Handler>(new Handler(addr));
    httpHandler->open().wait();

    cout << "Listening for requests at: " << addr << "\n";
}

void shutdown()
{
    httpHandler->close().wait();
}

int main(int argc, char* argv[])
{
    const string port = argc > 1 ? argv[1] : "8080";
    const string address = "http://127.0.0.1:" + port;
    initialize(address);

    // TODO actually make this text accurate to the functionality
    cout << "Press ENTER to exit.\n";
    string line;
    cin >> line;

    shutdown();
    return 0;
}
