#!/bin/bash

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
