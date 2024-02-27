#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace strutils {
    // trim white space from front and back of the string
    void trim(std::string& _str);

    // split the string into array of strings based on the delimiter
    // by default ignores any empty strings that might be encountered
    std::vector<std::string> split(std::string_view _str, char _delim, bool _includeEmpty = false);
}