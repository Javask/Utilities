#include "Utilities/FileUtils.h"
#include "Utilities/StringUtils.h"
#include <istream>
#include <ostream>
#include <fstream>
#ifdef CERESLOG_PLATFORM_WINDOWS
#include <Windows.h>
#else
#include <linux/limits.h>
#include <unistd.h>
#endif
namespace Utilities {
namespace fs = std::filesystem;

fs::path getExecutablePath() {
#ifdef CERESLOG_PLATFORM_WINDOWS
  // Use Windows API to find Current file
  std::vector<char> FileName = std::vector<char>(128);
  while (GetModuleFileNameA(nullptr, FileName.data(), (DWORD)FileName.size()) ==
         (DWORD)FileName.size()) {
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
      std::cerr << "Could not get filename!";
      abort();  // Unknown Error while finding executable
    }
    FileName.resize(FileName.size() + 128);
  }
  return {FileName.data()};
#else
  // Use Linux proc directory to find Current file
  // TODO Implement other OSes when targeted
  // TODO Bounds check count to PATH_MAX
  char FileName[PATH_MAX] = {};
  ssize_t count = readlink("/proc/self/exe", FileName, PATH_MAX);
  return std::string(FileName, (count > 0) ? count : 0);
#endif
}

fs::path createTempDir() {
  const auto TempDir = fs::temp_directory_path();
  auto dir = fs::path(TempDir);
  while (fs::exists(dir)) {
    dir = fs::path(TempDir).append(generateRandomString(8));
  }
  if (!create_directory(dir)) {
    throw std::runtime_error("Failed to create Temporary Directory!");
  }
  return dir;
}

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