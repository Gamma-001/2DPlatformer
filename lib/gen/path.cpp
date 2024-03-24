#include <gen/path.hpp>

#include <string>

#ifdef WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

std::filesystem::path path::root() {
    static fs::path res(".");
    if (res != ".") return res;

#ifdef WIN32
    {
        char fileName[256];
        GetModuleFileNameA(NULL, fileName, 256);
        res = fs::canonical(std::string(fileName));
    }
#else
    res = fs::canonical("/proc/self/exe");
#endif

    res = res.parent_path().parent_path();
    return res;
}