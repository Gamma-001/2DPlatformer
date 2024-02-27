#include <gen/strutils.hpp>

#include <cctype>
#include <utility>

void strutils::trim(std::string& _str) {
    int start = 0, end = _str.size() - 1;
    while (start < _str.size() && isspace(_str[start])) start += 1;
    while (end > start && isspace(_str[end])) end -= 1;

    _str.erase(_str.begin() + end + 1, _str.end());
    _str.erase(_str.begin(), _str.begin() + start);
}

std::vector<std::string> strutils::split(std::string_view _str, char _delim, bool _includeEmpty) {
    std::vector<std::string> res;
    std::string cur;
    for (auto &x: _str) {
        if (x != _delim) cur.push_back(x);
        else {
            if (!cur.size() && !_includeEmpty) continue;
            res.push_back(std::move(cur));
            cur = std::string();
        }
    }
    if (cur.size() || _includeEmpty) res.push_back(std::move(cur));

    return res;
}