#include "Utilities/FileUtils.h"
#include <istream>
#include <ostream>
#include <fstream>

namespace Utilities {
namespace fs = std::filesystem;

std::optional<std::vector<char>> readFromFileRaw(
    const std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    return {};
  }
  std::ifstream file =
      std::ifstream(path.generic_string(), std::ios::in | std::ios::ate);
  if (!file.is_open()) {
    return {};
  }

  auto endPos = file.tellg();
  file.seekg(std::ios::beg);
  auto size = endPos - file.tellg();
  auto filedata = std::vector<char>(size + 1);
  file.read(filedata.data(), size);
  file.close();
  return filedata;
}

std::optional<std::string> readFromFile(const std::filesystem::path& path) {
  auto filedata = readFromFileRaw(path);
  if (!filedata) return {};
  return std::string(filedata->data());
}

bool writeToFileRaw(const std::filesystem::path& path,
                    const std::vector<char>& data) {
  auto stream =
      std::ofstream(path.generic_string(), std::ios::out | std::ios::trunc);
  if (!stream.is_open()) return false;
  stream.write(data.data(), data.size());
  stream.close();
  return true;
}

bool writeToFile(const std::filesystem::path& path, const std::string& str) {
  auto stream =
      std::ofstream(path.generic_string(), std::ios::out | std::ios::trunc);
  if (!stream.is_open()) return false;
  stream.write(str.c_str(), str.size());
  stream.close();
  return true;
}
}  // namespace Utilities