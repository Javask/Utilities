#pragma once
#include <vector>
#include <cstring>
#include <initializer_list>
namespace Utilities {
template <typename T>
std::vector<T> combineVectors(std::initializer_list<std::vector<T>> list) {
  size_t combinedSize = 0;
  for (auto& v : list) combinedSize += v.size();
  auto out = std::vector<T>(combinedSize);
  size_t offset = 0;
  for (auto& elem : list) {
    memcpy(out.data() + offset, elem.data(), elem.size());
    offset += elem.size();
  }
  return out;
}

template <typename T>
std::vector<char> copyToByteVector(const std::vector<T>& val) {
  std::vector<char> out = std::vector<char>(sizeof(T) * val.size());
  memcpy(out.data(), val.data(), out.size());
  return out;
}

template <typename T>
std::vector<T> copyToVector(T* ptr, size_t count) {
  std::vector<T> out = std::vector<T>(count);
  memcpy(out.data(), ptr, sizeof(T) * count);
  return out;
}

template <typename T>
bool vectorEquals(const std::vector<T>& lhs, const std::vector<T>& rhs) {
  if (lhs.size() != rhs.size()) return false;
  for (size_t i = 0; i < lhs.size(); i++) {
    if (lhs[i] != rhs[i]) return false;
  }
  return true;
}
}  // namespace Utilities