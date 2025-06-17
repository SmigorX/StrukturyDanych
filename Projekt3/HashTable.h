// Hash
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode {
    char *key;
    void *value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    size_t capacity;
    size_t size;
    size_t collisions;
    size_t (*hash_func)(const char *);
    float load_factor;
} HashTable;

HashTable *ht_create(size_t initial_capacity,
                     size_t (*hash_func)(const char *));
void ht_destroy(HashTable *table);
int ht_insert(HashTable *table, const char *key, void *value);
int ht_remove(HashTable *table, const char *);
void *ht_get(HashTable *table, const char *key);
void ht_resize(HashTable *table, size_t new_capacity);

#endif // HASH_TABLE_H
