#ifndef HASHING_FUNCTIONS_H
#define HASHING_FUNCTIONS_H

#include <stddef.h>

size_t sdbm(const char *str);
size_t fnv1a(const char *str);
size_t jenkins(const char *str);
size_t crc32(const char *str);
size_t adler32(const char *str);
size_t constant_hash(const char *str);

#endif // HASHING_FUNCTIONS_H
