# RNS Primes

Finding and listing RNS primes for leveled RNS-CKKS.

For given N, we say p is an RNS prime if X^N+1 splits in Zp. This is equivalent to p is congruent to 1 mod 2N.
This script

This code finds RNS primes that are appropriate to be used for RNS-CKKS. It also finds RNS primes for 32-bit RNS-CKKS with higher precision bits than 32.

## Compiling
To build my code, call
``` bash
mkdir obj bin
make
```
This will build a binary file `bin/prime.exe`.
