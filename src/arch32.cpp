#include "typedefs.h"
#include "arch32.h"
#include <iostream>

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
