#include <iostream>
#include "prime.h"
#include <cstdio>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <bit>
#include <vector>
#include <cmath>
#include <math.h>
#include <climits>
using namespace std;

void append_primes32 (uint64 delta_init, uint64 delta, vector<bool> &prime_avail, vector<uint32> &primes, vector<uint32> &list)
{
    int num = primes.size();
    long long int diff_min = LLONG_MAX;
    int idx1 = 0, idx2 = 0;
    for (int i = 0; i < num; i ++) {
        if (!prime_avail[i])
            continue;
        for (int j = 0; j < i; j ++) {
            if (!prime_avail[j])
                continue;
            long long int diff = (long long int) delta_init - (long long int) ((long double) delta * ((long double) delta / (long double) primes[i] / (long double) primes[j]));
            if (abs(diff) < abs(diff_min)) {
                diff_min = diff;
                idx1 = i;
                idx2 = j;
            }
        }
    }

    prime_avail[idx1] = false;
    prime_avail[idx2] = false;

    list.push_back(primes[idx1]);
    list.push_back(primes[idx2]);
}

int find_all_32RNS_primes (int logN, vector<uint32> &primes)
{
    int num = 0;
    for (int bitlen = 1; bitlen <= 32; bitlen ++) {
        for (uint32 prime = ((uint32) 1 << (bitlen - 1)) + 0x1; !(prime >> bitlen); prime += (uint32) 1 << (logN + 1)) {
            if (is_prime(prime)) {
                primes.push_back(prime);
                num ++;
            }
        }
    }
    return num;
}

void generate_list32 (uint64 delta_init, int logN, int number, vector<uint32> &list) 
{
    list.resize(0);
    std::vector<uint32> primes;
    int num = find_all_32RNS_primes(logN, primes);
    cout << "Total " << num << " number of <=32-bit RNS primes for logN = " << logN << "." << endl;

    std::vector<bool> prime_avail(num);
    for (int i = 0; i < num; i ++)
        prime_avail[i] = true;

    cout << "Target delta: " << delta_init << endl;;

    list.resize(0);
    uint64 delta = delta_init;
    for (int i = 0; i < number; i += 2) {
        append_primes32(delta_init, delta, prime_avail, primes, list);
        delta = (uint64) ((long double) delta * ((long double) delta / (long double) list[i] / (long double) list[i + 1]));
    }

    cout << "Final delta: " << delta << " (" << -log2l(abs((long double) delta / delta_init - 1)) << ") (after 1 mult: "; 
        
    cout << -log2l(abs(((long double) delta_init * ((long double) delta_init / (long double) list[0] / (long double) list[1])) / delta_init - 1)) << ")" << endl;
}



uint64 next_prime (uint64 prime, int logN)
{
    uint64 p = prime;
    while (1) {
        p += (uint64) 1 << (logN + 1);
        if (is_prime(p))
            return p;
    }
    return 0;
}
uint64 prev_prime (uint64 prime, int logN)
{
    uint64 p = prime;
    while (1) {
        p -= (uint64) 1 << (logN + 1);
        if (is_prime(p))
            return p;
    }
    return 0;   
}

void append_prime64 (uint64 delta_init, uint64 delta, int logN, vector<uint64> &list) 
{
    uint64 p1 = next_prime (((delta >> (logN + 1)) << (logN + 1)) + 1, logN);
    uint64 p2 = prev_prime ((((delta >> (logN + 1)) - 1) << (logN + 1)) + 1, logN);

    while (1) {
        int check = 0;
        for (uint64 prime : list) {
            if (p1 == prime) {
                check = 1;
            }
        }
        if (!check)
            break;
        p1 = next_prime(p1, logN);
    }
 
     while (1) {
        int check = 0;
        for (uint64 prime : list) {
            if (p2 == prime) {
                check = 1;
            }
        }
        if (!check)
            break;
        p2 = prev_prime(p2, logN);
    }
    
    
    long long int diff1 = (long long int) delta_init - (long long int) ((long double) delta * ((long double) delta / (long double) p1));
    long long int diff2 = (long long int) delta_init - (long long int) ((long double) delta * ((long double) delta / (long double) p2));

    uint64 p = p1;
    if (abs(diff1) > abs(diff2))
        p = p2;
    list.push_back(p);
}

void generate_list64 (uint64 delta_init, int logN, int number, vector<uint64> &list) 
{
    list.resize(0);
    if (!number)
        return;

    cout << "Target delta: " << delta_init << endl;;
    
    uint64 delta = delta_init;
    for (int i = 0; i < number; i ++) {
        append_prime64(delta_init, delta, logN, list);
        delta = (uint64) ((long double) delta * ((long double) delta / (long double) list[i]));
    }

    cout << "Final delta: " << delta << " (" << -log2l(abs((long double) delta / delta_init - 1)) << ")" << endl; 
}


int main()
{

    int logN = 16;

    uint64 delta_init = 1ULL << 58;

    cout << "<= 32-bit RNS primes" << endl;
    vector<uint32> list32(0);
    generate_list32(delta_init, logN, 60, list32);
    for (uint32 prime : list32) {
        cout << prime << "ULL, ";
    }
    cout << endl << endl;

    cout << "<= 64-bit RNS primes" << endl;
    vector<uint64> list64(0);
    generate_list64(delta_init, logN, 30, list64);
    for (uint64 prime : list64) {
        cout << prime << "ULL, ";
    }
    cout << endl << endl;
 
    return 0;
}
