#pragma once

#include <filesystem>

namespace path {
    namespace fs = std::filesystem;

    fs::path root();

    inline fs::path join(fs::path _path) { return _path; }

    template <class T, class... Targs>
    fs::path join(fs::path _path, T _dir, Targs... _dirs);
};

template <class T, class... Targs>
std::filesystem::path path::join(fs::path _path, T _dir, Targs... _dirs) {
    return join(_path / fs::path(_dir), _dirs...);
}