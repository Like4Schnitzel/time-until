#pragma once

#include <ctime>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <boost/algorithm/string.hpp>

class DateTimeParser {
    public:
        static time_t parseISOTimestamp(std::string timestamp);
};
