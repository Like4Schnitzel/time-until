#include "datetimeparser.hpp"

std::vector<std::string> splitString(std::string str, std::string delimiter)
{
    std::vector<std::string> result;
    boost::split(result, str, boost::is_any_of(delimiter));
    return result;
    /*
    int i = 0;
    int nextPos = str.find(delimiter);
    while (nextPos > -1)
    {
        result.push_back(str.substr(i, nextPos-i));
        i = nextPos;
        nextPos = str.find(delimiter, i+1);
    }
    return result;
    */
}

time_t DateTimeParser::parseISOTimestamp(std::string timestamp)
{
    time_t unixtime;
    struct tm timeinfo;
    int tPos = timestamp.find("T");
    // parse time
    if (tPos > -1)
    {
        std::string timeString = timestamp.substr(tPos+1);
        timestamp = timestamp.substr(0, tPos); // remove time portion
        auto timeComponents = splitString(timeString, ":");
        if (timeComponents.size() != 3)
        {
            throw std::invalid_argument("Time component must consist of 3 parts");
        }

        // TODO more input validation

        std::istringstream(timeComponents[0]) >> std::dec >> timeinfo.tm_hour;
        std::istringstream(timeComponents[1]) >> std::dec >> timeinfo.tm_min;
        std::istringstream(timeComponents[2]) >> std::dec >> timeinfo.tm_sec;
    }
    else
    {
        timeinfo.tm_hour = 0;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;
    }

    auto dateComponents = splitString(timestamp, "-");
    if (dateComponents.size() != 3)
    {
        throw std::invalid_argument("Date component must consist of 3 parts");
    }

    // TODO more input validation

    std::istringstream(dateComponents[0]) >> std::dec >> timeinfo.tm_year;
    timeinfo.tm_year -= 1900;
    std::istringstream(dateComponents[1]) >> std::dec >> timeinfo.tm_mon;
    timeinfo.tm_mon -= 1;
    std::istringstream(dateComponents[2]) >> std::dec >> timeinfo.tm_mday;

    timeinfo.tm_isdst = -1;

    unixtime = mktime(&timeinfo);
    return unixtime;
}
