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

inline string toLower(const string& data)
{
    string tmp = data;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return tmp;
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
        long unitDiff = NULL;

        const string query = message.request_uri().query();
        const string lowerQuery = toLower(query);
        if (query.empty() || lowerQuery == "d" || lowerQuery == "day" || lowerQuery == "days")
        {
            unitDiff = round(diff / (double)(60 * 60 * 24));
        }
        else if (query == "M" || lowerQuery == "month" || lowerQuery == "months")
        {
            unitDiff = round(diff / (60 * 60 * 24 * 30.4375));
        }
        else if (lowerQuery == "y" || lowerQuery == "year" || lowerQuery == "years")
        {
            unitDiff = round(diff / (60 * 60 * 24 * 365.25));
        }
        else if (lowerQuery == "h" || lowerQuery == "hour" || lowerQuery == "hours")
        {
            unitDiff = round(diff / (double)(60 * 60));
        }
        else if (query == "m" || lowerQuery == "minute" || lowerQuery == "minutes")
        {
            unitDiff = round(diff / (double)60);
        }
        else if (lowerQuery == "s" || lowerQuery == "second" || lowerQuery == "seconds")
        {
            unitDiff = diff;
        }
        else
        {
            throw invalid_argument("Unit \"" + query + "\" not recognized.");
        }

        message.reply(status_codes::OK, unitDiff);
    }
    catch (invalid_argument e)
    {
        message.reply(status_codes::BadRequest, e.what());
    }
}
