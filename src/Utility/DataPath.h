#pragma once

#include <string>
#include <type_traits>
#include <filesystem>
#include "Library/Platform/Application/PlatformApplication.h"

// TODO(captainurist): this doesn't belong in Utility

void setDataPath(const std::filesystem::path &dataPath);
void setBasePath(Platform *platform);

std::string makeDataPath(std::initializer_list<std::string_view> paths);

template<typename... Ts>
std::string makeDataPath(Ts&&... paths) {
    static_assert(((std::is_same_v<std::remove_cvref_t<Ts>, std::string> || std::is_same_v<std::decay_t<Ts>, const char *>) && ...),
                  "T must be a basic string");
    return makeDataPath({paths...});
}

std::string makeDataPathMac(std::initializer_list<std::string_view> paths);

template<typename... Ts>
std::string makeDataPathMac(Ts&&... paths) {
    static_assert(((std::is_same_v<std::remove_cvref_t<Ts>, std::string> || std::is_same_v<std::decay_t<Ts>, const char *>) && ...),
                  "T must be a basic string");
    return makeDataPathMac({paths...});
}

bool validateDataPath(const std::string &data_path, std::string *missing_file);
bool validateDataPathMac(const std::string &data_path, std::string *missing_file, Platform *platform);
