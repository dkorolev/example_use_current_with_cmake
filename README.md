# example_use_current_with_cmake

## TL;DR: Clean perftest

```
git clone https://github.com/dkorolev/example_use_current_with_cmake
git clone --depth 1 -b stable https://github.com/c5t/current
git clone --depth 1 -b v1.14 https://github.com/c5t/googletest
time (cd example_use_current_with_cmake; make -j)
```


## Longer version

Please refer to `run.sh` for the strongly consistent version. Below is some eventually consistent one.

```
make
./.current/print_primes
./.current/print_primes -n 20

./.current/test_primes

make test

./.current/write_primes
./.current/process_primes
./.current/write_primes -n 20
./.current/process_primes

touch src/process_primes.cc && time make
touch src/process_shallow_primes.cc && time make

make debug
./.current_debug/print_primes
./.current_debug/print_primes -n 20

./.current_debug/test_primes

make debug_test
```
