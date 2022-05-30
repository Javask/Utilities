#include <catch2/catch_test_macros.hpp>
#include "Utilities/VectorUtils.h"

using namespace Utilities;
TEST_CASE("Combine Vectors") {
  std::vector<char> a = {'a', 'b'};
  std::vector<char> b = {'c', 'd'};
  std::vector<char> ab = {'a', 'b', 'c', 'd'};
  REQUIRE(vectorEquals(combineVectors({a, b}), ab));
}

TEST_CASE("Vector equals") {
  std::vector<char> a = {'a', 'b'};
  std::vector<char> b = {'c', 'd'};
  std::vector<char> ab = {'a', 'b', 'c', 'd'};
  REQUIRE(!vectorEquals(a, ab));
  REQUIRE(!vectorEquals(b, ab));
  REQUIRE(vectorEquals(ab, ab));
}

TEST_CASE("Copy To Bytevector") {
  std::vector<char> a = {0, 0, 0, 0, 1, 0, 0, 0};
  std::vector<int> i = {0, 1};
  auto ic = copyToByteVector(i);
  REQUIRE(vectorEquals(a, ic));
}

TEST_CASE("Copy To Vector") {
  std::vector<int> i = {0, 1};
  auto ic = copyToVector(i.data(), i.size());
  REQUIRE(vectorEquals(i, ic));
}