#include <iostream>

#include "blocks/blobs/blobs.h"
#include "bricks/dflags/dflags.h"

#include "gen_primes.h"
#include "schema.h"

DEFINE_string(input, "primes.bin", "The file name to read the primes from.");

int main(int argc, char** argv) {
  ParseDFlags(&argc, &argv);
  current::ProcessBlob<Number>(FLAGS_input, [](Number const* X, size_t N) {
    std::cout << "Total: " << N << " primes." << std::endl;
    for (size_t i = 0; i < N; ++i) {
      std::cout << "Prime: " << X[i].value << std::endl;
    }
  });
}
