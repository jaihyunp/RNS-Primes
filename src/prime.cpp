/* author: jhyunp@snu.ac.kr */
#include "prime.h"
#include "arch32.h"
#include "arch64.h"
#include <iostream>
#include <cassert>

uint32 mulmod(uint32 a, uint32 b, uint32 p)
{
    assert(!(p >> 31) && "p has more than 31 bits");
    uint32 x = 0, y = a % p;
    uint32 _b = b;
    while (_b > 0) {
        if (_b & 0x1)
            x = (x + y) % p;
        y = (y << 1) % p;
        _b >>= 1;
    }
    return x;
};

uint32 expmod(uint32 base, uint32 exp, uint32 p)
{
    assert(!(p >> 31) && "p has more than 31 bits");
    uint32 x = 1, y = base, _exp = exp;
    while (_exp) {
        if (_exp & 0x1)
            x = mulmod(x, y, p);
        y = mulmod(y, y, p);
        _exp >>= 1;
    }
    return x;
};

uint64 mulmod(uint64 a, uint64 b, uint64 p)
{
    assert(!(p >> 63) && "p has more than 63 bits");
    uint64 x = 0, y = a % p;
    uint64 _b = b;
    while (_b > 0) {
        if (_b & 0x1)
            x = (x + y) % p;
        y = (y << 1) % p;
        _b >>= 1;
    }
    return x;
};

uint64 expmod(uint64 base, uint64 exp, uint64 p)
{
    assert(!(p >> 63) && "p has more than 63 bits");
    uint64 x = 1, y = base, _exp = exp;
    while (_exp) {
        if (_exp & 0x1)
            x = mulmod(x, y, p);
        y = mulmod(y, y, p);
        _exp >>= 1;
    }
    return x;
};

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
