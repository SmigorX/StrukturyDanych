#ifndef HASHING_FUNCTIONS
#define HASHING_FUNCTIONS

#include <stddef.h>

// Hashing functions
// Hash table data structure
// Collision avoidance

size_t sdbm(char original[]) {
    size_t hash = 0;
    int c;
    while ((c = *original++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
}

size_t fnv1a(char original[]) {
    const size_t fnv_prime = 0x100000001b3;
    size_t hash = 0xcbf29ce484222325;
    unsigned char c;
    while ((c = (unsigned char)*original++)) {
        hash ^= c;
        hash *= fnv_prime;
    }
    return hash;
}

size_t jenkins(char original[]) {
    size_t hash = 0;
    unsigned char c;
    while ((c = (unsigned char)*original++)) {
        hash += c;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

size_t crc32(char original[]) {
    size_t crc = 0xFFFFFFFF;
    unsigned char c;
    while ((c = (unsigned char)*original++)) {
        crc ^= c;
        for (int i = 0; i < 8; i++) {
            size_t mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
    }
    return ~crc;
}

size_t adler32(char original[]) {
    const size_t MOD_ADLER = 65521;
    size_t a = 1, b = 0;
    unsigned char c;
    while ((c = (unsigned char)*original++)) {
        a = (a + c) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    return (b << 16) | a;
}

#endif
