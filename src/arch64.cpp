#include "typedefs.h"
#include "arch64.h"
#include <iostream>

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
