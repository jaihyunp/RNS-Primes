#include <iostream>
#include "../prime.h"
#include "../arch32.h"
#include "../arch64.h"
#include <cstdio>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <bit>
#include <vector>
#include <cmath>
#include <math.h>

uint64 update_delta (uint64 delta, uint32 p1, uint32 p2) {
    return (uint64) ((long double) delta * ((long double) delta / (long double) p1 / (long double) p2));
};
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
const int EXP_LOGN16 = 3;
const int EXP_SF = 4;

int EXP = EXP_SF;
    
    if (EXP == EXP_SF) {
        int logN = 16;
        int num = 0;
        //for (uint32 prime = ((uint32) 1 << bitlen) + 0x1 - ((uint32) 1 << (logN + 1)); prime >> (bitlen - 1); prime -= (uint32) 1 << (logN + 1)) {
        
        std::vector<uint32> primes;
        std::vector<long double> log_primes;
        std::vector<bool> prime_avail;
        
        for (int bitlen : {29, 30}) {
            for (uint32 prime = ((uint32) 1 << (bitlen - 1)) + 0x1; !(prime >> bitlen); prime += (uint32) 1 << (logN + 1)) {
                if (is_prime(prime)) {
                    primes.push_back(prime);
                    log_primes.push_back(std::log2l(prime));
                    prime_avail.push_back(true);
                    num ++;
                }
            }
        }



    } else if (EXP == EXP_NUM_PRIMES) {
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

    } else if (EXP == EXP_LOGN16) {

        int logN = 16;
        int bitlen = 30;

        std::cout << "logN: " << logN << std::endl;
        std::cout << "bitlen: " << bitlen << std::endl;
        
        int num = 0;
        //for (uint32 prime = ((uint32) 1 << bitlen) + 0x1 - ((uint32) 1 << (logN + 1)); prime >> (bitlen - 1); prime -= (uint32) 1 << (logN + 1)) {
        
        std::vector<uint32> primes;
        std::vector<long double> log_primes;
//        std::vector<int> prime_pair;
        
//        long double log_avg = 0;
        for (uint32 prime = ((uint32) 1 << (bitlen - 1)) + 0x1; !(prime >> bitlen); prime += (uint32) 1 << (logN + 1)) {
            if (is_prime(prime)) {
//                std::cout << num << ", " << std::hex << prime << " (" << std::dec << std::__popcount(prime) << ")" << std::endl;
                primes.push_back(prime);
                log_primes.push_back(std::log2l(prime));
//                prime_pair.push_back(-1);
                num ++;
//                log_avg += logl(prime);
            }
        }
//        log_avg /= num;

        int num_pair = 0;
        std::cout << num << std::endl;
        for (int i = 0; i < num; i ++) {
            if (num - i - 1 <= i)
                break;
            std::cout << primes[i] << "ULL, ";
            std::cout << primes[num-i-1] << "ULL, ";
        }
        std::cout << std::endl;
        
        uint64 max = 0;
        uint64 avg = 0;
        for (int i = 0; i < num; i ++) {
            uint64 prod = (uint64) primes[i] * (uint64) primes[num-i-1];
            std::cout << prod << std::endl;
            if (prod > max)
                max = prod;
            num_pair ++;
            avg = (uint64) ((long double) avg * ((long double) num_pair / (num_pair + 1)) + (long double) prod / ((long double) (num_pair + 1)));
       }
        std::cout << "MAX: " << max << std::endl;
        std::cout << "AVG: " << avg << std::endl;

        uint64 delta = 578354284736413697ULL ;
        for (int i = 0; i < num; i ++) {
            std::cout << delta << std::endl;
            std::cout << (long double) delta / (long double) primes[i] / (long double) primes[num-i-1] << std::endl;
            delta = (uint64) ((long double) delta * ((long double) delta / (long double) primes[i] / (long double) primes[num-i-1]));
        }

//        std::cout << log_avg << std::endl;

//        for (int i = 0; i < num; i ++) {
//            long double min_log = 999999;
//            for (int j = 0; j < num; j ++) {
//                if (i == j)
//                    continue;
//                long double diff = abs(log_avg * 2 - log_primes[i] - log_primes[j]);
//                if (diff < min_log) {
//                    min_log = diff;
//                    prime_pair[i] = j;
//                }
//            }
//        }
//        for (int i = 0; i < num; i ++){
//            std::cout << "ASDFA " << prime_pair[i] << std::endl;
//        }

//        std::cout << "Bitlen of two composites:" << std::endl;
//        for (int i = 0; i < num; i ++) {
//            for (int j = 0; j < i; j ++) {
//                std::cout << i << ", " << j  << ", " << log_primes[i] + log_primes[j] << std::endl;
//            }
//        }
//        
//        std::cout << std::hex;
//        uint64 max_sf = 0, min_sf = (uint64) 0xFFFFFFFFFFFFFFFF;
//        std::cout << max_sf << std::endl;
//        std::cout << min_sf << std::endl;
//        for (int i = 0; i < num; i ++) {
//            uint64 sf = (uint64) primes[i] * primes[num-i-1];
//            if (sf < min_sf)
//                min_sf = sf;
//            if (sf > max_sf)
//                max_sf = sf;
//            std::cout << sf << std::endl;
//        }
////
//        std::cout << max_sf << std::endl;
//        std::cout << min_sf << std::endl;
//        std::cout << std::log2l((long double) max_sf / min_sf) << std::endl;

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
