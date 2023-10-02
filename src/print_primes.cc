#include <iostream>

#include "bricks/dflags/dflags.h"

#include "gen_primes.h"

DEFINE_uint32(n, 10, "Up to what number should the primes be generated.");

int main(int argc, char **argv) {
  ParseDFlags(&argc, &argv);
  GenPrimes(static_cast<int>(FLAGS_n), [](int p) { std::cout << "Prime: " << p << std::endl; });
}
