#include <game/globalStore.hpp>

#include <fstream>
#include <cassert>
#include <array>
#include <cctype>
#include <iostream>

#include <gen/path.hpp>
#include <gen/strutils.hpp>

bool GlobalStoreSingleton::sInitialized = false;
decltype(GlobalStoreSingleton::sShaders) GlobalStoreSingleton::sShaders;

void GlobalStoreSingleton::init() {
    if (sInitialized) {
        std::cout << "global store already initialized, calling initialized again";
        return;
    }

    static std::array<std::pair<std::string, std::string>, 1> arShaders = {
        std::make_pair("defaultFlat", "flatShader")
    };

    // load all the shaders
    std::unique_ptr<Shader> shader;
    for (auto &x: arShaders) {
        shader.reset(new Shader());
        shader->loadFromFile(
            path::root()/"shaders"/(x.second + "Vert.glsl"),
            path::root()/"shaders"/(x.second + "Frag.glsl")
        );
        sShaders[x.first] = std::move(shader);
    }

    sInitialized = true;
}