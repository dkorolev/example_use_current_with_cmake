#pragma once

template <class F> void GenPrimes(int N, F &&f) {
  for (int i = 2; i <= N; ++i) {
    bool prime = true;
    for (int j = 2; j * j <= i && prime; ++j) {
      if ((i % j) == 0) {
        prime = false;
      }
    }
    if (prime) {
      f(i);
    }
  }
}
