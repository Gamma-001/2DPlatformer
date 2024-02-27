#pragma once

#include <string>
#include <memory>
#include <map>
#include <filesystem>
#include <utility>
#include <cassert>

#include <engine/shader.hpp>
#include <engine/texture.hpp>

// immutable global store
class GlobalStoreSingleton {
public:
    GlobalStoreSingleton() = delete;

    static void init();

    inline static bool isInitialized();
    inline static const Shader* getShader(const std::string& _key);

private:
    static std::map<std::string, std::unique_ptr<Shader>> sShaders;

    static bool sInitialized;
};

bool GlobalStoreSingleton::isInitialized() { return sInitialized; }

const Shader* GlobalStoreSingleton::getShader(const std::string& _key) {
    assert(sInitialized);

    return sShaders[_key].get();
}