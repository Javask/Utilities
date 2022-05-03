#include "Utilities/StringUtils.h"
#include <algorithm>
#include <regex>
namespace Utilities {

std::vector<std::string> splitString(const std::string& str,
                                     const std::set<char>& delimiters) {
  std::vector<std::string> result;

  char const* pch = str.c_str();
  char const* start = pch;
  for (; *pch; ++pch) {
    if (delimiters.find(*pch) != delimiters.end()) {
      if (start != pch) {
        std::string str2(start, pch);
        result.push_back(str2);
      } else {
        result.emplace_back("");
      }
      start = pch + 1;
    }
  }
  result.emplace_back(start);

  return result;
}

std::string intToHex(uintptr_t in) {
  std::stringstream stream;
  stream << std::hex << in;
  return stream.str();
}

std::vector<char> stringToVector(const std::string& message) {
  auto data = std::vector<char>(message.size());
  for (size_t i = 0; i < data.size(); i++) {
    data[i] = message.c_str()[i];
  }
  return data;
}

std::string toLowerCase(const std::string& val) {
  std::string data = val;
  std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(static_cast<int>(c)));
  });
  return data;
}

bool isInteger(const std::string& val, bool allowNegative) {
  auto regString = std::string("\\s*") + (allowNegative ? "(\\+|-)?" : "\\+?") +
                   "[[:digit:]]+\\s*";
  auto intRegex = std::regex(regString);
  return std::regex_match(val, intRegex);
}

bool isReal(const std::string& val, bool allowNegative) {
  auto regString = std::string("\\s*") + (allowNegative ? "(\\+|-)?" : "\\+?") +
                   "([[:digit:]]+(\\.[[:digit:]]+)?|\\.[[:digit:]]+)\\s*";
  auto realRegex = std::regex(regString);
  return std::regex_match(val, realRegex);
}

std::string removeFirstAndLastChar(const std::string& val) {
  return val.substr(1, val.size() - 2);
}

std::string removeFirstChar(const std::string& val) {
  return val.substr(1, val.size() - 1);
}

std::string removeLastChar(const std::string& val) {
  return val.substr(0, val.size() - 1);
}

std::vector<std::string> splitAtSpaces(const std::string& val) {
  const char space = ' ';
  auto substrings = std::vector<std::string>();
  size_t lastSpace = 0;
  for (size_t i = 0; i < val.size(); i++) {
    if (val[i] == space) {
      if (lastSpace != i) {
        substrings.push_back(val.substr(lastSpace, i - lastSpace));
      }
      lastSpace = i + 1;
    }
  }
  if (lastSpace < val.size()) {
    substrings.push_back(val.substr(lastSpace, val.size() - lastSpace));
  }
  return substrings;
}

std::vector<std::string> splitAtSpacesWithEscape(const std::string& val) {
  auto substrings = std::vector<std::string>();
  size_t lastSpace = 0;
  bool escape = false;
  bool inStringDQ = false;
  bool inStringSQ = false;
  for (size_t i = 0; i < val.size(); i++) {
    if (val[i] == '"' && !inStringSQ && !escape) {
      inStringDQ = !inStringDQ;
    }
    if (val[i] == '\'' && !escape) {
      inStringSQ = !inStringSQ;
    }

    if (val[i] == ' ' && !inStringDQ && !inStringSQ && !escape) {
      if (lastSpace != i) {
        substrings.push_back(val.substr(lastSpace, i - lastSpace));
      }
      lastSpace = i + 1;
    }

    if (val[i] == '\\')
      escape = true;
    else
      escape = false;
  }
  if (lastSpace < val.size()) {
    substrings.push_back(val.substr(lastSpace, val.size() - lastSpace));
  }
  if (inStringDQ || inStringSQ) {
    throw std::invalid_argument("Open quote in string!");
  }
  return substrings;
}
}  // namespace Utilities