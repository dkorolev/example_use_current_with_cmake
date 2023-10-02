#include <iostream>

#include "blocks/blobs/blobs.h"
#include "bricks/dflags/dflags.h"

#include "gen_primes.h"
#include "schema.h"

DEFINE_uint32(n, 100, "Up to what number should the primes be generated.");
DEFINE_string(output, "primes.bin", "The file name to output the primes into.");

int main(int argc, char **argv) {
  ParseDFlags(&argc, &argv);
  std::vector<Number> numbers;
  GenPrimes(static_cast<int>(FLAGS_n), [&numbers](int p) { numbers.emplace_back(p); });
  current::WriteBlob(numbers, FLAGS_output);
}
