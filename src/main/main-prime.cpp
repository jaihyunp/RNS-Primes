#include <iostream>
#include "../prime.h"
#include "../arch32.h"
#include "../arch64.h"
#include <cstdio>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <bit>

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

const int EXP_NUM_PRIMES = 1;
const int EXP_LOW_HWT = 2;

int EXP = EXP_LOW_HWT;
    
    if (EXP == EXP_NUM_PRIMES) {
        for (int logN : {16, 17, 15, 14, 13}) {
            for (int bitlen = 28; bitlen < 32; bitlen ++) {
                int num = 0;
                int hwt[32] = {0, };
                for (uint32 prime = ((uint32) 1 << (bitlen - 1)) + 1; !(prime >> bitlen); prime += (uint32) 1 << (logN + 1)) {
                    if (is_prime(prime)) {
                        num ++;
                        hwt[std::__popcount(prime)] ++;
                    }
                }

                std::cout << "logN: " << logN << std::endl;
                std::cout << "bitlen: " << bitlen << std::endl;
                std::cout << "Num of NTT primes: " << num << std::endl;
                for (int hamming = 0; hamming < 32; hamming ++) {
                    if (!hwt[hamming])
                        continue;
                    std::cout << "  hwt (" << hamming << "): " << hwt[hamming] << std::endl;
                }
                std::cout << std::endl;
            }
        }

    } else if (EXP == EXP_LOW_HWT) {
        
        int logN = 16;
        int bitlen = 30;
        
        std::cout << "logN: " << logN << std::endl;
        std::cout << "bitlen: " << bitlen << std::endl;
        uint32 minprime = 0xFFFFFFFF, maxprime = 0x1;
        
        int num = 0;
        //for (uint32 prime = ((uint32) 1 << bitlen) + 0x1 - ((uint32) 1 << (logN + 1)); prime >> (bitlen - 1); prime -= (uint32) 1 << (logN + 1)) {
        for (uint32 prime = ((uint32) 1 << (bitlen - 1)) + 0x1; !(prime >> bitlen); prime += (uint32) 1 << (logN + 1)) {
            if (is_prime(prime)) {
                if (std::__popcount(prime) > 7)
                    continue;
                num ++;
                std::cout << std::hex << prime << " (" << std::dec << std::__popcount(prime) << ")" << std::endl;
                if (minprime > prime)
                    minprime = prime;
                if (maxprime < prime)
                    maxprime = prime;
                
                if (num >= 100)
                    break;
            }
        }

        std::cout << (double) maxprime / minprime << std::endl;
        std::cout << num << std::endl;
    }

//    for (int logN = 15; logN <= 17; logN ++) {
//        for (int bitlen = 20; bitlen <= 63; bitlen ++) {
//            freopen(("out/logN"+std::to_string(logN)+"/" + std::to_string(bitlen) + "bit.primes").c_str(),"w", stdout);
//            int num = 0; 
//            for (uint64 prime = ((uint64) 1 << bitlen) + 1; !(prime >> (bitlen + 1)); prime += (uint64) 1 << (logN + 1)) {
//                if (is_prime(prime)) {
//                    std::cout << prime << std::endl; 
//                    num ++ ;
//                }
//            }
//            freopen("CON", "a", stdout);
//            std::cout << logN << " " << bitlen << ": " << num << std::endl;
//        }
//    }

    return 0;
}
