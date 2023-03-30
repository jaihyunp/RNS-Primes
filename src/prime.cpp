#include "prime.h"
#include "arch32.h"
#include "arch64.h"
#include <iostream>

//bool _is_prime(uint32 prime)
//{
//    if (prime == 2)
//        return true;
//    if ((prime != 2) && !(prime & 1))
//        return false;
//
//    for (uint32 n = 3; ((int64) n) * n < (int64) prime; n += 2) {
//        if (prime % n)
//            continue;
//        else
//            return false;
//    }
//    return true;
//}
//
//bool _is_prime(uint64 prime)
//{
//    if (prime == 2)
//        return true;
//    if ((prime != 2) && !(prime & 1))
//        return false;
//
//    for (int64 n = 3; n < (int64) 0xFFFFFFFF && n * n < (int64) prime; n += 2) {
//        if (prime % n)
//            continue;
//        return false;
//    }
//    return true;
//}


bool is_prime(uint32 prime)
{
    if (prime < 2)
        return false;

    if ((prime != 2) && !(prime & 0x1))
        return false;

    uint32 s = prime - 1;
    while (!(s & 0x1))
        s >>= 1;
    uint32 as[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (uint32 a : as) {
        uint32 tmp = s, mod = expmod(a, tmp, prime);
        while (tmp != prime - 1 && mod != 1 && mod != prime - 1) {
            mod = mulmod(mod, mod, prime);
            tmp <<= 1;
        }
        if ((mod != prime - 1) && !(tmp & 0x1))
            return false;
    }
    return true;
}

bool is_prime(uint64 prime)
{
    if (prime < 2)
        return false;

    if ((prime != 2) && !(prime & 0x1))
        return false;

    uint64 s = prime - 1;
    while (!(s & 0x1))
        s >>= 1;
    uint64 as[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (uint64 a : as) {
        uint64 tmp = s, mod = expmod(a, tmp, prime);
        while (tmp != prime - 1 && mod != 1 && mod != prime - 1) {
            mod = mulmod(mod, mod, prime);
            tmp <<= 1;
        }
        if ((mod != prime - 1) && !(tmp & 0x1))
            return false;
    }
    return true;
}



int get_num_RNS_primes(int bitlen, int logN, int hwt = -1)
{
    int _hwt = (hwt > 0) ? hwt : bitlen;
    return 0;
}

uint32 get_RNS_prime30(int bitlen, int logN, int hwt);
uint64 get_RNS_prime60(int bitlen, int logN, int hwt);
int print_all_RNS_primes(int bitlen, int logN)
{
    int num = 0;
    // which means 2N | p-1
    if (bitlen < logN + 1)
        return num;

    for (uint64 prime = ((uint64) 1 << bitlen) + 1; !(prime >> (bitlen + 1)); prime += (uint64) 1 << (logN + 1)) {
        if (is_prime(prime)) {
            std::cout << prime << std::endl; 
            num ++ ;
        }
    }
    return num;
}
