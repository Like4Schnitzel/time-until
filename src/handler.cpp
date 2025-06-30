#include "handler.hpp"

Handler::Handler(string url) : listener(url)
{
    listener.support(methods::GET, bind(&Handler::handleGet, this, placeholders::_1));
}

pplx::task<void> Handler::open()
{
    return listener.open();
}

pplx::task<void> Handler::close()
{
    return listener.close();
}

void Handler::handleGet(http_request message)
{
    auto paths = uri::split_path(uri::decode(message.relative_uri().path()));
    if (paths.size() != 1)
    {
        message.reply(status_codes::BadRequest);
        return;
    }

    try
    {
        const auto timestamp = DateTimeParser::parseISOTimestamp(paths[0]);
        const auto now = time(NULL);
        const auto diff = timestamp - now;
        const long diffDays = round(diff / (double)(60 * 60 * 24));
        message.reply(status_codes::OK, diffDays);
    }
    catch (invalid_argument e)
    {
        message.reply(status_codes::BadRequest, e.what());
    }
}
