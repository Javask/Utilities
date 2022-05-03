#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <optional>

namespace Utilities {
std::optional<std::string> readFromFile(const std::filesystem::path& filePath);

std::optional<std::vector<char>> readFromFileRaw(
    const std::filesystem::path& filePath);

bool writeToFile(const std::filesystem::path& path, const std::string& str);

bool writeToFileRaw(const std::filesystem::path& path,
                    const std::vector<char>& data);
}  // namespace Utilities