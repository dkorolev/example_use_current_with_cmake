#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "gen_primes.h"

inline std::string GenPrimesAsString(int n) {
  std::ostringstream oss;
  GenPrimes(n, [&oss](int i) { oss << ' ' << i; });
  std::string result = oss.str();
  return result.empty() ? "" : result.substr(1);
}

TEST(Primes, UpTo2) {
  EXPECT_EQ("2", GenPrimesAsString(2));
}

TEST(Primes, UpTo8) {
  EXPECT_EQ("2 3 5 7", GenPrimesAsString(8));
}

TEST(Primes, UpTo24) {
  EXPECT_EQ("2 3 5 7 11 13 17 19 23", GenPrimesAsString(24));
}

TEST(Primes, None) {
  EXPECT_EQ("", GenPrimesAsString(1));
}
