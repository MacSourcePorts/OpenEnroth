#include "DataPath.h"

#include <vector>
#include <set>

#include "FileSystem.h"

static std::filesystem::path globalDataPath;
static std::filesystem::path basePath;
static const std::vector<std::vector<std::string_view>> globalValidateList = {
    {"anims", "magic7.vid" },
    {"anims", "might7.vid" },
    {"data", "bitmaps.lod" },
//    {"data", "d3dbitmap.hwl" }, // We're not using HWL textures, so these are not required.
//    {"data", "d3dsprite.hwl" },
    {"data", "events.lod" },
    {"data", "games.lod" },
    {"data", "icons.lod" },
    {"data", "sprites.lod" },
    {"sounds", "audio.snd" },
    {"shaders", "glbillbshader.frag"},
    {"shaders", "glbillbshader.vert"},
    {"shaders", "glbspshader.frag"},
    {"shaders", "glbspshader.vert"},
    {"shaders", "gldecalshader.frag"},
    {"shaders", "gldecalshader.vert"},
    {"shaders", "glforcepershader.frag"},
    {"shaders", "glforcepershader.vert"},
    {"shaders", "gllinesshader.frag"},
    {"shaders", "gllinesshader.vert"},
    {"shaders", "glnuklear.frag"},
    {"shaders", "glnuklear.vert"},
    {"shaders", "gloutbuild.frag"},
    {"shaders", "gloutbuild.vert"},
    {"shaders", "glterrain.frag"},
    {"shaders", "glterrain.vert"},
    {"shaders", "gltextshader.frag"},
    {"shaders", "gltextshader.vert"},
    {"shaders", "gltwodshader.frag"},
    {"shaders", "gltwodshader.vert"}
};

void setDataPath(const std::filesystem::path &dataPath) {
    globalDataPath = dataPath;
}

void setBasePath(Platform *platform) {
    basePath = platform->basePath();
}

std::string makeDataPath(std::initializer_list<std::string_view> paths) {
    std::filesystem::path result = globalDataPath;

    for (auto p : paths)
        if (!p.empty())
            result /= p;

    return makeCaseInsensitivePath(result).string();
}

std::string makeDataPathMac(std::initializer_list<std::string_view> paths) {
    std::filesystem::path result = basePath;

    for (auto p : paths)
        if (!p.empty())
            result /= p;

    return makeCaseInsensitivePath(result).string();
}

bool validateDataPath(const std::string &data_path, std::string *missing_file) {
    for (auto v : globalValidateList) {
        std::filesystem::path path = data_path;
        for (auto p : v) {
            if (!p.empty())
                path /= p;
        }

        if (!std::filesystem::exists(makeCaseInsensitivePath(path))) {
            *missing_file = std::filesystem::absolute(path).string();
            return false;
        }
    }

    return true;
}

bool validateDataPathMac(const std::string &data_path, std::string *missing_file, Platform *platform) {
    for (auto v : globalValidateList) {
        std::filesystem::path path = data_path;
        std::filesystem::path path2 = platform->basePath();
        for (auto p : v) {
            if (!p.empty()) {
                path /= p;
                path2 /= p;
            }
        }

        if (!std::filesystem::exists(makeCaseInsensitivePath(path))) {
            if (!std::filesystem::exists(makeCaseInsensitivePath(path2))) {
                *missing_file = std::filesystem::absolute(path2).string();
                return false;
            }
        }
    }

    return true;
}
