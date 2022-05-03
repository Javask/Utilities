#pragma once
#include <string>
#include <vector>
#include <set>
#include <cstddef>

namespace Utilities {
std::string generateRandomString(std::size_t len);

std::vector<std::string> splitAtSpaces(const std::string& val);
std::vector<std::string> splitAtSpacesWithEscape(const std::string& val);
std::vector<std::string> splitString(const std::string& str,
                                     const std::set<char>& delimiters);

std::vector<char> stringToVector(const std::string& message);

std::string removeFirstAndLastChar(const std::string& val);
std::string removeFirstChar(const std::string& val);
std::string removeLastChar(const std::string& val);

std::string intToHex(uintptr_t in);
std::string toLowerCase(const std::string& val);

bool isInteger(const std::string& val, bool allowNegative = true);
bool isReal(const std::string& val, bool allowNegative = true);

}  // namespace Utilities