#pragma once
#include "typedefs.h"

bool is_prime(uint32 prime);
//bool _is_prime(uint32 prime);
bool is_prime(uint64 prime);
//bool _is_prime(uint64 prime);

int get_num_RNS_primes(int bitlen, int logN, int hwt);

uint32 get_RNS_prime30(int bitlen, int logN, int hwt);
uint64 get_RNS_prime60(int bitlen, int logN, int hwt);
int print_all_RNS_primes(int bitlen, int logN);

