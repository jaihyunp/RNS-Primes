#include <iostream>
#include "../prime.h"
#include "../arch32.h"
#include "../arch64.h"
#include <cstdio>
#include <string>
#include <stdio.h>
#include <stdlib.h>

int main()
{

//    for (int logN = 15; logN <= 17; logN ++) {
//        for (int bitlen = 20; bitlen <= 30; bitlen ++) {
//            int num = 0; 
//            for (uint32 prime = ((uint32) 1 << bitlen) + 1; !(prime >> (bitlen + 1)); prime += (uint32) 1 << (logN + 1)) {
//                if (is_prime(prime) != _is_prime(prime))
//                    std::cout << prime << " " << _is_prime(prime) <<  std::endl;
//            }
//        }
//    }
//
//    for (int logN = 17; logN <= 17; logN ++) {
//        for (int bitlen = 60; bitlen <= 60; bitlen ++) {
//            int num = 0; 
//            for (uint64 prime = ((uint64) 1 << bitlen) + 1; num < 1000; prime += (uint32) 1 << (logN + 1)) {
//                num ++;
//                std::cout << "Great1 " << prime << _is_prime(prime) << std::endl;
//                std::cout << "Great2 " << prime << is_prime(prime) << std::endl;
//                if (is_prime(prime) != _is_prime(prime)) {
//                    std::cout << "It sucks!!!!!!" << std::endl;
//                    return 1;
//                }
//            }
//        }
//    }

    for (int logN = 15; logN <= 17; logN ++) {
        for (int bitlen = 20; bitlen <= 63; bitlen ++) {
            freopen(("out/logN"+std::to_string(logN)+"/" + std::to_string(bitlen) + "bit.primes").c_str(),"w", stdout);
            int num = 0; 
            for (uint64 prime = ((uint64) 1 << bitlen) + 1; !(prime >> (bitlen + 1)); prime += (uint64) 1 << (logN + 1)) {
                if (is_prime(prime)) {
                    std::cout << prime << std::endl; 
                    num ++ ;
                }
            }
            freopen("CON", "a", stdout);
            std::cout << logN << " " << bitlen << ": " << num << std::endl;
        }
    }

    return 0;
}
